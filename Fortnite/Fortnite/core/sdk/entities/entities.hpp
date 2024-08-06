#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#define current_class reinterpret_cast<uint64_t>( this )

#define declare_member(type, name, offset) type name() { return vm->read<type>( current_class + offset ); } 
#define declare_member_bit(Bit, Name, Offset) bool Name( ) { return bool( vm->read<char>( current_class + Offset) & (1 << Bit)); }

#define apply_member(type, name, offset) void name( type val ) { vm->write<type>( current_class + offset, val); }
#define apply_member_bit(Bit, Name, Offset) void Name( bool Value ) { vm->write<char>( vm->read<char>( current_class + Offset) | (1 << Bit), Value); }

namespace sdk {

	struct fname {
		std::uint32_t idx;
	};

	struct fbox_sphere_bounds final
	{
	public:
		struct uemath::fvector                        orgin;                                            // 0x0000(0x0018)(Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		struct uemath::fvector                        box_extent;                                         // 0x0018(0x0018)(Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		double                                        sphere_radius;                                      // 0x0030(0x0008)(Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	template< class type >
	class tarray {
	public:

		tarray( ) : data( ), count( ), max_count( ) { }
		tarray( type* data, std::uint32_t count, std::uint32_t max_count ) :
			data( data ), count( count ), max_count( max_count ) { }

		FORCEINLINE type get( std::uintptr_t idx )
		{	
			return vm->read< type >(
				std::bit_cast< std::uintptr_t >( this->data ) + ( idx * sizeof( type ) ) 
			);
		}

		FORCEINLINE std::vector<type> get_itter( )
		{
			if ( this->count > this->max_count )
				return {};

			std::vector<type> buffer( this->count );

			vm->read_array( 
				std::bit_cast<std::uintptr_t>( this->data ), 
				buffer.data( ), 
				sizeof( type ) * this->count
			);

			return buffer;
		}

		ALWAYS_INLINE std::uintptr_t get_addr( )
		{
			return reinterpret_cast<std::uintptr_t>( this->data );
		}

		ALWAYS_INLINE std::uint32_t size( ) const
		{
			return this->count;
		};

		ALWAYS_INLINE std::uint32_t max_size( ) const
		{
			return this->max_count;
		};

		ALWAYS_INLINE bool is_valid_index( std::int32_t index ) const
		{
			return this->index >= 0 && index < count;
		};

		ALWAYS_INLINE bool is_valid( ) const
		{
			return this->data != nullptr;
		};

		type* data;
		std::uint32_t count;
		std::uint32_t max_count;

	};

	// Class CoreUObject.Object
	class u_object
	{
	public:
		declare_member( fname, name_private, 0x18 );
	};

	class u_actor_component : public u_object
	{
	public:
	};

	// Class Engine.SceneComponent
	class u_scene_component : public u_actor_component
	{
	public:
		declare_member( uemath::fvector, component_velocity, 0x168 );
		declare_member( uemath::fvector, relative_location, 0x120 );
		declare_member( uemath::fvector, relative_rotation, 0x138 );

		//apply_member( uemath::fvector, component_velocity, 0x168 );
		//apply_member( uemath::fvector, relative_location, 0x120 );
		//apply_member( uemath::fvector, relative_rotation, 0x138 );
	};

	class u_primitive_component : public u_scene_component
	{
	public:
		declare_member( float, last_submit_time, 0x344 + 0x14 );
		declare_member( float, last_render_time_on_screen, 0x344 + 0x1C );
	};

	class u_mesh_component : public u_primitive_component
	{
	public:
	};

	// Class Engine.SkinnedMeshComponent
	class u_skinned_mesh_component : public u_mesh_component
	{
	public:
		declare_member( std::int32_t, is_cached, 0x5F8 );
		declare_member( tarray<uengine::ftransform>, bone_array, 0x5b0 + ( this->is_cached( ) * 0x10 ) );
		declare_member( uengine::ftransform, component_to_world, 0x1C0 );
		declare_member( fbox_sphere_bounds, get_bounds, 0xE8 );

		auto get_bone_id( std::uint32_t bone_index ) -> uemath::fvector
		{
			auto bone_array = this->bone_array( );
			if ( !bone_array.is_valid( ) ) 
				return { };

			auto bone = bone_array.get( bone_index );

			auto matrix = bone.to_matrix( ).to_multiplication(
				this->component_to_world( ).to_matrix( )
			);

			return matrix.w_plane;
		}

		auto get_bone_location( uengine::ftransform bone_transform ) -> uemath::fvector
		{

			auto matrix = bone_transform.to_matrix( ).to_multiplication(
				this->component_to_world( ).to_matrix( )
			);

			return matrix.w_plane;
		}
	};

