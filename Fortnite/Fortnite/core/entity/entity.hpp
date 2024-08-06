#ifndef ENTITY_HPP
#define ENTITY_HPP

namespace entity
{

	class c_entity
	{
		std::mutex	m_mutex { };
		sdk::a_game_state_base* game_state {};
		std::vector<aactor::c_list>  m_list_cache { };
		//std::vector<fortnite::c_item>   m_loots{ };

	public:

		ALWAYS_INLINE ~c_entity( ) = default;

		ALWAYS_INLINE c_entity( ) 
			: m_list_cache( { } )
		{
			g_vars->load( ); this->m_list_cache.resize( 110 ); 
			/*this->m_list_cache.reserve( 110 );*/ 
			/* this->m_loots.reserve( 300 );*/ 
		}

		ALWAYS_INLINE void reset( ) { /*fortnite::m_players.clear( ); */ /* this->m_loots.clear( );*/ }

		ALWAYS_INLINE void get_world( const sdk::u_world& world );
		ALWAYS_INLINE void get_actors(  );

		void tick( ) noexcept;
		void loop( const std::function< void( aactor::c_list )>& fn ) const;

		std::vector<aactor::c_list>  m_list { };
		//std::vector<fortnite::c_item>  m_loot{ };

		// temp
		sdk::u_scene_view_state* view_state { };
		sdk::a_fort_player_state_athena* local_player_state;
		sdk::a_fort_player_pawn_athena* local_player_pawn;
		sdk::a_player_controller* local_player_controller;
		sdk::a_player_controller* player_controller;

		sdk::a_fort_player_pawn_athena* target_player_pawn;
 	};

} inline const auto g_entity = std::make_unique<entity::c_entity>( );

#endif // ENTITY_HPP
