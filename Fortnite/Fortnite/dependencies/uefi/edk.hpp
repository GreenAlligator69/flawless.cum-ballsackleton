#include <unordered_set>
#ifndef EDK_HPP
#define EDK_HPP

namespace uefi {

	enum class build_ver {
		win_22h2 = 19045,
		win_21h2 = 19044,
		win_1809 = 17763,
		win_1607 = 14393,
		win_1507 = 10240
	};

	using read_args = struct
	{
		std::uintptr_t address;
		void* buffer;
		std::size_t size;
	};

	class c_interface {

		bool debug = false;

		GUID efi_global_variable_guid = {
			0x8BE4DF61,0x93CA,0x11D2,
			{ 0xAA,0x0D,0x00,0xE0,0x98,0x03,0x2B,0x8C }
		};

		using payload = struct {

			std::uintptr_t rcx;
			std::uintptr_t rdx;
			std::uintptr_t r8;
			std::uintptr_t r9;
			std::uintptr_t rsp;

		};

		//using iat_t = struct {

		//	std::uintptr_t mm_copy_memory;
		//	std::uintptr_t mm_map_space;
		//	std::uintptr_t mm_unmap_space;
		//	std::uintptr_t ps_initial_system_process;
		//	std::uintptr_t ps_get_process_id;
		//	std::uintptr_t mm_physical_ranges;
		//	std::uintptr_t memcpy;

		//};

		std::int32_t m_pid = 0;
		std::uintptr_t m_dtb = 0;

		void* m_eprocess = nullptr;
		void* m_handle = nullptr;

		std::uintptr_t mm_copy_memory;
		std::uintptr_t mm_map_space;
		std::uintptr_t mm_unmap_space;
		std::uintptr_t ps_initial_system_process;
		std::uintptr_t ps_get_process_id;
		std::uintptr_t mm_physical_ranges;
		std::uintptr_t memcpy;

		std::unordered_map<std::uintptr_t, ::pml4e>  pml4e_cache { };
		std::unordered_map<std::uintptr_t, ::pdpte>  pdpte_cache { };
		std::unordered_map<std::uintptr_t, ::pde>    pd_cache { };
		std::unordered_map<std::uintptr_t, ::pte>    pte_cache { };

	public:

		explicit c_interface( );

		// test
		bool batch_read( const std::vector<read_args>& args, ULONG requests );

		[[nodiscard]] bool send_cmd( std::uintptr_t data, void* parameters );
		[[nodiscard]] bool is_dtb_invalid( std::uintptr_t cr3 );
		[[nodiscard]] bool attach_vm( const std::wstring& proc_name );

		[[nodiscard]] const std::uintptr_t get_image_base( const std::uintptr_t e_process );
		[[nodiscard]] const std::uintptr_t get_eprocess( std::uint32_t process_id );
		[[nodiscard]] const std::uint32_t get_process_pid( const std::wstring& proc_name );
		[[nodiscard]] const std::uint16_t get_build_number( );
		[[nodiscard]] std::uintptr_t get_directory_table_base( std::uintptr_t image_base );
		[[nodiscard]] std::uintptr_t invoke_kernel( std::uintptr_t address, std::uintptr_t a1 = 0, std::uintptr_t a2 = 0, std::uintptr_t a3 = 0, std::uintptr_t a4 = 0 );

		[[nodiscard]] const std::uintptr_t get_kernel_export( const std::uintptr_t image_name, const std::string& module_name );
		[[nodiscard]] const std::uintptr_t get_kernel_image( const std::string& module_name );

		template <typename t_invoke>
		[[nodiscard]] t_invoke invoke( std::uintptr_t address, std::uintptr_t a1 = 0, std::uintptr_t a2 = 0, std::uintptr_t a3 = 0, std::uintptr_t a4 = 0 ) {

			this->invoke_kernel(
				address,
				a1,
				a2,
				a3,
				a4
			);

			return *reinterpret_cast< t_invoke* >( &cache_rax );
		}

		// km 
		[[nodiscard]] bool read_physical_km( std::uintptr_t address, void* buffer, std::uintptr_t length );
		[[nodiscard]] bool write_physical_km( std::uintptr_t address, void* buffer, std::uintptr_t length );
		[[nodiscard]] bool read_virtua_km( std::uintptr_t address, void* buffer, std::uintptr_t length );

