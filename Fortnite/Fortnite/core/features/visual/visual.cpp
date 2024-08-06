#pragma once 
#include "../../inc.hpp"

auto c_visual::render( ) -> void
{
	engine->update_matrix( );

	sdk::u_skeletal_mesh_component* closest_mesh = { };
	auto target_distance = flt_max;

	// i am gonna put all the render esp in a function, no shit should be defined here but calling our render func
	auto fn = [ & ] ( aactor::c_list const entity ) {
		const auto player = static_cast< aactor::c_list const >( entity );

		auto player_controller = player.m_actor->controller( );
		if ( player_controller->is_local_controller( ) )
		{
			g_entity->local_player_state = player.m_state;
			g_entity->local_player_pawn = player.m_actor;
			g_entity->local_player_controller = player_controller;
		}

		if ( player.m_actor == g_entity->local_player_pawn ) return;

		auto mesh = player.m_actor->mesh( );
		if ( !mesh ) return;

		auto head_bone = mesh->get_bone_id( 110 );
		if ( !head_bone.is_valid( ) )
			return;

		auto root_bone = mesh->get_bone_id( 0 );
		if ( !root_bone.is_valid( ) )
			return;

		const auto in_lobby = player.m_game_state->is_in_lobby( );

		auto distance = engine->location.distance_to( root_bone ) / 100;
		if ( !in_lobby && distance >= g_vars->misc.maximum_distance )
			return;

		auto m_distance = in_lobby ? 10.0f : distance;
		if ( !m_distance ) return;

		auto head_direct = engine->world_to_screen( head_bone );
		if ( !engine->in_screen( head_direct ) )
			return;

		head_bone.z += 20.f;
		auto head_screen = engine->world_to_screen( head_bone );
		if ( !engine->in_screen( head_screen ) )
			return;

		root_bone.z -= 10.f;
		auto root_screen = engine->world_to_screen( root_bone );
		if ( !engine->in_screen( root_screen ) )
			return;

		auto local_weapon = g_entity->local_player_pawn->retrieve_player_weapon( );
		auto pred = g_aimbot.get( )->weapon_properties.find( local_weapon );
		if ( pred != g_aimbot.get( )->weapon_properties.end( ) ) {
			g_aimbot.get( )->projectile_speed = pred->second.speed;
			g_aimbot.get( )->projectile_gravity = pred->second.gravity;
		}
		else {
			g_aimbot.get( )->projectile_speed = 0;
			g_aimbot.get( )->projectile_gravity = 0;
		}

		if ( g_vars.get( )->aim.enabled ) {
			auto dx = head_screen.x - ( g_render.get( )->m_width_2 );
			auto dy = head_screen.y - ( g_render.get( )->m_height_2 );
			auto dist = sqrtf( dx * dx + dy * dy );

			if ( dist < g_vars.get( )->aim.fov_c && dist < target_distance ) {
				if ( g_vars.get( )->aim.prediction ) {
					g_aimbot.get( )->velocity = player.m_actor->root_component( )->component_velocity( );
					g_aimbot.get( )->local_velocity = g_entity->local_player_pawn->root_component( )->component_velocity( );
				}
				target_distance = dist;
				closest_mesh = mesh;
			}
		}

		auto box_color = framework->get_color( 0, 0, 0 );
		auto is_bot = player.m_state->is_bot( );
		if ( is_bot ) {
			box_color = framework->get_color( 254, 0, 0 );
		}
		else {
			box_color = framework->get_color( 254, 169, 1 );
		}

		auto bounds = mesh->get_bounds( );

		// entity.relative_location
		auto min_location = bounds.orgin - bounds.box_extent; // bottom
		auto max_location = bounds.orgin + bounds.box_extent; // top

		auto bounds_min_screen = engine->world_to_screen( min_location );
		auto bounds_max_screen = engine->world_to_screen( max_location );
		auto bounds_orgin = engine->world_to_screen( bounds.orgin );

		if ( g_vars.get( )->visuals.bounding_corner ) {

			bounds.box_extent *= 1.8f;

			bounds.orgin.x -= bounds.box_extent.x / 2.f;
			bounds.orgin.y -= bounds.box_extent.y / 2.f;
			bounds.orgin.z -= bounds.box_extent.z / 2.f;

			uemath::fvector one = bounds.orgin;
			uemath::fvector two = bounds.orgin; two.x += bounds.box_extent.x;
			uemath::fvector three = bounds.orgin; three.x += bounds.box_extent.x; three.y += bounds.box_extent.y;
			uemath::fvector four = bounds.orgin; four.y += bounds.box_extent.y;

			uemath::fvector five = one; five.z += bounds.box_extent.z;
			uemath::fvector six = two; six.z += bounds.box_extent.z;
			uemath::fvector seven = three; seven.z += bounds.box_extent.z;
			uemath::fvector eight = four; eight.z += bounds.box_extent.z;

			auto s1 = engine->world_to_screen( one );
			auto s2 = engine->world_to_screen( two );
			auto s3 = engine->world_to_screen( three );
			auto s4 = engine->world_to_screen( four );
			auto s5 = engine->world_to_screen( five );
			auto s6 = engine->world_to_screen( six );
			auto s7 = engine->world_to_screen( seven );
			auto s8 = engine->world_to_screen( eight );

			double x_array[ 8 ] = { s1.x, s2.x, s3.x, s4.x, s5.x, s6.x, s7.x, s8.x };
			float right = x_array[ 0 ], left = x_array[ 0 ];

			for ( auto right_idx = 0; right_idx < 8; right_idx++ )
				if ( x_array[ right_idx ] > right )
					right = x_array[ right_idx ];

			for ( auto left_idx = 0; left_idx < 8; left_idx++ )
				if ( x_array[ left_idx ] < left )
					left = x_array[ left_idx ];

			uemath::fvector min, max, size;
			min.x = left;
			min.y = root_screen.y;

			max.x = right;
			max.y = head_screen.y;

			size.x = min.x - max.x;
			size.y = min.y - max.y;

			framework->bounding_corner( max, size, box_color );
		}

		if ( g_vars->visuals.distance ) {
			auto distance_format = std::format( "{:.0f}m", m_distance );

			framework->text(
				distance_format,
				root_screen.x, root_screen.y,
				uemath::flinearcolor( 255, 255, 255, 255 ),
				14, 0
			);

		}

		};
	g_entity->loop( fn );

	if ( closest_mesh && g_vars->aim.enabled ) {
		auto bone = closest_mesh->get_bone_id( 110 );

		const auto closest_bone = engine->world_to_screen( bone );
		if ( !engine->in_screen( closest_bone ) )
			return;

		auto cross_hair = engine.get( )->get_cross_distance( closest_bone.x, closest_bone.y, g_render->m_width_2, g_render->m_height_2 );
		if ( cross_hair <= g_vars.get( )->aim.fov_c ) {
			float distance = engine.get( )->location.distance( bone );

			if ( g_aimbot.get( )->projectile_speed != 0 ) {

				bone = g_aimbot->prediction_calculations(
					bone, 
					g_aimbot->velocity,
					g_aimbot->local_velocity, 
					g_aimbot->projectile_speed,
					g_aimbot->projectile_gravity, 
					distance 
				);

				const auto predicted_bone = engine->world_to_screen( bone );

				framework->text(
					"X",
					predicted_bone.x, predicted_bone.y,
					uemath::flinearcolor( 255, 40, 215, 250 ),
					14, 0
				);
			}

			auto is_held = ( GetAsyncKeyState( g_vars.get( )->aim.aim_keycode ) & 0x8000 );
			if ( is_held ) {
				if ( g_vars.get( )->aim.ignore_invisible ) {
					if ( closest_mesh->is_visible( ) ) {
						g_aimbot.get( )->aim_lock( bone );
					}
				}
			}
		}
		else
		{
			closest_mesh = 0;
			target_distance = flt_max;
		}
	}

	if ( g_vars->misc.crosshair )
		framework->crosshair( );

	if ( g_vars.get( )->misc.fov )
		framework.get( )->fov( );
}
