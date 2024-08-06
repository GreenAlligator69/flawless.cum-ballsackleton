#pragma once
#include "../../core/inc.hpp"

auto c_ipc::insert_object(
	const void* source, std::size_t size ) -> void
{

	//if ( this->offset + size > 0xF4240 ) {
	//	LOG( hash_str( "overflow detected.\n" ) );
	//	this->offset = 0;
	//}

	std::memcpy(
		reinterpret_cast< void* >( reinterpret_cast< char* >( this->buffer ) + this->offset ),
		source,
		size );

	// index
	//this->offset += size;
}

auto c_ipc::create_mutex(
	const std::string& module ) -> bool
{
	this->mutex = OpenMutexA(
		0x00100000L, // !synchronize
		false,
		module.c_str( )
	);

	return this->mutex != nullptr;
}

auto c_ipc::map_buffer( ) -> bool
{
	this->buffer = MapViewOfFile(
		this->ipc,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		0xF4240
	);

	return this->buffer != nullptr;
}

auto c_ipc::connect_buffer(
	const std::string& module ) -> bool
{
	this->ipc = OpenFileMappingA(
		FILE_MAP_ALL_ACCESS,
		false,
		module.c_str( )
	);

	return this->ipc != nullptr;
}

auto c_ipc::initialize(
	const std::string& module
) -> bool
{
	const auto a_pid = g_utils->get_process_id( hash_str( L"flawless-gamebar.exe" ) );
	if ( !a_pid ) {
		LOG( hash_str( "invalid widget.\n" ) );
		return false;
	}

	const auto gamebar_sid = g_utils->get_gamebar_sid( a_pid );
	if ( gamebar_sid.empty( ) ) {
		LOG( hash_str( "invalid sid.\n" ) );
		return false;
	}

	const std::string sid(
		gamebar_sid.begin( ),
		gamebar_sid.end( )
	);

	const auto buffer = hash_str( "AppContainerNamedObjects\\" ) + sid + hash_str( "\\" ) + module;

	auto status = this->connect_buffer( buffer.c_str( ) );
	if ( !status )
	{
		LOG( hash_str( "failed to open file.\n" ) );
		return false;
	}

	status = this->map_buffer( );
	if ( !status )
	{
		LOG( hash_str( "failed to map file.\n" ) );
		return false;
	}

	return true;
}