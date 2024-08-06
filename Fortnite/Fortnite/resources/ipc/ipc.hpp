#ifndef IPC_HPP
#define IPC_HPP

class c_ipc {

	HANDLE ipc = nullptr;

public:

	HANDLE mutex = nullptr;

	void* buffer = nullptr;
	std::uint32_t offset = 0;

	ALWAYS_INLINE c_ipc( ) { };

	ALWAYS_INLINE ~c_ipc( ) {

		std::printf( hash_str( " [ipc] -> deconstructor called.\n" ) );
		std::cin.get( );

		if ( buffer ) {
			UnmapViewOfFile( buffer );
			buffer = nullptr;
		}

		if ( ipc ) {
			CloseHandle( ipc );
			ipc = nullptr;
		}

		if ( mutex ) {
			CloseHandle( mutex );
			mutex = nullptr;
		}
	}


	[[nodiscard]] bool initialize( const std::string& module );

	void insert_object( const void* source, std::size_t size );

	template<typename type>
	auto write( std::uintptr_t address, type value ) -> void {

		*reinterpret_cast< type* >( address ) = value;
	}

	template <typename type>
	auto read( std::uintptr_t address ) -> type
	{
		return *reinterpret_cast< type* >( address );
	}

	auto copy( void* src, uint32_t size ) -> bool
	{
		if ( !buffer )
		{
			return false;
		}

		std::memcpy(
			buffer,
			src, 
			size 
		);

		return true;
	}

private:

	bool connect_buffer( const std::string& module );
	bool create_mutex( const std::string& module );
	bool map_buffer( );

}; inline const auto ipc = std::make_unique<c_ipc>( );

#endif