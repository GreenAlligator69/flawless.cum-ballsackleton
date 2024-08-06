#pragma once 
#include "../inc.hpp"
#include <windows.h>
#include <ShellAPI.h>

m_interface::c_interface::c_interface( )
{
	this->color_menu_bg = uemath::flinearcolor( 255, 10, 10, 10 );
	this->color_menu_fg = uemath::flinearcolor( 255, 23, 21, 30 );
	this->color_menu_bar = uemath::flinearcolor( 255, 13, 13, 13 );
	this->color_menu_theme = uemath::flinearcolor( 255, 216, 169, 255 );

	this->color_checkbox_bg = uemath::flinearcolor( 255, 32, 32, 32 );
	this->color_checkbox_hovered = uemath::flinearcolor( 255, 43, 43, 43 );
	this->color_checkbox_active = uemath::flinearcolor( 255, 239, 68, 68 );

	g_vars->load( );
}

// text disabled = 48, 47, 55
// text color = 255, 205, 204, 206
// purple = 255, 130, 67, 186

auto m_interface::c_interface::draw_interface( ) -> void 
{
	//this->add_page( 0, [ & ]( ) {

	//	this->begin_parent( "Visuals", uemath::fvector2d( 0, 0 ), uemath::fvector2d( 750, 600 ) );
	//	{
	//		this->set_position( uemath::fvector2d { 265.f, 65.f } );

	//		this->add_widget( uemath::fvector2d( 280.0f, 520.0f ) );
	//		{
	//			// HEADER/PIN
	//			this->set_position( uemath::fvector2d{ 265.f, 82.f } );
	//			framework.get( )->line( current_offset( ).x + 75, current_offset( ).y - 2.0f, current_offset( ).x + 260, current_offset( ).y - 2.0f, framework.get( )->get_color( 255, 88, 88, 88 ) );
	//			framework.get( )->text( "ESP Options", current_offset( ).x + 9.0f, current_offset( ).y - 10.0f, framework.get( )->get_color( 255, 88, 88, 88 ), 10, false, font_weight::m_bold, true );

	//			this->set_position( uemath::fvector2d{ 265.f, 85.f } );
	//			this->check_box( "Box", &g_vars.get( )->visuals.box );

	//			this->set_position( uemath::fvector2d{ 265.f, 112.f } );
	//			this->check_box( "Corner", &g_vars.get( )->visuals.corner );

	//			this->set_position( uemath::fvector2d{ 265.f, 139.f } );
	//			this->check_box( "Username", &g_vars.get( )->visuals.username );

	//			this->set_position( uemath::fvector2d{ 265.f, 166.f } );
	//			this->check_box( "Distance", &g_vars.get( )->visuals.distance );

	//			this->set_position( uemath::fvector2d{ 265.f, 193.f } );
	//			this->check_box( "Snapline", &g_vars.get( )->visuals.snapline );

	//			this->set_position( uemath::fvector2d{ 265.f, 220.f } );
	//			this->check_box( "Weapon", &g_vars.get( )->visuals.weapon );

	//			this->set_position( uemath::fvector2d{ 265.f, 247.f } ); // +27
	//			this->check_box( "Skeleton", &g_vars.get( )->visuals.skeleton );

	//			this->set_position( uemath::fvector2d{ 265.f, 274.f } );
	//			this->check_box( "Eye Tracer", &g_vars.get( )->visuals.view_angle );

	//			this->set_position( uemath::fvector2d{ 265.f, 344.f } ); // 50 before 297
	//			framework.get( )->line( current_offset( ).x + 85, current_offset( ).y - 2.0f, current_offset( ).x + 260, current_offset( ).y - 2.0f, framework.get( )->get_color( 255, 88, 88, 88 ) );
	//			framework.get( )->text( "ESP Properties", current_offset( ).x + 9.0f, current_offset( ).y - 10.0f, framework.get( )->get_color( 255, 88, 88, 88 ), 10, false, font_weight::m_bold, true );

	//			this->set_position( uemath::fvector2d{ 275.f, 377.f } ); // 33 before 330
	//			this->slider( "Distance Limit", &g_vars.get( )->misc.maximum_distance, 10.f, 250.0f );
	//		}

	//		this->set_position( uemath::fvector2d{ 562.f, 65.f } );

	//		this->add_widget( uemath::fvector2d( 250.0f, 520.0f ) );
	//		{
	//			this->set_position( uemath::fvector2d{ 570.0f, 82.f } );

	//			std::string preview;

	//			if ( g_vars.get( )->visuals.username )
	//				preview += "AI";

	//			if ( g_vars.get( )->visuals.distance )
	//				preview +=  " (10m)";

	//			framework.get( )->text( preview.c_str( ), current_offset( ).x + 115.0f, current_offset( ).y + 24.0f, framework.get( )->get_color( 255, 163, 163, 163 ), 12, true, font_weight::m_bold );
	//			
	//			this->set_position( uemath::fvector2d{ 570.0f + 88.0f, 82.f + 30.0f } );
	//			this->interactive_rect( uemath::fvector2d{ 55.0f, 55.0f } );

	//			this->set_position( uemath::fvector2d{ 570.0f + 88.0f - 13.0f, 82.f + 90.0f } );
	//			this->interactive_rect( uemath::fvector2d{ 75.0f, 105.0f } );

	//			this->set_position( uemath::fvector2d{ 570.0f + 45.f, 82.f + 90.0f } );
	//			this->interactive_rect( uemath::fvector2d{ 25.0f, 125.0f } );

	//			this->set_position( uemath::fvector2d{ 604.0f + 121.f, 82.f + 90.0f } );
	//			this->interactive_rect( uemath::fvector2d{ 25.0f, 125.0f } );

	//			this->set_position( uemath::fvector2d{ 570.f + 75.0f, 82.f + 200.0f } );
	//			this->interactive_rect( uemath::fvector2d{ 35.0f, 100.0f } );

	//			this->set_position( uemath::fvector2d{ 570.f + 115.0f, 82.f + 200.0f } );
	//			this->interactive_rect( uemath::fvector2d{ 35.0f, 100.0f } );

	//			std::string BottomPreview;
	//			if ( g_vars.get( )->visuals.weapon )
	//				BottomPreview += "Havoc Pump Shotgun";

	//			framework.get( )->text( BottomPreview.c_str( ), current_offset( ).x, current_offset( ).y + 125.0f, framework.get( )->get_color( 255, 163, 163, 163 ), 12, true, font_weight::m_bold );
	//			
	//			framework.get( )->text( "Rendering takes up a large chunk of usage,\nbecareful with what options you choose.\nUse performance mode found in\nMiscellaneous settings.", current_offset( ).x - 108.0f, current_offset( ).y + 178.0f, framework.get( )->get_color( 255, 163, 163, 163 ), 11, false, font_weight::m_normal, true );
	//			framework.get( )->rect( current_offset( ).x - 115.0f, current_offset( ).y + 175.0f , 230.f, 115.f, framework.get( )->get_color( 255, 163, 163, 163 ), true, 5, 5 );
	//			framework.get( )->filled_rect( current_offset( ).x + 58.0f, current_offset( ).y + 232.0f, 50.f, 50.f, framework.get( )->get_color( 255, 88, 88, 88 ), true, 5, 5 );
	//			framework.get( )->rect( current_offset( ).x + 58.0f, current_offset( ).y + 232.0f, 50.f, 50.f, framework.get( )->get_color( 255, 163, 163, 163 ), true, 5, 5 );
	//			framework.get( )->text( "!", current_offset( ).x + 78.0f, current_offset( ).y + 232.0f, framework.get( )->get_color( 255, 163, 163, 163 ), 36, false, font_weight::m_bold, true );
	//		}
	//	}

	//	} );

	//this->add_page( 1, [ & ]( ) {

	//	this->begin_parent( "Aimbot", uemath::fvector2d( 0, 0 ), uemath::fvector2d( 750, 600 ) );
	//	{
	//		this->set_position( uemath::fvector2d{ 265.f, 65.f } );

	//		this->add_widget( uemath::fvector2d( 280.0f, 520.0f ) );
	//		{
	//			// HEADER/PIN
	//			this->set_position( uemath::fvector2d{ 265.f, 82.f } );
	//			framework.get( )->line( current_offset( ).x + 90, current_offset( ).y - 2.0f, current_offset( ).x + 260, current_offset( ).y - 2.0f, framework.get( )->get_color( 255, 88, 88, 88 ) );
	//			framework.get( )->text( "Aimbot Options", current_offset( ).x + 9.0f, current_offset( ).y - 10.0f, framework.get( )->get_color( 255, 88, 88, 88 ), 10, false, font_weight::m_bold, true );

	//			this->set_position( uemath::fvector2d{ 265.f, 85.f } );
	//			this->check_box( "Aimbot", &g_vars.get( )->aim.enabled );

	//			if ( g_vars.get( )->aim.enabled )
	//			{
	//				this->set_position( uemath::fvector2d{ 350.f, 95.f } );
	//				this->hotkey( &g_vars.get( )->aim.aim_keycode );

	//				this->set_position( uemath::fvector2d{ 265.f, 112.f } );
	//				this->check_box( "FOV Circle", &g_vars.get( )->misc.fov );

	//				this->set_position( uemath::fvector2d{ 275.f, 175.f } );
	//				this->slider( "FOV Radius", &g_vars.get( )->aim.fov_c, 0.f, 350.0f );

	//				this->set_position( uemath::fvector2d{ 275.f, 212.f } );
	//				this->slider( "Smoothing", &g_vars.get( )->aim.smooth, 0.f, 30.0f );

	//				this->set_position( uemath::fvector2d{ 275.f, 255.f } );
	//				this->slider( "Accuracy Rate", &g_vars.get( )->aim.accuracy_rate, 0.f, 10.0f );
	//				
	//				this->set_position( uemath::fvector2d{ 265.f, 265.f } );
	//				this->check_box( "Ignore Team", &g_vars.get( )->aim.ignore_team );

	//				this->set_position( uemath::fvector2d{ 265.f, 293.f } );
	//				this->check_box( "Ignore Knocked", &g_vars.get( )->aim.ignore_knocked );

	//				this->set_position( uemath::fvector2d{ 265.f, 320.f } );
	//				this->check_box( "Ignore Invisible", &g_vars.get( )->aim.ignore_invisible );

	//				this->set_position( uemath::fvector2d{ 265.f, 370.f } );
	//				
	//				framework.get( )->line( current_offset( ).x + 95, current_offset( ).y - 2.0f, current_offset( ).x + 270, current_offset( ).y - 2.0f, framework.get( )->get_color( 255, 88, 88, 88 ) );
	//				framework.get( )->text( "Weapon Configs", current_offset( ).x + 9.0f, current_offset( ).y - 10.0f, framework.get( )->get_color( 255, 88, 88, 88 ), 10, false, font_weight::m_bold, true );


	//				this->set_position( uemath::fvector2d{ 275.f, 380.f } );

	//				static int weapon_tab = 0;

	//				if ( this->button( "SMG", uemath::fvector2d{ 40.f, 25.f } ) )
	//				{
	//					weapon_tab = 0;
	//				}

	//				this->set_position( uemath::fvector2d{ 319.f, 380.f } );
	//				if ( this->button( "AR", uemath::fvector2d{ 30.f, 25.f } ) )
	//				{
	//					weapon_tab = 1;
	//				}

	//				this->set_position( uemath::fvector2d{ 353.f, 380.f } );
	//				if ( this->button( "Shotgun", uemath::fvector2d{ 60.f, 25.f } ) )
	//				{
	//					weapon_tab = 2;
	//				}


	//				this->set_position( uemath::fvector2d{ 417.f, 380.f } );
	//				if ( this->button( "Pistol", uemath::fvector2d{ 40.f, 25.f } ) )
	//				{
	//					weapon_tab = 3;
	//				}

	//				this->set_position( uemath::fvector2d{ 461.f, 380.f } );
	//				if ( this->button( "Sniper", uemath::fvector2d{ 73.f, 25.f } ) )
	//				{
	//					weapon_tab = 4;
	//				}

	//				this->set_position( uemath::fvector2d{ 275.f, 415.f } );

	//				framework.get( )->rect( current_offset( ).x, current_offset( ).y, 260.f, 155.f, framework.get( )->get_color( 255, 88, 88, 88 ), true, 5, 5 );
	//				
	//				const auto draw_weapon_tab = [ & ]( bool* enabled, bool* prediction, float* weapon_fov, bool no_prediction = false ) -> void 
	//				{
	//					this->set_position( uemath::fvector2d{ 275.f, 415.f } );
	//					this->check_box( "Allow Aimbot", enabled );

	//					this->set_position( uemath::fvector2d{ 275.f, 445.f } );

	//					if ( !no_prediction )
	//					{
	//						this->check_box( "Prediction", prediction );
	//					}
	//					else
	//					{
	//						this->set_position( uemath::fvector2d{ 288.f, 475.f } );
	//						this->slider( "Weapon FOV", weapon_fov, 0.f, 350.0f );
	//					}

	//					if ( !no_prediction )
	//					{
	//						this->set_position( uemath::fvector2d{ 288.f, 505.f } );
	//						this->slider( "Weapon FOV", weapon_fov, 0.f, 350.0f );
	//					}
	//				};

	//				switch ( weapon_tab )
	//				{
	//					case 0:
	//					{
	//						draw_weapon_tab( 
	//							&g_vars.get( )->weapon_config.smg.enabled,
	//							&g_vars.get( )->weapon_config.smg.prediction,
	//							&g_vars.get( )->weapon_config.smg.weapon_fov
	//						);
	//						break;
	//					}

	//					case 1:
	//					{
	//						draw_weapon_tab(
	//							&g_vars.get( )->weapon_config.ars.enabled,
	//							&g_vars.get( )->weapon_config.ars.prediction,
	//							&g_vars.get( )->weapon_config.ars.weapon_fov
	//						);
	//						break;
	//					}

	//					case 2:
	//					{
	//						draw_weapon_tab(
	//							&g_vars.get( )->weapon_config.shotgun.enabled,
	//							0,
	//							&g_vars.get( )->weapon_config.shotgun.weapon_fov,
	//							true
	//						);
	//						break;
	//					}

	//					case 3:
	//					{
	//						draw_weapon_tab(
	//							&g_vars.get( )->weapon_config.pistol.enabled,
	//							&g_vars.get( )->weapon_config.pistol.prediction,
	//							&g_vars.get( )->weapon_config.pistol.weapon_fov
	//						);
	//						break;
	//					}

	//					case 4:
	//					{
	//						draw_weapon_tab(
	//							&g_vars.get( )->weapon_config.snipers.enabled,
	//							&g_vars.get( )->weapon_config.snipers.prediction,
	//							&g_vars.get( )->weapon_config.snipers.weapon_fov
	//						);
	//						break;
	//					}
	//				}

	//			}
	//		}

	//		this->set_position( uemath::fvector2d{ 562.f, 65.f } );
	//		this->add_widget( uemath::fvector2d( 250.0f, 520.0f ) );
	//		{
	//			this->set_position( uemath::fvector2d{ 570.0f, 82.f } );

	//			// head
	//			this->set_position( uemath::fvector2d{ 570.0f + 88.0f, 82.f + 30.0f } );
	//			if ( this->interactive_rect( uemath::fvector2d{ 55.0f, 55.0f } ) || g_vars.get( )->aim.target_bone == 109)
	//			{
	//				g_vars.get( )->aim.target_bone = 109;
	//				framework.get( )->rect( this->current_offset( ).x, this->current_offset( ).y, 55.0f, 55.0f, framework.get( )->get_color( 100, 239, 68, 68 ), true, 2, 2 );
	//			}

	//			// chest
	//			this->set_position( uemath::fvector2d{ 570.0f + 88.0f - 13.0f, 82.f + 90.0f } );
	//			this->interactive_rect( uemath::fvector2d{ 75.0f, 115.0f }, true );

	//			// rib 1
	//			this->set_position( uemath::fvector2d{ 570.0f + 81.0f, 82.f + 97.0f } );
	//			if ( this->interactive_rect( uemath::fvector2d{ 62.0f, 30.0f } ) || g_vars.get( )->aim.target_bone == 7 )
	//			{
	//				g_vars.get( )->aim.target_bone = 7;
	//				framework.get( )->rect( this->current_offset( ).x, this->current_offset( ).y, 62.0f, 30.0f, framework.get( )->get_color( 100, 239, 68, 68 ), true, 2, 2 );
	//			}

	//			// rib 2
	//			this->set_position( uemath::fvector2d{ 570.0f + 81.0f, 82.f + 132.0f } );
	//			if ( this->interactive_rect( uemath::fvector2d{ 62.0f, 30.0f } ) || g_vars.get( )->aim.target_bone == 5 )
	//			{
	//				g_vars.get( )->aim.target_bone = 5;
	//				framework.get( )->rect( this->current_offset( ).x, this->current_offset( ).y, 62.0f, 30.0f, framework.get( )->get_color( 100, 239, 68, 68 ), true, 2, 2 );
	//			}

	//			// rib 3
	//			this->set_position( uemath::fvector2d{ 570.0f + 81.0f, 82.f + 167.0f } );
	//			if ( this->interactive_rect( uemath::fvector2d{ 62.0f, 30.0f } ) || g_vars.get( )->aim.target_bone == 2 )
	//			{
	//				g_vars.get( )->aim.target_bone = 2;
	//				framework.get( )->rect( this->current_offset( ).x, this->current_offset( ).y, 62.0f, 30.0f, framework.get( )->get_color( 100, 239, 68, 68 ), true, 2, 2 );
	//			}

	//			// left arm
	//			this->set_position( uemath::fvector2d{ 570.0f + 45.f, 82.f + 90.0f } );
	//			if ( this->interactive_rect( uemath::fvector2d{ 25.0f, 125.0f } ) || g_vars.get( )->aim.target_bone == 10 )
	//			{
	//				g_vars.get( )->aim.target_bone = 10;
	//				framework.get( )->rect( this->current_offset( ).x, this->current_offset( ).y, 25.0f, 125.0f, framework.get( )->get_color( 100, 239, 68, 68 ), true, 2, 2 );
	//			}

	//			// right arm
	//			this->set_position( uemath::fvector2d{ 604.0f + 121.f, 82.f + 90.0f } );
	//			if ( this->interactive_rect( uemath::fvector2d{ 25.0f, 125.0f } ) || g_vars.get( )->aim.target_bone == 39 )
	//			{
	//				g_vars.get( )->aim.target_bone = 39;
	//				framework.get( )->rect( this->current_offset( ).x, this->current_offset( ).y, 25.0f, 125.0f, framework.get( )->get_color( 100, 239, 68, 68 ), true, 2, 2 );
	//			}

	//			// left leg
	//			this->set_position( uemath::fvector2d{ 570.f + 75.0f, 82.f + 210.0f } );
	//			if ( this->interactive_rect( uemath::fvector2d{ 35.0f, 100.0f } ) || g_vars.get( )->aim.target_bone == 77 )
	//			{
	//				g_vars.get( )->aim.target_bone = 77;
	//				framework.get( )->rect( this->current_offset( ).x, this->current_offset( ).y, 35.0f, 100.0f, framework.get( )->get_color( 100, 239, 68, 68 ), true, 2, 2 );
	//			}

	//			// right left
	//			this->set_position( uemath::fvector2d{ 570.f + 115.0f, 82.f + 210.0f } );
	//			if ( this->interactive_rect( uemath::fvector2d{ 35.0f, 100.0f } ) || g_vars.get( )->aim.target_bone == 84 )
	//			{
	//				g_vars.get( )->aim.target_bone = 84;
	//				framework.get( )->rect( this->current_offset( ).x, this->current_offset( ).y, 35.0f, 100.0f, framework.get( )->get_color( 100, 239, 68, 68 ), true, 2, 2 );
	//			}
	//			this->set_position( uemath::fvector2d{ 570.f + 115.0f, 82.f + 200.0f } );

	//			framework.get( )->text( "Having too many headshots or too much \ndamage may indicate the anticheat \nthat you're exploiting. Be sure to always\nbehave and play legit, or you may risk an \nexploit ban.", current_offset( ).x - 108.0f, current_offset( ).y + 178.0f, framework.get( )->get_color( 255, 163, 163, 163 ), 11, false, font_weight::m_normal, true );
	//			framework.get( )->rect( current_offset( ).x - 115.0f, current_offset( ).y + 175.0f, 230.f, 115.f, framework.get( )->get_color( 255, 163, 163, 163 ), true, 5, 5 );

	//			this->set_position( uemath::fvector2d{ 570.f + 115.0f, 82.f + 350.0f } );
	//			framework.get( )->text( "* Certain skins may have different bones", current_offset( ).x, current_offset( ).y, framework.get( )->get_color( 255, 163, 163, 163 ), 11, true, font_weight::m_bold, true );

	//		}

	//	}

	//	} );

	//this->add_page( 2, [ & ]( ) {

	//	this->begin_parent( "Exploit", uemath::fvector2d( 0, 0 ), uemath::fvector2d( 750, 600 ) );
	//	{
	//		this->set_position( uemath::fvector2d{ 265.f, 65.f } );
	//		this->add_widget( uemath::fvector2d( 280.0f, 520.0f ) );
	//		{
	//			// HEADER/PIN
	//			this->set_position( uemath::fvector2d{ 265.f, 82.f } );
	//			framework.get( )->line( current_offset( ).x + 80, current_offset( ).y - 2.0f, current_offset( ).x + 260, current_offset( ).y - 2.0f, framework.get( )->get_color( 255, 88, 88, 88 ) );
	//			framework.get( )->text( "Exploit Options", current_offset( ).x + 9.0f, current_offset( ).y - 10.0f, framework.get( )->get_color( 255, 88, 88, 88 ), 10, false, font_weight::m_bold, true );
	//		}
	//		this->set_position( uemath::fvector2d{ 265.f, 85.f } );
	//		this->check_box( "No Recoil", &g_vars.get( )->exploits.no_recoil );

	//		this->set_position( uemath::fvector2d{ 265.f, 112.f } );
	//		this->check_box( "No Spread", &g_vars.get( )->exploits.no_spread );

	//		this->set_position( uemath::fvector2d{ 265.f, 112.f + 27.f } );
	//		this->check_box( "First Person", &g_vars.get( )->exploits.first_person );

	//		this->set_position( uemath::fvector2d{ 265.f, 112.f + 27.f + 27.f } );
	//		this->check_box( "Instant Weapon Animation", &g_vars.get( )->exploits.instant_weapon_animation );

	//		this->set_position( uemath::fvector2d{ 265.f, 112.f + 27.f + 27.f + 27.f } );
	//		this->check_box( "No Sprint To Shoot Cooldown", &g_vars.get( )->exploits.no_sprint_to_shoot_cooldown );

	//		this->set_position( uemath::fvector2d{ 562.f, 65.f } );
	//		this->add_widget( uemath::fvector2d( 250.0f, 520.0f ) );
	//	}

	//} );

	//this->begin( uemath::fvector2d( 100, 100 ), uemath::fvector2d( 830, 600 ) );
	//{
	//	// nav bar

	//	auto sidebar_length = uemath::fvector2d( 250.0f, 600.0f );

	//	framework.get( )->filled_rect( position.x, position.y, sidebar_length.x, sidebar_length.y, this->color_menu_bar, true, 5, 5 );

	//	uemath::flinearcolor border_color = framework.get( )->get_color( 255, 38, 38, 38 );

	//	framework.get( )->line( position.x + 250.0f, position.y + 50, position.x + 830.0f, position.y + 50, border_color );
	//	framework.get( )->line( position.x + sidebar_length.x, position.y, position.x + sidebar_length.x, position.y + sidebar_length.y, border_color );

	//	framework.get( )->icon( icon_holder::m_logo_first, position.x + 13.0f, position.y + 9.0f, framework.get( )->get_color( 255, 239, 68, 68 ), 26.0f );
	//	framework.get( )->icon( icon_holder::m_logo_second, position.x + 15.0f, position.y + 10.0f, framework.get( )->get_color( 255, 255, 255, 255 ), 23.0f );
	//	
	//	framework.get( )->text( "OXEGEN", position.x + 47.0f, position.y + 11.0f, framework.get( )->get_color( 255, 255, 255, 255 ), 20, false, font_weight::m_medium, true );
	//	framework.get( )->text( "v3.0.31.53 Fortnite", position.x + 48.0f, position.y + 36.0f, framework.get( )->get_color( 255, 255, 255, 255 ), 10.0f, false, font_weight::m_bold, true );

	//	this->set_position( uemath::fvector2d{ 10.f, 40.0f } );

	//	for ( auto i = 0; i < m_tab.size( ); i++ ) {

	//		switch ( m_tab[i].m_num ) {
	//		case 0:
	//		{
	//			this->tab( icon_holder::m_eye_icon, m_tab[i].m_label, m_tab[i].m_num, uemath::fvector2d( 62, 15 ) );
	//			break;
	//		}

	//		case 1:
	//		{
	//			this->tab( icon_holder::m_crosshair_icon, m_tab[i].m_label, m_tab[i].m_num, uemath::fvector2d( 62, 25 ) );
	//			break;
	//		}

	//		case 2:
	//		{
	//			this->tab( icon_holder::m_box_icon, m_tab[i].m_label, m_tab[i].m_num, uemath::fvector2d( 62, 29 ) );
	//			break;
	//		}

	//		case 3:
	//		{
	//			this->tab( icon_holder::m_sparkle_icon, m_tab[i].m_label, m_tab[i].m_num, uemath::fvector2d( 62, 31 ) );
	//			break;
	//		}

	//		case 4:
	//		{
	//			this->set_position( uemath::fvector2d{ 10.f, 200.0f } );
	//			framework.get( )->text( "SETTINGS", position.x + 18.f, position.y + 245.0f, framework.get( )->get_color( 255, 88, 88, 88 ), 10.0f, false, 1, true );

	//			this->tab( icon_holder::m_pallet_icon, m_tab[i].m_label, m_tab[i].m_num, uemath::fvector2d( 62, 41 ) );
	//			break;
	//		}

	//		case 5:
	//		{
	//			this->tab( icon_holder::m_gear_icon, m_tab[i].m_label, m_tab[i].m_num, uemath::fvector2d( 62, 36 ) );
	//			break;
	//		}

	//		default:
	//			break;
	//		}
	//	}

	//	this->render_page( );

	//}

}

