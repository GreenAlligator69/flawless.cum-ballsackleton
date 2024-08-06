#pragma once 
#include "../../inc.hpp"

auto clock_old = std::chrono::high_resolution_clock::now( );

std::unordered_map<std::string, c_aimbot::projectile_properties> c_aimbot::weapon_properties = {
	{"Striker AR", {80000, 3.5}},
	{"Nemesis AR", {80000, 3.5}},
	{"Warforged Assault Rifle", {80000, 3.5}},
	{"Tactical Assault Rifle", {80000, 3.5}},
	{"Reaper Sniper Rifle", {50000, 3.5}},
	{"Enforcer AR", {65000, 2.5}},
	{"Ranger Pistol", {60000, 2}},
	{"Thunder Burst SMG", {70000, 3}},
	{"Hyper SMG", {70000, 3}},
	{"Harbinger SMG", {70000, 3}},
	{"Thunder Bust SMG", {70000, 3}},
	{"Huntress DMR", {96000, 2.5}},
	{"Hand Cannon", {60000, 2}},
	{"Drum Gun", {75000, 3}},
};

auto c_aimbot::prediction_calculations( uemath::fvector target, uemath::fvector velocity, uemath::fvector local_velocity, float projectile_speed_scale, float projectile_gravity_scale, float distance ) -> uemath::fvector
{
	// Calculate the vertical distance between the player and the target
	float vertical_distance = target.z - local_velocity.z;

	// Only adjust gravity if the target is above the player
	if ( vertical_distance > 0 )
	{
		// Calculate the exceed counts based on distance thresholds
		int exceed_count_70 = static_cast< int >( ( distance - 70 ) / 70 );
		int exceed_count_125 = static_cast< int >( ( distance - 125 ) / 125 );
		int exceed_count_150 = static_cast< int >( ( distance - 150 ) / 150 );

		// Adjust gravity scale based on distance
		if ( exceed_count_150 > 0 )
		{
			projectile_gravity_scale -= 0.3f;
		}
		else if ( exceed_count_125 > 0 )
		{
			projectile_gravity_scale -= 0.4f;
		}
		else if ( exceed_count_70 > 0 )
		{
			projectile_gravity_scale -= 0.5f;
		}
	}

	// Calculate horizontal and vertical time
	float horizontal_time = distance / projectile_speed_scale;
	float vertical_time = distance / projectile_speed_scale;

	// Predict target's position
	target.x += velocity.x * horizontal_time;
	target.y += velocity.y * horizontal_time;
	target.z += velocity.z * vertical_time + fabs( -980 * projectile_gravity_scale ) * 0.5f * ( vertical_time * vertical_time );

	return target;
}

uemath::frotator c_aimbot::find_look_at_rotation( uemath::fvector& start, uemath::fvector& target ) {

	uemath::fvector direction = target - start; // Direction vector from start to target
	direction = direction / sqrt( direction.length( ) ); // Normalize the direction vector

	// Calculate yaw
	double yaw = atan2( direction.y, direction.x ) * ( 180.0 / std::numbers::pi ); // Convert radians to degrees

	// Invert the pitch calculation if necessary
	double pitch = atan2( direction.z, sqrt( direction.x * direction.x + direction.y * direction.y ) ) * ( 180.0 / std::numbers::pi ); // Convert radians to degrees

	// Return the FRotator with the calculated yaw and pitch, and a roll of 0
	return uemath::frotator( pitch, yaw, 0.0 );
}

uemath::frotator c_aimbot::clamp_angle( uemath::frotator startRotation, uemath::frotator endRotation, float SmoothScale )
{
	uemath::frotator ret = endRotation;

	ret.pitch -= startRotation.pitch;
	ret.yaw -= startRotation.yaw;

	//clamp
	if ( ret.yaw < -180.0f )
		ret.yaw += 360.0f;

	if ( ret.yaw > 180.0f )
		ret.yaw -= 360.0f;

	if ( ret.pitch < -74.0f )
		ret.pitch = -74.0f;

	if ( ret.pitch > 74.0f )
		ret.pitch = 74.0f;

	ret.pitch = ( ret.pitch / SmoothScale ) + startRotation.pitch;
	ret.yaw = ( ret.yaw / SmoothScale ) + startRotation.yaw;

	//clamp
	if ( ret.yaw < -180.0f )
		ret.yaw += 360.0f;

	if ( ret.yaw > 180.0f )
		ret.yaw -= 360.0f;

	if ( ret.pitch < -74.0f )
		ret.pitch = -74.0f;

	if ( ret.pitch > 74.0f )
		ret.pitch = 74.0f;

	return ret;
}

