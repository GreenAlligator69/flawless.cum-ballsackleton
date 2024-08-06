#pragma once 
#include "../../core/inc.hpp"

auto c_framework::get_color( std::int8_t r, std::int8_t g, std::int8_t b, std::int8_t a ) -> uemath::flinearcolor {

	return uemath::flinearcolor {
		static_cast< std::int8_t >( a ),
		static_cast< std::int8_t >( r ),
		static_cast< std::int8_t >( g ),
		static_cast< std::int8_t >( b )
	};

}

auto c_framework::crosshair( ) -> void
{
	this->line(
		engine->m_width_2 - 5,
		engine->m_height_2,
		engine->m_width_2 + 5,
		engine->m_height_2,
		this->get_color( 255, 255, 255, 255 )
	);

	this->line(
		engine->m_width_2,
		engine->m_height_2 - 5,
		engine->m_width_2,
		engine->m_height_2 + 5,
		this->get_color( 255, 255, 255, 255 )
	);
}

auto c_framework::fov( ) -> void
{
	this->circle(
		engine->m_width_2, engine->m_height_2,
		g_vars->aim.fov_c,
		this->get_color( 255, 255, 255, 255 ),
		1.f
	);
}

void c_framework::text(
	const std::string& input,
	float x,
	float y,
	uemath::flinearcolor color,
	float fontSize,
	bool center,
	int weight,
	bool menu ) {

}

void c_framework::line( float x1, float y1, float x2, float y2, uemath::flinearcolor color, float stroke ) {

}

void c_framework::bounding_corner( const uemath::fvector& position, const uemath::fvector& size, uemath::flinearcolor color ) {

}

void c_framework::rect(
	float x,
	float y,
	float width,
	float height,
	uemath::flinearcolor color,
	bool rounded,
	float _x,
	float _y ) {

}

void c_framework::filled_rect(
	float x,
	float y,
	float width,
	float height,
	uemath::flinearcolor color,
	bool rounded,
	float _x,
	float _y ) {

}

void c_framework::circle( float x, float y, float radius, uemath::flinearcolor color, float stroke, bool filled ) {

}

bool c_framework::send_cmd( void* data, request code )
{
	if ( !data )
		return false;

	return true;
}

auto c_framework::release( ) -> void {

}

auto c_framework::initializer( ) -> void
{
	if ( !ipc ) {
		std::printf( " [ipc] -> invalid.\n" );
		std::cin.get( );
	}

}

auto c_framework::begin_scene( ) -> void {

}

auto c_framework::end_scene( ) -> void {

}