auto m_interface::c_interface::add_page(
	int tab, std::function< void( ) > code ) -> void {
	this->m_tab[tab].page = code;
}

auto m_interface::c_interface::render_page( ) -> void {
	if ( this->m_tab[current_page].page == nullptr )
		return;

	this->m_tab[current_page].page( );
}

auto m_interface::c_interface::set_position(
	uemath::fvector2d value ) -> void {

	this->offset = value;
}

auto m_interface::c_interface::get_cursor( ) -> uemath::fvector2d {

	POINT CursorPoint = {};

	GetCursorPos( &CursorPoint );

	return uemath::fvector2d( double( CursorPoint.x ), double( CursorPoint.y ) );
}

auto m_interface::c_interface::handler( ) -> void {
	static bool LeftMouseAlreadyDown = false;
	this->LeftMouseDown = GetAsyncKeyState( 0x1 );

	if ( this->LeftMouseDown )
	{
		if ( LeftMouseAlreadyDown )
		{
			this->LeftMouseClicked = false;
		}
		else
		{
			this->LeftMouseClicked = true;
		}

		LeftMouseAlreadyDown = true;
	}
	else
	{
		this->LeftMouseClicked = false;
		LeftMouseAlreadyDown = false;
	}
}

bool m_interface::c_interface::is_hovered( uemath::fvector2d Start, uemath::fvector2d Size ) {

	auto cursor_pos = get_cursor( );

	if ( cursor_pos.x > Start.x && cursor_pos.y > Start.y )
	{
		if ( cursor_pos.x < Start.x + Size.x && cursor_pos.y < Start.y + Size.y )
		{
			return true;
		}
	}

	return false;
}