auto c_aimbot::aim_lock( uemath::fvector aim_location ) -> void
{

	auto aim_rotation = find_look_at_rotation(
		engine.get( )->location,
		aim_location
	);

	if ( g_vars.get( )->aim.smooth > 1 ) {

		aim_rotation = clamp_angle(
			engine.get( )->rotation,
			aim_rotation,
			g_vars.get( )->aim.smooth
		);
	}

	aim_rotation.pitch = aim_rotation.pitch - engine.get( )->rotation.pitch;
	aim_rotation.yaw = aim_rotation.yaw - engine.get( )->rotation.yaw;

	// normalize Yaw to be between -180 and 180
	aim_rotation.normalize( );

	// Check and scale Pitch if it exceeds the bounds
	if ( abs( aim_rotation.pitch ) > 0.68f ) {
		auto scaleFactorPitch = 0.68f / abs( aim_rotation.pitch );
		aim_rotation.pitch *= scaleFactorPitch;
	}
	// Check and scale Yaw if it exceeds the bounds
	if ( abs( aim_rotation.yaw ) > 0.68f ) {
		auto scaleFactorYaw = 0.68f / abs( aim_rotation.yaw );
		aim_rotation.yaw *= scaleFactorYaw;
	}

	g_entity->local_player_controller->view_angles( aim_rotation );
	g_entity->local_player_controller->rotation_reset( aim_rotation );

}

//uemath::frotator clamp_angle( uemath::frotator startRotation, uemath::frotator endRotation, float SmoothScale )
//{
//	uemath::frotator ret = endRotation;
//
//	ret.pitch -= startRotation.pitch;
//	ret.yaw -= startRotation.yaw;
//
//	//clamp
//	if ( ret.yaw < -180.0f )
//		ret.yaw += 360.0f;
//
//	if ( ret.yaw > 180.0f )
//		ret.yaw -= 360.0f;
//
//	if ( ret.pitch < -74.0f )
//		ret.pitch = -74.0f;
//
//	if ( ret.pitch > 74.0f )
//		ret.pitch = 74.0f;
//
//	ret.pitch = ( ret.pitch / SmoothScale ) + startRotation.pitch;
//	ret.yaw = ( ret.yaw / SmoothScale ) + startRotation.yaw;
//
//	//clamp
//	if ( ret.yaw < -180.0f )
//		ret.yaw += 360.0f;
//
//	if ( ret.yaw > 180.0f )
//		ret.yaw -= 360.0f;
//
//	if ( ret.pitch < -74.0f )
//		ret.pitch = -74.0f;
//
//	if ( ret.pitch > 74.0f )
//		ret.pitch = 74.0f;
//
//	return ret;
//}
//
//uemath::frotator find_look_at_rotation( uemath::fvector& start, uemath::fvector& target ) {
//
//	uemath::fvector direction = target - start; // Direction vector from start to target
//	direction = direction / sqrt( direction.length( ) ); // Normalize the direction vector
//
//	// Calculate yaw
//	double yaw = atan2( direction.y, direction.x ) * ( 180.0 / std::numbers::pi ); // Convert radians to degrees
//
//	// Invert the pitch calculation if necessary
//	double pitch = atan2( direction.z, sqrt( direction.x * direction.x + direction.y * direction.y ) ) * ( 180.0 / std::numbers::pi ); // Convert radians to degrees
//
//	// Return the FRotator with the calculated yaw and pitch, and a roll of 0
//	return uemath::frotator( pitch, yaw, 0.0 );
//}
//
//auto c_aimbot::aim_lock( uemath::fvector aim_location ) -> void
//{
//
//	//auto aim_rotation = find_look_at_rotation(
//	//	m_engine.get( )->location,
//	//	aim_location
//	//);
//
//	//if ( g_vars.get( )->aim.smooth > 1 ) {
//
//	//	aim_rotation = clamp_angle(
//	//		m_engine.get( )->rotation,
//	//		aim_rotation,
//	//		g_vars.get( )->aim.smooth
//	//	);
//	//}
//
//	//aim_rotation.pitch = aim_rotation.pitch - m_engine.get( )->rotation.pitch;
//	//aim_rotation.yaw = aim_rotation.yaw - m_engine.get( )->rotation.yaw;
//
//	//// normalize Yaw to be between -180 and 180
//	//aim_rotation.normalize( );
//
//	//// Check and scale Pitch if it exceeds the bounds
//	//if ( abs( aim_rotation.pitch ) > 0.68f ) {
//	//	auto scaleFactorPitch = 0.68f / abs( aim_rotation.pitch );
//	//	aim_rotation.pitch *= scaleFactorPitch;
//	//}
//	//// Check and scale Yaw if it exceeds the bounds
//	//if ( abs( aim_rotation.yaw ) > 0.68f ) {
//	//	auto scaleFactorYaw = 0.68f / abs( aim_rotation.yaw );
//	//	aim_rotation.yaw *= scaleFactorYaw;
//	//}
//
//	//m_engine.get( )->local_player_controller->view_angles( aim_rotation );
//	//m_engine.get( )->local_player_controller->rotation_reset( aim_rotation );
//}

