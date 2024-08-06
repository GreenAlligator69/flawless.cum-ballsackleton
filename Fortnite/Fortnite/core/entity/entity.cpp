#pragma once 
#include "../inc.hpp"
auto timer_stop = std::chrono::high_resolution_clock::now( );

auto entity::c_entity::tick( ) noexcept -> void
{
	for ( ;; ) {
		
		constexpr auto update_time = 25;

		auto timer_start = std::chrono::high_resolution_clock::now( );
		auto count = std::chrono::duration_cast< std::chrono::milliseconds >(
			timer_start - timer_stop
		).count( );

		if ( count > update_time )
		{
			std::unique_lock<std::mutex> lock( this->m_mutex );
			{

				sdk::u_world m_world {};
				this->get_world( m_world );

				this->get_actors( );

			}
			lock.unlock( );
			timer_stop = std::move( timer_start );
		}
		else {

			std::this_thread::sleep_for(
				std::chrono::milliseconds(
					update_time - count
				) );
		}

	}
}

auto entity::c_entity::get_world( const sdk::u_world& world ) -> void
{
	auto uworld = world.get_world( );
	if ( !uworld ) return;

	this->game_state = uworld->game_state( );

	auto game_instance = uworld->game_instance( );
	if ( !game_instance ) return;

	auto localplayer = game_instance->get_localplayer( );
	if ( !localplayer ) return;

	this->view_state = localplayer->view_state( ).get( 1 );
	if ( !view_state ) return;
}

auto entity::c_entity::get_actors(  ) -> void 
{
	const auto actor_array = game_state->player_array( ).get_itter( );

	for ( auto index = 0ul; index < actor_array.size( ); ++index ) {
		
		auto player_state = actor_array[ index ];
		if ( !player_state ) continue;

		auto actor = player_state->pawn_private( );
		if ( !actor ) continue;

		const auto is_same = [ & ] ( const aactor::c_list& list )
		{
			return actor == list.m_actor;
		};

		const auto it = std::find_if( m_list_cache.begin( ), m_list_cache.end( ), is_same );
		if ( it == m_list_cache.end( ) ) {
			m_list_cache.emplace_back( aactor::c_list { index, actor, player_state, game_state } );
		}
	}
	this->m_list.swap( m_list_cache );

	if ( !this->m_list_cache.empty( ) )
		this->m_list_cache.clear( );
}

void entity::c_entity::loop( const std::function< void( aactor::c_list )>& fn ) const {

	for ( const auto& it : this->m_list ) {

		// checks here
		
		fn( it );
	}

}