auto m_interface::c_interface::draw_frames( ) -> void {

}

void m_interface::c_interface::slider( std::string Title, float* Option, float Min, float Max ) {

	//auto Current = uemath::fvector2d( this->position.x + offset.x, this->position.y + offset.y );
	//auto slider_size = uemath::fvector2d{ 170, 5 };
	//auto padding = uemath::fvector2d{ 10, 15 };

	//bool Hovered = this->is_hovered( uemath::fvector2d{ Current.x, Current.y + slider_size.y + padding.y - 34 }, uemath::fvector2d{ slider_size.x, slider_size.y + 30 } );
	//bool Pressed = Hovered && this->LeftMouseDown;

	//if ( Pressed ) {
	//	auto cursorPos = get_cursor( );
	//	*Option = ( ( cursorPos.x - Current.x ) / ( slider_size.x - 5.0f ) ) * ( Max - Min ) + Min;

	//	// Clamp the value to ensure it stays within the Min and Max range.
	//	if ( *Option < Min ) *Option = Min;
	//	if ( *Option > Max ) *Option = Max;
	//}

	//// Render the background of the slider based on hover state
	//if ( Hovered ) {
	//	framework.get( )->filled_rect( Current.x, Current.y + slider_size.y, slider_size.x - 5.0f, slider_size.y, framework.get( )->get_color( 255, 31, 30, 43 ) );
	//	hover_element = true;
	//}
	//else {
	//	framework.get( )->filled_rect( Current.x, Current.y + slider_size.y, slider_size.x - 5.0f, slider_size.y, framework.get( )->get_color( 255, 23, 22, 31 ) );
	//}

	//// Render the text label for the slider
	//auto text_position = uemath::fvector2d{ Current.x + 0.0f, Current.y - 20.0f };
	//framework.get( )->text( Title.c_str( ), text_position.x, text_position.y, framework.get( )->get_color( 255, 163, 163, 163 ), 11, false, font_weight::m_bold, true );

	//float calc = ( *Option - Min ) / ( Max - Min ) * ( slider_size.x - 5.0f ); // Subtract the width of the red box from the slider width.
	//// Ensure that 'calc' does not exceed the graphical bounds of the slider
	//float calc_max = slider_size.x - 5; // 5 is the offset to prevent overlap with the text
	//if ( calc > calc_max ) calc = calc_max;

	//// Render the fill for the slider
	//framework.get( )->filled_rect( Current.x, Current.y + slider_size.y, calc, slider_size.y, framework.get( )->get_color( 255, 239, 68, 68 ) );

	//// Render the draggable circle for the slider
	//framework.get( )->circle( Current.x + calc, Current.y + slider_size.y + 2.66f, 7.0f, framework.get( )->get_color( 255, 255, 255, 255 ), true, true );

	//// Render the text for the slider's current value
	//auto text_layout = std::format( "{:.0f}", *Option );
	//auto value_position = uemath::fvector2d{ Current.x + slider_size.x - 20.0f, Current.y - 3.0f };
	//framework.get( )->text( text_layout.c_str( ), value_position.x, value_position.y, framework.get( )->get_color( 255, 163, 163, 163 ), 12, true, font_weight::m_normal, true );

	//// Increment the y offset for the next UI element
	//this->offset.y += slider_size.y + 10;
}


