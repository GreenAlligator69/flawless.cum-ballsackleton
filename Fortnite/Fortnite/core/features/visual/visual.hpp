#ifndef VISUAL_HPP
#define VISUAL_HPP

class c_visual
{
private:

	std::mutex m_mutex {};

public:

	ALWAYS_INLINE c_visual( ) { g_vars.get( )->load( ); }
	//ALWAYS_INLINE ~c_visual( ) = default;

	void render( );
}; 

inline const auto visual = std::make_unique<c_visual>( );

#endif