	class u_skeletal_mesh_component : public u_skinned_mesh_component
	{
	public:
		auto is_visible( ) -> bool 
		{
			return last_render_time_on_screen( ) + 0.06f >= last_submit_time( );
		}
	};

	// Class Engine.Actor
	class a_actor : public u_object
	{
	public:
		declare_member( u_scene_component*, root_component, 0x198 );

	};


	class f_text
	{
	public:
		declare_member( uintptr_t, name, 0x28 );
		declare_member( int32_t, length, 0x30 );

		auto get_name( ) -> std::string
		{
			auto text_length = this->length( );
			auto text_ptr = this->name( );

			if ( !text_ptr || text_length < 1 )
				return hash_str( "NULL" );

			wchar_t* name = new wchar_t[uintptr_t( text_length ) + 1];
			vm->read_large_array( text_ptr, name, text_length );

			std::wstring ws( name );
			delete[] name;

			return std::string( ws.begin( ), ws.end( ) );
		}
	};

	// Class Engine.Controller
	struct a_controller : public a_actor
	{
	public:

	};

	// Class FortniteGame.FortItemDefinition
	struct u_fort_item_definition : public a_actor
	{
		//declare_member( e_fort_item_tier, tier, 0x73 );
		//declare_member( e_fort_item_type, type, 0x70 );
		//declare_member( f_text*, display_name, 0x90 );
	};

	struct u_fort_world_item_definition : public u_fort_item_definition
	{
	public:
		declare_member( f_text*, weapon_display_name, 0x40 );
	};

	struct u_fort_weapon_item_defintion : public u_fort_world_item_definition
	{
	public:

	};

	// Class FortniteGame.FortWeaponAnimSet
	struct u_fort_weapon_anim_set
	{
	public:
		//apply_member( float, sprint_fire_speed, 0x34 );
	};

	// ScriptStruct FortniteGame.FortRangedWeaponRecoil
	struct f_fort_ranged_weapon_recoil
	{
	public:
		//apply_member( float, min_vertical, 0x04 );
		//apply_member( float, max_vertical, 0x08 );
		//apply_member( float, min_horizontal, 0x0c );
		//apply_member( float, max_horizontal, 0x10 );
	};

	// Class FortniteGame.FortWeaponModRuntimeData
	struct u_fort_weapon_mod_runtime_data : public u_object
	{
	public:
		//declare_member( tarray<f_fort_ranged_weapon_recoil*>, recoil_per_bullet, 0x28 );
	};

	// Class FortniteGame.FortWeapon
	struct a_fort_weapon : public a_actor
	{
	public:
		declare_member( u_fort_weapon_item_defintion*, weapon_data, 0x500 );
		//declare_member( u_fort_weapon_mod_runtime_data*, mod_runtime_data, 0xf00 );
		//declare_member( u_fort_weapon_anim_set*, weapon_animation_override, 0x1260 );
		//declare_member( bool, reloading, 0x360 );
		//declare_member( bool, charging, 0x361 );
		//declare_member( bool, aiming_consumable, 0x364 );
		//declare_member( bool, disable_animation, 0x362 );

		//apply_member( bool, disable_animation, 0x362 );
		//apply_member( bool, switch_slot_cooldown, 0x1359 );
	};

	// ScriptStruct FortniteGame.FortItemEntry
	struct f_fort_item_entry
	{
		//declare_member( u_fort_item_definition*, item_def, 0x18 );
	};

	// Class FortniteGame.FortPickup
	class a_fort_pickup : public a_actor
	{
	public:
		//declare_member( u_fort_item_definition*, pickup_entry, 0x350 + 0x18 );
	};

	// Class Engine.Pawn
	class a_pawn : public a_actor
	{
	private:
		//auto decrypt_fname( int key ) -> std::string
		//{
		//	auto pool_chunk = vm.get( )->read<uint64_t>(
		//		vm.get( )->m_image_base + 0x1150A280 +
		//		( 8 * ( uint32_t ) ( ( int ) ( key ) >> 16 ) )
		//		+ 16 ) + ( unsigned int ) ( 2 * ( uint16_t ) key
		//			);

		//	auto pool_size = vm.get( )->read<uint16_t>( pool_chunk );

		//	auto name_length = pool_size >> 6;

		//	char buff[2048];

		//	if ( name_length )
		//	{
		//		vm.get( )->read_physical( pool_chunk + 2, buff, name_length );

		//		char* v2 = buff; // rdi
		//		int v4 = 14; // edx
		//		__int64 result = name_length; // rax
		//		__int64 v6; // r8
		//		unsigned int v7; // edx

