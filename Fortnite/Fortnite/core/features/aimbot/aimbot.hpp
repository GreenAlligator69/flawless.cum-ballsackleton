#ifndef AIMBOT_HPP
#define AIMBOT_HPP

class c_aimbot
{
	std::mutex m_mutex {};

public:

	ALWAYS_INLINE c_aimbot( ) { g_vars->load( ); }
	ALWAYS_INLINE ~c_aimbot( ) = default;

	struct projectile_properties {
		int speed;
		double gravity;
	};

	uemath::fvector local_velocity;
	uemath::fvector velocity;
	float projectile_speed;
	float projectile_gravity;
	static std::unordered_map<std::string, projectile_properties> weapon_properties;
	uemath::fvector prediction_calculations( uemath::fvector target, uemath::fvector velocity, uemath::fvector local_velocity, float projectile_speed_scale, float projectile_gravity_scale, float distance );

	uemath::frotator find_look_at_rotation( uemath::fvector& start, uemath::fvector& target );
	uemath::frotator clamp_angle( uemath::frotator startRotation, uemath::frotator endRotation, float SmoothScale );
	void aim_lock( uemath::fvector aim_location );

	void tick( );
}; inline const auto g_aimbot = std::make_unique<c_aimbot>( );

#endif