bool m_interface::c_interface::tab( int icon_id, std::string title, int tab_id, uemath::fvector2d size ) {

	//auto padding = uemath::fvector2d{ 25, 10 };
	//auto Current = uemath::fvector2d( this->position.x + this->offset.x, this->position.y + this->offset.y );

	//uemath::fvector2d bg_size = { 222.0f, 34.0f };

	//uemath::fvector2d clickable_area_top_left = { Current.x - 12.0f, Current.y - 2.0f + size.y / 0.5f };

	//auto is_hovered = this->is_hovered( clickable_area_top_left, bg_size );

	//auto selected = current_page == tab_id;
	//auto Clicked = is_hovered && this->LeftMouseClicked;

	//auto text_pos = uemath::fvector2d{ Current.x + size.x / 4.0f, Current.y + size.y / 0.6f };

	//uemath::flinearcolor Textcolor;
	//uemath::flinearcolor Bgcolor;

	//if ( selected )
	//{
	//	Textcolor = framework.get( )->get_color( 255, 250, 250, 250 );
	//	Bgcolor = framework.get( )->get_color( 204, 38, 38, 38 );
	//}

	//else if ( is_hovered )
	//{
	//	if ( Clicked ) {

	//		current_page = tab_id;
	//	}

	//	Textcolor = framework.get( )->get_color( 255, 250, 250, 250 );
	//	Bgcolor = framework.get( )->get_color( 204, 38, 38, 38 );
	//	hover_element = true;
	//}
	//else {
	//	Textcolor = framework.get( )->get_color( 255, 163, 163, 163 );
	//	Bgcolor = framework.get( )->get_color( 0, 0, 0, 0 );
	//}

	////text
	//framework.get( )->filled_rect( text_pos.x - 12.0f, text_pos.y - 2.0f, 222.0f, 34.0f, Bgcolor, true, 5, 5 );
	//framework.get( )->text( title.c_str( ), text_pos.x + 19.0f, text_pos.y + 5.0f, Textcolor, 14, false, font_weight::m_medium, true );
	//framework.get( )->icon( icon_id, text_pos.x - 4.0f, text_pos.y + 7.0f, framework.get( )->get_color( 255, 239, 68, 68 ), 14.0f );

	//this->offset.y += size.y + padding.y;

	return true;
}

