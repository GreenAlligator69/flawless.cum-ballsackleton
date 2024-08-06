#pragma once 

namespace render
{

	class c_render
	{
	private:

		std::mutex m_mutex {};
		MSG m_msg { };

	public:

		ALWAYS_INLINE c_render( ) { g_vars.get( )->load( ); };

		bool setup( const std::wstring& proc_name );

		std::string get_window_name( HWND window );
		HWND get_window_handle( std::uint32_t pid );

		bool get_screen_status( );
		bool get_window( );

		void clean_context( );
		void release_objects( );

		void tick( );

	public:

		MARGINS m_margin { -1 };
		RECT m_rect { };

		std::uint32_t m_pid { };
		std::string m_name { };

		HWND m_window_target { };

		int m_width { };
		int m_height { };

		int m_width_2 { };
		int m_height_2 { };
	};

} inline const auto g_render = std::make_unique<render::c_render>( );