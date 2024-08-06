#pragma once 
#include "..\inc.hpp"
#include <stack>
#include <concrt.h>

constexpr bool developer = true;

auto render::c_render::setup( 
	const std::wstring& proc_name ) -> bool {
	
	auto handle = ipc->initialize(
		hash_str( "FN_buffer" )
	);

	if ( !handle ) {
		print_error( hash_str( "initialization failed.\n" ), true );
		return false;
	}

	framework->initializer( );

	print_info( hash_str( "gamebar initialized.\n" ) );

	auto m_target_pid = g_utils->get_process_id( proc_name.c_str( ) );
	if ( !m_target_pid ) {
		print_error( hash_str( "failed to get application pid.\n" ), false );
		return false;
	}

	auto w_handle = this->get_window_handle( m_target_pid );
	if ( !w_handle ) {
		print_error( hash_str( "failed to get window handle.\n" ), false );
		return false;
	}

	auto w_name = this->get_window_name( w_handle );
	if ( w_name.empty( ) ) {
		print_error( hash_str( "failed to get window name.\n" ), false );
		return false;
	}

	this->m_pid = std::move( m_target_pid );
	this->m_name = std::move( w_name );
	this->m_window_target = std::move( w_handle );

	auto get_window = this->get_window( );
	if ( !get_window ) {
		LOG( hash_str( "failed to get window info.\n" ) );
		return false;
	}

	print_info( hash_str( "pid: %i\n" ), this->m_pid );
	print_info( hash_str( "window target: %llx\n" ), this->m_window_target );
	print_info( hash_str( "width: %i\n" ), this->m_width );
	print_info( hash_str( "height: %i\n" ), this->m_height );

	return true;
}

auto render::c_render::release_objects( ) -> void
{

}

auto render::c_render::clean_context( ) -> void
{

}

auto render::c_render::get_window( ) -> bool
{
	auto result = GetWindowRect( 
		this->m_window_target, 
		&this->m_rect );
	if ( !result ) {
		return false;
	}

	this->m_width = m_rect.right - m_rect.left;
	this->m_height = m_rect.bottom - m_rect.top;

	this->m_width_2 = m_width / 2;
	this->m_height_2 = m_height / 2;

	engine->m_width = m_rect.right - m_rect.left;
	engine->m_height = m_rect.bottom - m_rect.top;

	engine->m_width_2 = m_width / 2;
	engine->m_height_2 = m_height / 2;

	return true;
}

auto render::c_render::get_window_name(
	HWND window ) -> std::string 
{

	wchar_t title [ 1024 ];
	GetWindowTextW( window, title, 1024 );

	// Convert wide character array to narrow character array
	char title_conver [ 1024 ];
	std::wcstombs( title_conver, title, 1024 );


	return std::string( title_conver );
}

auto render::c_render::get_window_handle(
	std::uint32_t pid ) -> HWND
{
	std::pair<HWND, DWORD> params = { 0, pid };

	auto result = EnumWindows([ ] ( HWND hwnd, LPARAM lParam ) -> int
	{
		auto pParams = (std::pair<HWND, DWORD>*)(lParam);
		
		DWORD processId;
		if ( GetWindowThreadProcessId( hwnd, &processId ) && processId == pParams->second )
		{

			SetLastError( -1 );
			pParams->first = hwnd;
			return false;
		}

		return true;

	}, reinterpret_cast< LPARAM >(&params) );

	if ( !result && GetLastError() == -1 && params.first )
	{
		return params.first;
	}

	return 0;
}

auto render::c_render::get_screen_status( ) -> bool
{
	if ( this->m_window_target == GetForegroundWindow( ) ) {
		return true;
	}

	if ( this->m_window_target == GetActiveWindow( ) ) {
		return true;
	}

	if ( GetActiveWindow( ) == GetForegroundWindow( ) ) {
		return true;
	}

	return false;
}

auto render::c_render::tick( ) -> void
{

	constexpr auto flag = 0x0001;
	constexpr auto wm_quit = 0x0012;

	while (
		this->m_msg.message
		!= wm_quit ) {

		if ( PeekMessageA(
			&this->m_msg,
			this->m_window_target,
			0,
			0,
			flag ) ) {

			TranslateMessage( &this->m_msg );
			DispatchMessageA( &this->m_msg );

		}

		framework->begin_scene( );
		{
			if ( this->get_screen_status( ) )
			{

			/*	if ( g_vars.get( )->misc.menu )
					*/

				if ( g_vars->visuals.esp )
					visual->render( );
			}
		}
		framework->end_scene( );
	}

	framework->release( );
	this->release_objects( );
	this->clean_context( );

}