bool m_interface::c_interface::button( std::string Title, uemath::fvector2d size ) {

	const auto Current = uemath::fvector2d( this->position.x + this->offset.x, this->position.y + this->offset.y );

	bool is_hovered = this->is_hovered( Current, size );
	bool Clicked = is_hovered && this->LeftMouseClicked;

	uemath::flinearcolor color = is_hovered ? framework->get_color( 255, 100, 100, 100 ) : framework->get_color( 255, 88, 88, 88 );

	if ( is_hovered )
	{
		hover_element = true;
	}

	//framework.get( )->filled_rect( Current.x, Current.y, size.x, size.y, color, false, 0, 0 );

	//Outline
	framework->rect( Current.x, Current.y, size.x, size.y, color, true, 5, 5);

	//Text
	auto text_pos = uemath::fvector2d{ Current.x + size.x / 2, Current.y + size.y / 1.25 };
	//framework->text( Title.c_str( ), text_pos.x, text_pos.y, framework->get_color( 255, 205, 204, 206 ), 12, true, font_weight::m_bold, true );

	this->offset.y += size.y + this->ItemSpacing;
	//this->offset.x += size.x + 15;

	return Clicked;
}

void m_interface::c_interface::check_box( std::string Title, bool* Option ) {

	//auto padding = uemath::fvector2d{ 10, 10 };
	//auto Current = uemath::fvector2d( this->position.x + padding.x + offset.x, this->position.y + padding.y + offset.y );
	//auto size = uemath::fvector2d( 20, 20 );

	//bool is_hovered = this->is_hovered( Current, size );
	//bool Clicked = is_hovered && this->LeftMouseClicked;

	////Background
	//if ( is_hovered ) {
	//	framework.get( )->rect( Current.x, Current.y, size.x, size.y, framework.get( )->get_color( 255, 88, 88, 88 ), true, 4, 4 );
	//	framework.get( )->filled_rect( Current.x, Current.y, size.x, size.y, this->color_checkbox_hovered, true, 4, 4 );
	//}
	//else {
	//	framework.get( )->rect( Current.x, Current.y, size.x, size.y, framework.get( )->get_color( 255, 88, 88, 88 ), true, 4, 4 );
	//	framework.get( )->filled_rect( Current.x, Current.y, size.x, size.y, this->color_checkbox_bg, true, 4, 4 );
	//}

	//// checkbox
	//if ( *Option )
	//{
	//	framework.get( )->filled_rect( Current.x + 3, Current.y + 3, size.x - 6, size.y - 6, this->color_checkbox_active, true, 3, 3 );
	//}

	//auto text_position = uemath::fvector2d{ Current.x + size.x + 7.0f, Current.y + size.y - 19 };

	//framework.get( )->text( Title.c_str( ), text_position.x, text_position.y, framework.get( )->get_color( 255, 163, 163, 163 ), 12, false, font_weight::m_normal, true );

	//if ( is_hovered && Clicked )
	//{
	//	*Option = !*Option;
	//}

	//this->offset.y += size.y + 2 + this->ItemSpacing;
}

