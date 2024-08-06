#pragma once
namespace settings
{
	using e_setting_type = enum
	{
		set_none,
		set_int,
		set_float,
		set_bool,
		set_primary
	};

	class c_vars
	{
		std::string m_name;
		e_setting_type m_type;

	public: 

		void load( );
		void save( );
		void reset( );

		struct {
			int aim_keycode;
			int target_bone;
			bool enabled;
			float fov_c; 
			bool prediction;
			float smooth;
			float accuracy_rate;
			bool ignore_team;
			bool ignore_knocked;
			bool ignore_invisible;
		} aim;

		struct {
			struct {
				bool enabled;
				bool prediction;
				float weapon_fov;
			} smg;

			struct {
				bool enabled;
				bool prediction;
				float weapon_fov;
			} ars;

			struct {
				bool enabled;
				float weapon_fov;
			} shotgun;

			struct {
				bool enabled;
				bool prediction;
				float weapon_fov;
			} pistol;

			struct {
				bool enabled;
				bool prediction;
				float weapon_fov;
			} snipers;

		} weapon_config;
		
		struct {
			bool esp;
			
			bool bounding_box;
			bool bounding_corner;
			bool bounding_3d;
			bool corner;
			bool username;
			bool distance;
			bool snapline;
			bool weapon;
			bool skeleton;
			bool view_angle;
			
			bool ignore_team;
			bool ignore_knocked;

		} visuals;

		struct {
			bool enabled;
			float width;
			float height;
			bool show_team;
		} radar;

		struct {
			bool weapons;
			bool items;
			bool vehicles;
			bool chests;
			bool ammo;

			bool smart_loot;
			bool priot_tier;
			bool prior_ammo;
			bool prior_health;
			bool prior_shield;
			
			float weapons_render_distance = 50.0f;
			float items_render_distance = 50.0f;
			float vehicles_render_distance = 150.0f;
			float chests_render_distance = 50.0f;
			float ammo_render_distance = 50.0f;
		} loot;

		struct {

			bool fov;
			bool fps;
			bool menu;
			bool trigger_bot;
			bool crosshair;

			bool kill;

			float custom_delay;
			float maximum_distance;
			bool has_clicked;
			std::chrono::steady_clock::time_point tb_begin;
			std::chrono::steady_clock::time_point tb_end;
			int tb_time_since;

		} misc;

		struct {

		} keybind;
	};

} inline const auto g_vars= std::make_shared<settings::c_vars>( );