		// km 
		template <typename t>
		t read_kernel_physical( std::uintptr_t addr ) {
			t response { };

			read_physical_km(
				addr,
				&response,
				sizeof( t )
			);

			return response;
		}

		template <typename t>
		t read_kernel_virtual( std::uintptr_t addr ) {
			t response { };

			read_virtua_km(
				addr,
				&response,
				sizeof( t )
			);

			return response;
		}

		// vm 
		//[[nodiscard]] const std::uintptr_t translate_linear( pt_entries& entries,std::uintptr_t virtual_address,std::uintptr_t directory_base );
		std::uintptr_t translate_linear(
			pt_entries& entries,
			std::uintptr_t virtual_address,
			std::uintptr_t directory_base );
		[[nodiscard]] bool read_physical( const uintptr_t address, void* buffer, const std::uintptr_t size );
		[[nodiscard]] bool write_physical( const uintptr_t address, void* buffer, const size_t size );

		// vm
		template <typename t>
		[[nodiscard]] auto write( const uintptr_t address, t value ) -> bool {
			return write_physical( address, &value, sizeof( t ) );
		}

		template <typename t>
		[[nodiscard]] auto read( std::uintptr_t address ) -> t {
			
			t response { };

			auto result = read_physical(
				address,
				&response,
				sizeof( t )
			);

			return response;
		}

		template <typename t>
		[[nodiscard]] auto read_array( const uintptr_t address, t buffer, size_t size ) -> bool {
			return read_physical( address, buffer, size );
		}

		template<typename T>
		bool read_large_array( uint64_t address, T out[ ], size_t len )
		{
			size_t real_size = sizeof( T ) * len;
			size_t read_size = 0;
			T* temp = out;  // Temporary pointer to keep track of the current position in the out array

			while ( read_size < real_size ) {
				BYTE* buffer = new BYTE[ 512 ];

				size_t diff = real_size - read_size;
				if ( diff > 512 )
					diff = 512;

				this->read_physical( address + read_size, buffer, diff );

				std::memcpy( temp, buffer, diff );

				read_size += diff;
				temp += ( diff / sizeof( T ) );

				delete[ ] buffer;
			}

			return true;
		}

		[[nodiscard]] auto read_string( std::uintptr_t address, void* buffer, std::size_t size ) -> std::string {

			read_array( address, buffer, size );
			char name[ 255 ] = { 0 };
			std::memcpy( &name, buffer, size );
			return std::string( name );
		}

		// only a test for now
		auto test_speeds( ) -> const void
		{
			const auto buffer = this->read<std::uintptr_t>( this->m_image_base );
			if ( !buffer ) {
				std::printf( hash_str(" [buffer] -> invalid.\n") );
				std::cin.get( );
			}
			std::printf( hash_str( "\n [buffer] -> %I64d\n" ), buffer );

			const auto rpm_time = [ & ] ( ) -> float
				{
					auto time_now = std::chrono::high_resolution_clock::now( );

					for ( auto x = 0ull; x < 0x10000; x++ ) {

						auto data = this->read<std::uintptr_t>( this->m_image_base + x );
						if ( !data ) { continue; }

					}

					auto time_span = std::chrono::duration_cast< std::chrono::duration< float > >(
						std::chrono::high_resolution_clock::now( ) - time_now
					);

					return time_span.count( );
				};
			std::printf( hash_str("\n [read(0x10,000)] -> %fs"), rpm_time( ) );

			const auto rpm_time2 = [ & ] ( ) -> float
				{
					auto time_now = std::chrono::high_resolution_clock::now( );
					for ( auto x = 0ull; x < 0x100000; x++ ) {

						auto data = this->read<std::uintptr_t>( this->m_image_base + x );
						if ( !data ) { continue; }

					}
					auto time_span =
						std::chrono::duration_cast< std::chrono::duration< float> >( std::chrono::high_resolution_clock::now( ) - time_now );
					return time_span.count( );
				};
			std::printf( hash_str( "\n [read(0x100,000)] -> %fs\n" ), rpm_time2( ) );
		}

	public:

		std::uintptr_t cache_rax = 0;
		std::uintptr_t m_image_base = 0;
	};

} inline auto vm = std::make_unique<uefi::c_interface>( );

#endif // include guard