auto m_interface::c_interface::begin_parent(
	const std::string& title,
	uemath::fvector2d start,
	uemath::fvector2d size ) -> void
{
	// 400, 450

	////m_render.get( )->filled_rect( position.x + 50, position.y + 85, size.x - 100, size.y - 120, m_render.get( )->get_color( 255, 16, 14, 24 ), true, 5, 5 );
	//framework.get( )->filled_rect( position.x + 48, position.y + 85, size.x, size.y, framework.get( )->get_color( 255, 16, 14, 24 ), true, 5, 5 );

	////m_render.get( )->line( position.x + 50, position.y + 130, position.x + size.x, position.y + 130, m_render.get( )->get_color( 255, 23, 21, 30 ) );
	//framework.get( )->line( position.x + 50, position.y + 130, position.x + size.x * 1.16, position.y + 130, framework.get( )->get_color( 255, 23, 21, 30 ) );

	////m_render.get( )->text( "Aimbot", position.x + size.x / 6, position.y + 100, m_render.get( )->get_color( 255, 210, 209, 210 ), 14, false, true );
	//framework.get( )->text( title.c_str( ), position.x + size.x / 4.5, position.y + 100, framework.get( )->get_color( 255, 210, 209, 210 ), 14, false, true );

}

void m_interface::c_interface::begin( uemath::fvector2d start, uemath::fvector2d size ) {

	//if ( !this->initialized ) {

	//	this->position = start;
	//	this->ItemSpacing = 6;
	//	this->size = size;

	//	this->initialized = true;
	//}

	//this->handler( );

	//auto is_hovered = this->is_hovered( this->position, this->size );

	////Drag
	//if ( hover_element && GetAsyncKeyState( 0x1 ) )
	//{

	//}
	//else if ( ( is_hovered || drag_position.x != 0 ) && !hover_element )
	//{
	//	if ( this->LeftMouseDown )
	//	{
	//		auto cursorPos = get_cursor( );

	//		cursorPos.x -= size.x;
	//		cursorPos.y -= size.y;

	//		if ( drag_position.x == 0 )
	//		{
	//			drag_position.x = ( cursorPos.x - position.x );
	//			drag_position.y = ( cursorPos.y - position.y );
	//		}
	//		position.x = cursorPos.x - drag_position.x;
	//		position.y = cursorPos.y - drag_position.y;
	//	}
	//	else
	//	{
	//		drag_position = uemath::fvector2d{ 0, 0 };
	//	}
	//}
	//else
	//{
	//	hover_element = false;
	//}

	//this->offset = uemath::fvector2d( 0, 0 );

	//framework.get( )->rect( position.x, position.y , size.x, size.y, framework.get( )->get_color( 255, 88, 87, 86 ), true,
	//	5,
	//	5 );

	//framework.get( )->filled_rect(
	//	position.x,
	//	position.y,
	//	size.x,
	//	size.y,
	//	this->color_menu_bg,
	//	true,
	//	5,
	//	5
	//);


}