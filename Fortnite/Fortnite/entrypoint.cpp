#pragma once
#include "core/inc.hpp"

// we will convert to a dll
auto main( ) -> std::int32_t 
{
	auto status = g_utils->attach_console( );
	if ( !status ) { return 0; }

	status = vm->attach_vm( L"FortniteClient-Win64-Shipping.exe" );
	if ( !status ) { return 0; }

	status = g_render->setup( L"FortniteClient-Win64-Shipping.exe" );
	if ( !status ) { return 0; }

	std::jthread( [ & ] ( ) -> void { g_entity->tick( ); } ).detach( );
	std::jthread( [ & ] ( ) -> void { g_render->tick( ); } ).detach( );

	return std::cin.get( ) != EOF;
}