auto c_aimbot::tick( ) -> void
{
	//m_engine.get( )->update_matrix( );

	//std::scoped_lock mutex( this->m_mutex );

	//for ( ;; ) {
	//	
	//	sdk::u_skeletal_mesh_component* closest_mesh = { };
	//	auto target_distance = flt_max;

	//	auto fn = [ & ] ( aactor::c_list const entity ) {
	//		const auto player = static_cast< aactor::c_list const >( entity );

	//		auto player_state = player.m_state;

	//		const auto in_lobby = player.m_game_state->is_in_lobby( );

	//		m_engine->player_controller = player.m_actor->controller( );
	//		if ( m_engine->player_controller->is_local_controller( ) )
	//		{

	//			m_engine.get( )->local_player_state = std::move( player_state );
	//			m_engine.get( )->local_player_pawn = player.m_actor;
	//			m_engine.get( )->local_player_controller = std::move( m_engine->player_controller );

	//			//auto local_weapon = local_pawn->current_weapon( );

	//		}

	//		if ( player.m_actor == m_engine.get( )->local_player_pawn ) return;

	//		auto skeletal_mesh = player.m_actor->mesh( );
	//		if ( !skeletal_mesh ) return;

	//		auto head_bone = m_engine.get( )->get_bone( skeletal_mesh, 110 );
	//		if ( !head_bone.is_valid( ) )
	//			return;

	//		auto root_bone = m_engine.get( )->get_bone( skeletal_mesh, 0 );
	//		if ( !root_bone.is_valid( ) )
	//			return;

	//		auto local_mesh = m_engine.get( )->local_player_pawn->mesh( );

	//		auto local_bone = m_engine.get( )->get_bone( local_mesh, 0 );

	//		auto distance = local_bone.distance_to( root_bone ) / 100;
	//		if ( !in_lobby && distance >= g_vars.get( )->misc.maximum_distance )
	//			return;

	//		auto m_distance = in_lobby ? 10.0f : distance;
	//		if ( !m_distance )
	//			return;

	//		auto head_screen = m_engine.get( )->world_to_screen( head_bone );
	//		if ( !m_engine.get( )->in_screen( head_screen ) )
	//			return;

	//		if ( g_vars.get( )->aim.enabled )
	//		{

	//			auto dx = head_screen.x - ( g_render.get( )->m_width_2 );
	//			auto dy = head_screen.y - ( g_render.get( )->m_height_2 );
	//			auto dist = sqrtf( dx * dx + dy * dy );

	//			if ( dist < g_vars.get( )->aim.fov_c
	//				&& dist < target_distance )
	//			{

	//				target_distance = dist;
	//				closest_mesh = skeletal_mesh;

	//			}

	//		}

	//	};
	//	g_entity->loop( fn );

	//	if ( closest_mesh && g_vars.get( )->aim.enabled ) {

	//		uemath::fvector bone = m_engine.get( )->get_bone( closest_mesh, 110 );

	//		auto is_held = ( GetAsyncKeyState( g_vars.get( )->aim.aim_keycode ) & 0x8000 );
	//		if ( is_held )
	//		{
	//			std::printf( "ho" );
	//			this->aim_lock( bone );
	//		}
	//	}
	//	else
	//	{
	//		closest_mesh = 0;
	//		target_distance = flt_max;
	//	}
	//}

}