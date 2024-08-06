#pragma once 
namespace utilities
{
	class c_utilities
	{

		FILE* m_console = nullptr;
		std::chrono::steady_clock::time_point m_time { };
		
	public:
		
		const std::wstring get_gamebar_sid( std::uint32_t process_id );
		const std::uint32_t get_process_id( const std::wstring_view process_name );
		bool attach_console( );
		void detach_console( );

		std::chrono::steady_clock::time_point timer_start( );
		void timer_end( );
	};
} inline auto g_utils = std::make_shared<utilities::c_utilities>( );