		//		if ( ( int ) result )
		//		{
		//			v6 = ( unsigned int ) result;
		//			do {
		//				v7 = v4 + 45297;
		//				*v2 = v7 + ~*v2;
		//				result = v7 << 8;
		//				++v2;
		//				v4 = result | ( v7 >> 8 );
		//				--v6;
		//			} while ( v6 );
		//		}

		//		buff[name_length] = '\0';
		//		return std::string( buff );
		//	}
		//	else {
		//		return hash_str( "None" );
		//	}
		//}

	public:
		//declare_member( std::int32_t, pool_id, 0x18 );

		/*
		auto get_object_name( ) -> std::string
		{
			auto key = this->pool_id( );
			if ( !key ) {
				return OBFUSCATE_STR( "None" );
			}

			if ( m_vm.get( )->fname_cache.find( key ) != m_vm.get( )->fname_cache.end( ) ) {
				return m_vm.get( )->fname_cache[key];
			}

			auto pool_chunk = m_vm.get( )->read<uint64_t>(
				m_vm.get( )->m_image_base + 0x11947880 +
				( 8 * ( uint32_t ) ( ( int ) ( key ) >> 16 ) )
				+ 16 ) + ( unsigned int ) ( 2 * ( uint16_t ) key
					);

			auto pool_size = m_vm.get( )->read<uint16_t>( pool_chunk );

			if ( pool_size < 64 )
			{
				std::string fname = decrypt_fname(
					m_vm.get( )->read<DWORD>( pool_chunk + 2 )
				);

				m_vm.get( )->fname_cache[key] = fname;

				return fname;
			}
			else
			{
				std::string fname = decrypt_fname(
					key
				);

				m_vm.get( )->fname_cache[key] = fname;

				return fname;
			}
		}*/
	};

	// Class Engine.Character
	class a_character : public a_pawn
	{
	public:
		declare_member( u_skeletal_mesh_component*, mesh, 0x318 );
	};

	struct afgf_character : public a_character
	{
	public:
	};

	// Class FortniteGame.FortPawn
	struct a_fort_pawn : public afgf_character
	{
	public:

		//apply_member( bool, override_materials, 0x570 );

		declare_member( a_fort_weapon*, current_weapon, 0xA68 );
		//declare_member( a_fort_weapon*, previous_weapon, 0xa28 );
		declare_member( tarray<a_fort_weapon*>, weapon_list, 0xa30 );

		declare_member_bit( 4, is_dying, 0x758 );
		declare_member_bit( 4, is_dbno, 0x93a );

		std::string retrieve_player_weapon( )
		{
			auto current_weapon = this->current_weapon( );
			auto weapon_data = current_weapon->weapon_data( );
			if ( !weapon_data ) return hash_str( "Building Plan");

			auto display_name = weapon_data->weapon_display_name( );
			if ( !display_name ) return hash_str( "Building Plan" );

			auto weapon_length = display_name->length( );
			if ( !weapon_length ) return hash_str( "Building Plan" );

			if ( weapon_length <= 0 ) return hash_str( "Building Plan" );

			auto weapon_name = new wchar_t[ std::uint64_t( weapon_length ) + 1 ];
			vm->read_array( reinterpret_cast< uintptr_t >( display_name->name( ) ), weapon_name, weapon_length * sizeof( wchar_t ) );

			std::wstring s_weapon_name( weapon_name );
			delete[ ] weapon_name;

			return std::string( s_weapon_name.begin( ), s_weapon_name.end( ) );
		}
	};

	struct f_replicated_athena_vehicle_attributes
	{
	public:
	};

	struct a_fort_athena_vehicle : public a_pawn
	{
	public:
		//apply_member( float, seat_switch_cooldown, 0xcf4 );
	};

	struct a_fort_player_pawn : public a_fort_pawn
	{
	public:
	};

	// Class Engine.PlayerController
	struct a_player_controller : public a_controller
	{
	public:
		//apply_member( uemath::fvector, control_input, 0x520 );
		//apply_member( bool, first_person, 0xF70 + 0x10 + 0x18 );

		declare_member( bool, is_local_controller, 0x6bc );
		//declare_member( uemath::fvector, control_input, 0x520 );

		apply_member( uemath::frotator, view_angles, 0x520 );
		apply_member( uemath::frotator, rotation_reset, 0x820 );

		//apply_member( a_fort_player_pawn_athena*, focal_point, 0x3b68 );
	};


	struct a_fort_player_pawn_athena : public a_fort_player_pawn
	{
	public:
	/*	declare_member( a_fort_athena_vehicle*, current_vehicle, 0x2840 );*/
		declare_member( a_player_controller*, controller, 0x2c8 );
	};

	// Class Engine.PlayerState
	class a_player_state : public u_object
	{
	public:
		declare_member( a_fort_player_pawn_athena*, pawn_private, 0x308 );
		declare_member_bit( 3, is_bot, 0x29a );

	public:

