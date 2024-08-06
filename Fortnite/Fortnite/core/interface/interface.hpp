#ifndef INTERFACE_HPP
#define INTERFACE_HPP

namespace m_interface
{
	struct c_tab {
		int m_num;
		const char* m_label;

		std::function< void( ) > page;

		c_tab( int num, const char* label ) {
			m_num = num;
			m_label = label;
		}
	};

	class c_interface
	{
		bool hover_element = false;
		uemath::fvector2d drag_position{};

		uemath::flinearcolor color_menu_bg = { };
		uemath::flinearcolor color_menu_bar = { };
		uemath::flinearcolor color_menu_fg = { };
		uemath::flinearcolor color_menu_theme = { };

		uemath::flinearcolor color_checkbox_bg = { };
		uemath::flinearcolor color_checkbox_active = { };
		uemath::flinearcolor color_checkbox_hovered = { };

	public:

		c_interface( );

		void draw_frames( );
		void draw_interface( );
		void begin( uemath::fvector2d start, uemath::fvector2d size );
		void begin_parent( const std::string& title, uemath::fvector2d start, uemath::fvector2d size );
		void handler( );

		uemath::fvector2d get_cursor( );

		bool is_hovered( uemath::fvector2d Start, uemath::fvector2d Size );
		bool button( std::string Title, uemath::fvector2d size );
		bool tab( int icon_id, std::string title, int tab_id, uemath::fvector2d size );
		void slider( std::string Title, float* Option, float Min, float Max );
		void check_box( std::string Title, bool* Option );

		bool add_widget( uemath::fvector2d size )
		{
			auto current = uemath::fvector2d( this->position.x + this->offset.x, this->position.y + this->offset.y );

			framework.get( )->rect( current.x, current.y, size.x, size.y, framework.get( )->get_color( 255, 38, 38, 38 ), true, 5, 5 );
			framework.get( )->filled_rect( current.x, current.y, size.x, size.y, this->color_menu_bar, true, 5, 5 );

			return true;
		}

		auto current_offset( )
		{
			return uemath::fvector2d( this->position.x + this->offset.x, this->position.y + this->offset.y );
		}

		bool hotkey( int* k ) {
			auto current = uemath::fvector2d( this->position.x + this->offset.x, this->position.y + this->offset.y );
			auto size = uemath::fvector2d( 40, 20 );

			bool is_hovered = this->is_hovered( current, size );
			bool clicked = is_hovered && this->LeftMouseClicked;

			uemath::flinearcolor color = is_hovered ? framework.get( )->get_color( 255, 100, 100, 100 ) : framework.get( )->get_color( 255, 38, 38, 38 );

			static bool waitingforkey = false;
			static bool ignoreMouseClick = false;

			if ( clicked && !waitingforkey ) {
				waitingforkey = true;
				ignoreMouseClick = true;
			}
			else if ( waitingforkey ) {
				if ( ignoreMouseClick ) {
					ignoreMouseClick = false;
				}
				else {
					for ( int i = 0; i < sizeof( KeyCodes ) / sizeof( KeyCodes[0] ); ++i ) {
						if ( this->LeftMouseClicked )
						{
							*k = 0x01;
							waitingforkey = false;
							break;
						}

						if ( GetAsyncKeyState( KeyCodes[i] ) & 0x01 ) {  // Check if the key was pressed.
							*k = KeyCodes[i];
							waitingforkey = false;
							break;
						}
					}
				}
			}

			std::string string = waitingforkey ? "..." : KeyNames[*k];
			//framework.get( )->text( string, current.x + 20.0f, current.y + 16.0f, framework.get( )->get_color( 255, 163, 163, 163 ), 10, true, font_weight::m_normal, true );
			framework.get( )->rect( current.x, current.y, size.x, size.y, color );

			return true;
		}

		auto interactive_rect( uemath::fvector2d size, bool static_color = false, uemath::flinearcolor static_color_code = uemath::flinearcolor( 255, 38, 38, 38 ) )
		{
			auto current = this->current_offset( );
			bool is_hovered = this->is_hovered( current, size );
			bool clicked = is_hovered && this->LeftMouseClicked;

			auto hover_color = framework.get( )->get_color( 255, 239, 68, 68 );

			if ( is_hovered && !static_color )
			{
				hover_color = framework.get( )->get_color( 100, 239, 68, 68 );
			}
			else
			{
				hover_color = framework.get( )->get_color( 255, 38, 38, 38 );
			}

			if ( static_color )
				hover_color = static_color_code;

			framework.get( )->filled_rect(current.x, current.y, size.x, size.y, hover_color, true, 2, 2 );
			framework.get( )->rect(current.x, current.y, size.x, size.y, framework.get( )->get_color( 255, 83, 83, 83 ), true, 2, 2 );
			
			return clicked;
		}

		bool header( std::string Title )
		{
			uemath::fvector2d size = uemath::fvector2d{ 46.0f, 25.0f };

			const auto current = uemath::fvector2d( this->position.x + this->offset.x, this->position.y + this->offset.y );


			//Outline
			//framework.get( )->rect( Current.x, Current.y, size.x, size.y, framework.get( )->get_color( 255, 38, 38, 38 ), true, 2, 2 );
			//framework.get( )->filled_rect( Current.x, Current.y, size.x, size.y, framework.get( )->get_color( 255, 32, 32, 32 ), true, 2, 2 );

			//Text
			auto text_pos = uemath::fvector2d{ current.x + size.x / 2, current.y + size.y / 1.25 };
			framework.get( )->filled_rect( current.x, current.y, size.x, size.y, this->color_menu_bar, true, 2, 2 );
			//framework.get( )->text( Title.c_str( ), text_pos.x, text_pos.y, framework.get( )->get_color( 255, 255, 255, 255 ), 12, true, font_weight::m_normal, true );

			this->offset.y += size.y + this->ItemSpacing;
			//this->offset.x += size.x + 15;

			return true;

		}

		void set_position( uemath::fvector2d value );

		std::vector< m_interface::c_tab > m_tab{
			{ 0, "Visuals" },
			{ 1, "Aimbot" },
			{ 2, "Loot" },
			{ 3, "Miscellaneous" },
			{ 4, "Customize" },
			{ 5, "Config" }
		};

		float ItemSpacing;
		uemath::fvector2d position, size, offset, cursor;
		bool initialized = false;
		bool LeftMouseClicked, LeftMouseDown;

	private:

		int current_page = 0;

		void add_page( int tab, std::function< void( ) > code );
		void render_page( );
	};
}; inline const auto g_interface = std::make_unique<m_interface::c_interface>( );

#endif 