#pragma once 
namespace uengine {

    template < typename _value_t >
        requires std::is_arithmetic_v< _value_t >
    using enough_float_t = std::conditional_t< sizeof( _value_t ) <= sizeof( float ), float, double >;

    template < typename _ret_t >
        requires std::is_floating_point_v< _ret_t >
    inline constexpr auto k_pi = static_cast< _ret_t >( std::numbers::pi );

    template < typename _ret_t >
        requires std::is_floating_point_v< _ret_t >
    inline constexpr auto k_pi2 = static_cast< _ret_t >( k_pi< double > *2.0 );

    template < typename _ret_t >
        requires std::is_floating_point_v< _ret_t >
    inline constexpr auto k_rad_pi = static_cast< _ret_t >( 180.0 / k_pi< double > );

    template < typename _ret_t >
        requires std::is_floating_point_v< _ret_t >
    inline constexpr auto k_deg_pi = static_cast< _ret_t >( k_pi< double > / 180.0 );

    template < typename _value_t >
        requires std::is_arithmetic_v< _value_t >
    ALWAYS_INLINE constexpr auto to_deg( const _value_t rad )
    {
        using ret_t = enough_float_t< _value_t >;

        return static_cast< ret_t >( rad * k_rad_pi< ret_t > );
    }

    template < typename _value_t >
        requires std::is_arithmetic_v< _value_t >
    ALWAYS_INLINE constexpr auto to_rad( const _value_t deg )
    {
        using ret_t = enough_float_t< _value_t >;

        return static_cast< ret_t >( deg * k_deg_pi< ret_t > );
    }

    struct f_plane : uemath::fvector {

        f_plane( ) : w( 0 ) { }
        f_plane( double w ) : w( w ) { }

        uemath::fvector to_vector( ) {
            uemath::fvector value;
            value.x = this->x;
            value.y = this->y;
            value.z = this->z;
            return value;
        }

        double w;
    };

    class c_matrix {
    public:

        double m[ 4 ][ 4 ];
        f_plane x_plane, y_plane, z_plane, w_plane;

        c_matrix( ) : x_plane( ), y_plane( ), z_plane( ), w_plane( ) { }
        c_matrix( f_plane x_plane, f_plane y_plane, f_plane z_plane, f_plane w_plane )
            : x_plane( x_plane ), y_plane( y_plane ), z_plane( z_plane ), w_plane( w_plane ) { }

        c_matrix to_multiplication( c_matrix m_matrix );
        c_matrix to_rotation_matrix( uemath::frotator& rotation );
    };

    class ftransform {
    public:

        f_plane rotation;
        uemath::fvector translation;
        char pad[ 0x4 ]; // 0x38(0x08)
        uemath::fvector scale;
        char pad1[ 0x4 ]; // 0x58(0x08)

        ftransform( ) : rotation( ) , translation( 0.f, 0.f, 0.f ), scale( 0.f, 0.f, 0.f ), pad( ), pad1( ) { }

        ftransform( const f_plane& rot, const uemath::fvector& translation, const uemath::fvector& scale )
        {
            this->rotation = rot;
            this->translation = translation;

            this->pad[ 0x4 ] = 0;
            this->scale = scale;
            this->pad1[ 0x4 ] = 0;
        }

        [[nodiscard]] c_matrix to_matrix( );

    };

    class c_tick_listener
    {
    public:

    };

    class c_engine : public c_matrix {

        std::vector<uengine::ftransform> v_bone;

    public:
        void update_matrix( );
        bool in_screen( uemath::fvector bone );
        double get_cross_distance( double x1,double y1,double x2,double y2 );
        bool is_shot( uemath::fvector lur,uemath::fvector wl );

        uemath::fvector get_axes( uemath::fvector& world_location );
        uemath::fvector world_to_screen( uemath::fvector& world_location );
        uemath::fvector world_to_screen( uemath::fvector& world_location, uemath::fvector point_location ); 

        uemath::frotator rotation { };
        uemath::fvector location { };

        float field_of_view = 0;

        int m_width { };
        int m_height { };

        int m_width_2 { };
        int m_height_2 { };
    };

} inline auto engine = std::make_unique<uengine::c_engine>( );