		/*auto get_player_username( bool is_lobby )
		{
			__int64 ftext;
			int length;

			if ( is_lobby )
			{
				length = vm.get( )->read<int>( current_class + 0x330 );

				ftext = vm.get( )->read<__int64>( current_class + 0x328 );
			}
			else
			{
				auto fstring = vm.get( )->read<__int64>( current_class + 0xAE8 );
				length = vm.get( )->read<int>( fstring + 16 );

				ftext = ( uintptr_t )vm.get( )->read<__int64>( fstring + 8 );
			}

			wchar_t* buffer = new wchar_t[length];
			vm.get( )->read_physical( ftext, buffer, length * sizeof( wchar_t ) );

			auto v6 = ( __int64 ) length;

			if ( !v6 )
				return std::string( hash_str( "AI" ) );

			char v21;
			int v22;
			int i;
			int v25;
			_WORD* v23;

			v21 = v6 - 1;
			if ( !( _DWORD ) v6 )
				v21 = 0;
			v22 = 0;
			v23 = ( _WORD* ) buffer;
			for ( i = ( v21 ) & 3; ; *v23++ += i & 7 )
			{
				v25 = v6 - 1;
				if ( !( _DWORD ) v6 )
					v25 = 0;
				if ( v22 >= v25 )
					break;
				i += 3;
				++v22;
			}

			std::wstring username{ buffer };
			return std::string( username.begin( ), username.end( ) );
		} */

	};

	class a_fort_player_state : public a_player_state
	{
	public:
	};

	// Class FortniteGame.FortPlayerStateZone
	class a_fort_player_state_zone : public a_fort_player_state
	{
	public:
		//declare_member( uint8, kick_reason, 0xce8 );
		//declare_member( float, current_health, 0xe34 );
		//declare_member( float, current_shield, 0xe3c );
	};

	// Class FortniteGame.FortPlayerStateAthena
	class a_fort_player_state_athena : public a_fort_player_state_zone
	{
	public:
		//declare_member( std::int32_t, team_kill_score, 0x103c );
		//declare_member( std::int32_t, human_kill_score, 0x1100 );
		//declare_member( std::int32_t, ai_kill_score, 0x1144 );
		//declare_member( std::int32_t, total_player_score, 0x1194 );
		declare_member( std::int32_t, team_id, 0x1251 );
	};

	// Redacted in SDK, must be accessed directly in memory.
	struct u_scene_view_state : public u_object
	{
	public:
		auto get_current_class( ) {
			return current_class;
		}
	};

	// Class Engine.LocalPlayer
	struct u_localplayer : public u_object
	{
	public:
		//declare_member( a_player_controller*, controller, 0xC0 );
		//declare_member( a_player_controller*, controller, 0x30 );

		//auto get_view_state( ) -> u_scene_view_state* {
		//	auto view_state = vm->read<tarray<u_scene_view_state*>>(
		//		current_class + 0xd0
		//	);

		//	return view_state.get( 0x1 );
		//}

		declare_member( tarray<u_scene_view_state*>, view_state, 0xd0 );
	};

	// Class Engine.Level
	struct u_level : public u_object
	{
	public:
		//declare_member( tarray<a_fort_player_pawn*>, actors, 0xA0 );
		//declare_member( int32_t, actor_count, 0xA8 );
	};

	// Class Engine.GameInstance
	struct u_game_instance : public u_object
	{
	public:
		declare_member( tarray<u_localplayer*>, localplayers, 0x38 );

		auto get_localplayer( ) -> u_localplayer* {

			return this->localplayers( ).get_itter( )[ 0 ];
		}
	};

	// Class Engine.GameStateBase
	struct a_game_state_base : public u_object
	{
	public:
		declare_member( float, server_world_time, 0x2c8 );
		declare_member( tarray<a_fort_player_state_athena*>, player_array, 0x2a8 );

		//declare_member( float, FocalPointRotationInterpSpeed, 0x1558 );
		//declare_member( float, FocalPointFOV, 0x1578 );

		ALWAYS_INLINE bool is_in_lobby( ) { return server_world_time( ) ? false : true; }
	};

	// Class Engine.World
	struct u_world : public u_object
	{
	public:
		//declare_member( u_level*, persistent_level, 0x30 );
		declare_member( a_game_state_base*, game_state, 0x160 );
		//declare_member( tarray<u_level*>, levels_array, 0x170 );
		declare_member( u_game_instance*, game_instance, 0x1D8 );

		ALWAYS_INLINE auto get_world( ) const -> u_world* {
			// sig: 48 89 05 ? ? ? ? 48 8B 4F 78 (RVA 7)
			return vm->read<u_world*>( vm->m_image_base + 0x126CF528 );
		}
	};

}

#endif // !gaurd