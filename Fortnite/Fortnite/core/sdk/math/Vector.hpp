#pragma once 
#include <cassert>

constexpr auto flt_max = 3.402823466e+38F; // max value
constexpr auto flt_min = 1.175494351e-38F; // min normalized positive value

namespace uemath
{
    struct FVector
    {
        double                                             x;                                                        // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
        double                                             y;                                                        // 0x0008(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
        double                                             z;                                                        // 0x0010(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)

        inline FVector( )
            : x( 0 ), y( 0 ), z( 0 )
        { }

        inline FVector( double x, double y, double z )
            : x( x ),
            y( y ),
            z( z )
        { }

        bool IsNearlyZero( ) const {
            const float Tolerance = 1e-6;
            return ( x * x + y * y + z * z ) < Tolerance;
        }

        __forceinline FVector operator-( const FVector& V ) {
            return FVector( x - V.x, y - V.y, z - V.z );
        }

        __forceinline FVector operator+( const FVector& V ) {
            return FVector( x + V.x, y + V.y, z + V.z );
        }

        __forceinline FVector operator*( float Scale ) const {
            return FVector( x * Scale, y * Scale, z * Scale );
        }

        __forceinline FVector operator/( float Scale ) const {
            const float RScale = 1.f / Scale;
            return FVector( x * RScale, y* RScale, z * RScale );
        }

        __forceinline FVector operator+( float A ) const {
            return FVector( x + A, y + A, z + A );
        }

        __forceinline FVector operator-( float A ) const {
            return FVector( x - A, y - A, z - A );
        }

        __forceinline FVector operator*( const FVector& V ) const {
            return FVector( x * V.x, y * V.y, z * V.z );
        }

        __forceinline FVector operator/( const FVector& V ) const {
            return FVector( x / V.x, y / V.y, z / V.z );
        }

        __forceinline float operator|( const FVector& V ) const {
            return x * V.x + y * V.y + z * V.z;
        }

        __forceinline float operator^( const FVector& V ) const {
            return x * V.y - y * V.x - z * V.z;
        }

        __forceinline FVector& operator+=( const FVector& v ) {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        __forceinline FVector& operator-=( const FVector& v ) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        __forceinline FVector& operator*=( const FVector& v ) {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            return *this;
        }

        __forceinline FVector& operator/=( const FVector& v ) {
            x /= v.x;
            y /= v.y;
            z /= v.z;
            return *this;
        }

        __forceinline bool operator==( const FVector& src ) const {
            return ( src.x == x ) && ( src.y == y ) && ( src.z == z );
        }

        __forceinline bool operator!=( const FVector& src ) const {
            return ( src.x != x ) || ( src.y != y ) || ( src.z != z );
        }

        __forceinline float SizeSquared( ) const {
            return x * x + y * y + z * z;
        }

        __forceinline float SizeSquared2D( ) const {
            return x * x + y * y;
        }

        __forceinline float Dot( const FVector& vOther ) const {
            const FVector& a = *this;

            return ( a.x * vOther.x + a.y * vOther.y + a.z * vOther.z );
        }

        /*float Distance(FVector v)
        {
            return ((X - v.X) * (X - v.X) +
                (Y - v.Y) * (Y - v.Y) +
                (Z - v.Z) * (Z - v.Z));
        }*/

        double Distance( FVector v )
        {
            return double( ( sqrt )( ( pow )( v.x - x, 2.0 ) +  pow( v.y - y, 2.0 ) + pow( v.z - z, 2.0 ) ) );
        }

        //double Distance(FVector v)
        //{
        //	double dx = v.X - X;
        //	double dy = v.Y - Y;
        //	double dz = v.Z - Z;

        //	double squaredDistance = dx * dx + dy * dy + dz * dz;

        //	// Approximate the square root using the Newton-Raphson method
        //	double sqrtDistance = squaredDistance;
        //	double temp = 0;
        //	while (sqrtDistance != temp) {
        //		temp = sqrtDistance;
        //		sqrtDistance = 0.5 * (sqrtDistance + squaredDistance / sqrtDistance);
        //	}

        //	return sqrtDistance;
        //}

    };

	class fvector
	{
	public:
		fvector( ) : x( ), y( ), z( ) { }
		fvector( double x, double y, double z ) : x( x ), y( y ), z( z ) { }

		fvector operator + ( const fvector& other ) const { return { this->x + other.x, this->y + other.y, this->z + other.z }; }
		fvector operator - ( const fvector& other ) const { return { this->x - other.x, this->y - other.y, this->z - other.z }; }
		fvector operator * ( double offset ) const { return { this->x * offset, this->y * offset, this->z * offset }; }
		fvector operator / ( double offset ) const { return { this->x / offset, this->y / offset, this->z / offset }; }

		fvector& operator *= ( const double other ) { this->x *= other; this->y *= other; this->z *= other; return *this; }
		fvector& operator /= ( const double other ) { this->x /= other; this->y /= other; this->z /= other; return *this; }

		fvector& operator = ( const fvector& other ) { this->x = other.x; this->y = other.y; this->z = other.z; return *this; }
		fvector& operator += ( const fvector& other ) { this->x += other.x; this->y += other.y; this->z += other.z; return *this; }
		fvector& operator -= ( const fvector& other ) { this->x -= other.x; this->y -= other.y; this->z -= other.z; return *this; }
		fvector& operator *= ( const fvector& other ) { this->x *= other.x; this->y *= other.y; this->z *= other.z; return *this; }
		fvector& operator /= ( const fvector& other ) { this->x /= other.x; this->y /= other.y; this->z /= other.z; return *this; }

		operator bool( ) { return bool( this->x || this->y || this->z ); }
		friend bool operator == ( const fvector& a, const fvector& b ) { return a.x == b.x && a.y == b.y && a.z == b.z; }
		friend bool operator != ( const fvector& a, const fvector& b ) { return !(a == b); }

		[[nodiscard]] inline double vector_scalar( const fvector& v ) { return x * v.x + y * v.y + z * v.z; }
        [[nodiscard]] inline float distance_to( fvector v ) { return double( sqrtf( powf( v.x - x, 2.0 ) + powf( v.y - y, 2.0 ) + powf( v.z - z, 2.0 ) ) ) / 100; }
        [[nodiscard]] inline double distance( fvector v ) { return double( sqrtf( powf( v.x - x, 2.0 ) + powf( v.y - y, 2.0 ) + powf( v.z - z, 2.0 ) ) ); }
		[[nodiscard]] bool is_valid( ) const { return std::isfinite( this->x ) && std::isfinite( this->y ) && std::isfinite( this->z ); }
		constexpr void in_validate( ) { this->x = this->y = this->z = std::numeric_limits<float>::infinity( ); }
		[[nodiscard]] inline double length( ) { return sqrt( x * x + y * y + z * z ); }

        __forceinline float SizeSquared( ) const {
            return x * x + y * y + z * z;

        }

		double x, y, z;
	};

	inline double degree_to_radian( double degree ) {
		return static_cast<double>(degree * ( std::numbers::pi / 180 ));
	}

	inline void angle_rotation( const fvector& angles, fvector* forward )
	{
		double	sp, sy, cp, cy;

		sy = sin( degree_to_radian( angles.y ) );
		cy = cos( degree_to_radian( angles.y ) );

		sp = sin( degree_to_radian( angles.x ) );
		cp = cos( degree_to_radian( angles.x ) );

		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	struct fvector2d
	{
		fvector2d( ) : x( ), y( ) { }
		fvector2d( double x, double y ) : x( x ), y( y ) { }

		fvector2d operator + ( const fvector2d& other ) const { return { this->x + other.x, this->y + other.y }; }
		fvector2d operator - ( const fvector2d& other ) const { return { this->x - other.x, this->y - other.y }; }
		fvector2d operator * ( double offset ) const { return { this->x * offset, this->y * offset }; }
		fvector2d operator / ( double offset ) const { return { this->x / offset, this->y / offset }; }

		fvector2d& operator *= ( const double other ) { this->x *= other; this->y *= other; return *this; }
		fvector2d& operator /= ( const double other ) { this->x /= other; this->y /= other; return *this; }

		fvector2d& operator = ( const fvector2d& other ) { this->x = other.x; this->y = other.y; return *this; }
		fvector2d& operator += ( const fvector2d& other ) { this->x += other.x; this->y += other.y; return *this; }
		fvector2d& operator -= ( const fvector2d& other ) { this->x -= other.x; this->y -= other.y; return *this; }
		fvector2d& operator *= ( const fvector2d& other ) { this->x *= other.x; this->y *= other.y; return *this; }
		fvector2d& operator /= ( const fvector2d& other ) { this->x /= other.x; this->y /= other.y; return *this; }

		operator bool( ) { return bool( this->x || this->y ); }
		friend bool operator == ( const fvector2d& A, const fvector2d& B ) { return A.x == B.x && A.y == A.y; }
		friend bool operator != ( const fvector2d& A, const fvector2d& B ) { return !(A == B); }

		double vector_scalar( const fvector2d& V ) { return x * V.x + y * V.y; }
		double distance( fvector2d V ) { return double( sqrtf( powf( V.x - this->x, 2.0 ) + powf( V.y - this->y, 2.0 ) ) ); }

		double x, y;
	};

	class frotator
	{
	public:

		frotator( ) : pitch( ), yaw( ), roll( ) { }
		frotator( double Pitch, double Yaw, double Roll ) : pitch( Pitch ), yaw( Yaw ), roll( Roll ) { }

		frotator operator + ( const frotator& other ) const { return { this->pitch + other.pitch, this->yaw + other.yaw, this->roll + other.roll }; }
		frotator operator - ( const frotator& other ) const { return { this->pitch - other.pitch, this->yaw - other.yaw, this->roll - other.roll }; }
		frotator operator * ( double offset ) const { return { this->pitch * offset, this->yaw * offset, this->roll * offset }; }
		frotator operator / ( double offset ) const { return { this->pitch / offset, this->yaw / offset, this->roll / offset }; }

		frotator& operator *= ( const double other ) { this->pitch *= other; this->yaw *= other; this->roll *= other; return *this; }
		frotator& operator /= ( const double other ) { this->pitch /= other; this->yaw /= other; this->roll /= other; return *this; }

		frotator& operator = ( const frotator& other ) { this->pitch = other.pitch; this->yaw = other.yaw; this->roll = other.roll; return *this; }
		frotator& operator += ( const frotator& other ) { this->pitch += other.pitch; this->yaw += other.yaw; this->roll += other.roll; return *this; }
		frotator& operator -= ( const frotator& other ) { this->pitch -= other.pitch; this->yaw -= other.yaw; this->roll -= other.roll; return *this; }
		frotator& operator *= ( const frotator& other ) { this->pitch *= other.pitch; this->yaw *= other.yaw; this->roll *= other.roll; return *this; }
		frotator& operator /= ( const frotator& other ) { this->pitch /= other.pitch; this->yaw /= other.yaw; this->roll /= other.roll; return *this; }

		operator bool( ) { return bool( this->pitch || this->yaw || this->roll ); }
		friend bool operator == ( const frotator& a, const frotator& b ) { return a.pitch == b.pitch && a.yaw == b.yaw && a.roll == b.roll; }
		friend bool operator != ( const frotator& a, const frotator& b ) { return !(a == b); }

		inline frotator get( ) {
			return frotator( pitch, yaw, roll );
		}

		inline void set( double _Pitch, double _Yaw, double _Roll ) {
			pitch = _Pitch;
			yaw = _Yaw;
			roll = _Roll;
		}

		inline frotator normalize( ) {

			frotator result = get( );

            if ( std::isfinite( result.pitch ) && std::isfinite( result.yaw ) && std::isfinite( result.roll ) ) {
                result.pitch = std::clamp( result.pitch, -89.0, 89.0 );
                result.yaw = std::clamp( result.yaw, -180.0, 180.0 );
                result.roll = 0.f;
                return result;
            }

		}

		double length( ) {
			return sqrt( pitch * pitch + yaw * yaw + roll * roll );
		}

		double Dot( const frotator& V ) { return pitch * V.pitch + yaw * V.yaw + roll * V.roll; }
		double Distance( frotator V ) { return double( sqrtf( powf( V.pitch - this->pitch, 2.0 ) + powf( V.yaw - this->yaw, 2.0 ) + powf( V.roll - this->roll, 2.0 ) ) ); }

		double pitch;
		double yaw;
		double roll;

	};

    struct FRotator
    {
        double                                             Pitch;                                                    // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
        double                                             Yaw;                                                      // 0x0008(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
        double                                             Roll;                                                     // 0x0010(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)

        inline FRotator( )
            : Pitch( 0 ), Yaw( 0 ), Roll( 0 )
        { }

        inline FRotator( double pitch, double yaw, double roll )
            : Pitch( pitch ),
            Yaw( yaw ),
            Roll( roll )
        { }

        __forceinline FRotator operator-( const FRotator& V ) {
            return FRotator( Pitch - V.Pitch, Yaw - V.Yaw, Roll - V.Roll );
        }

        __forceinline FRotator operator+( const FRotator& V ) {
            return FRotator( Pitch + V.Pitch, Yaw + V.Yaw, Roll + V.Roll );
        }

        __forceinline FRotator operator*( float Scale ) const {
            return FRotator( Pitch * Scale, Yaw * Scale, Roll * Scale );
        }

        __forceinline FRotator operator/( float Scale ) const {
            const float RScale = 1.f / Scale;
            return FRotator( Pitch * RScale, Yaw * RScale, Roll * RScale );
        }

        __forceinline FRotator operator+( float A ) const {
            return FRotator( Pitch + A, Yaw + A, Roll + A );
        }

        __forceinline FRotator operator-( float A ) const {
            return FRotator( Pitch - A, Yaw - A, Roll - A );
        }

        __forceinline FRotator operator*( const FRotator& V ) const {
            return FRotator( Pitch * V.Pitch, Yaw * V.Yaw, Roll * V.Roll );
        }

        __forceinline FRotator operator/( const FRotator& V ) const {
            return FRotator( Pitch / V.Pitch, Yaw / V.Yaw, Roll / V.Roll );
        }

        __forceinline float operator|( const FRotator& V ) const {
            return Pitch * V.Pitch + Yaw * V.Yaw + Roll * V.Roll;
        }

        __forceinline float operator^( const FRotator& V ) const {
            return Pitch * V.Yaw - Yaw * V.Pitch - Roll * V.Roll;
        }

        __forceinline FRotator& operator+=( const FRotator& v ) {
            Pitch += v.Pitch;
            Yaw += v.Yaw;
            Roll += v.Roll;
            return *this;
        }

        __forceinline FRotator& operator-=( const FRotator& v ) {
            Pitch -= v.Pitch;
            Yaw -= v.Yaw;
            Roll -= v.Roll;
            return *this;
        }

        __forceinline FRotator& operator*=( const FRotator& v ) {
            Pitch *= v.Pitch;
            Yaw *= v.Yaw;
            Roll *= v.Roll;
            return *this;
        }

        __forceinline FRotator& operator/=( const FRotator& v ) {
            Pitch /= v.Pitch;
            Yaw /= v.Yaw;
            Roll /= v.Roll;
            return *this;
        }

        __forceinline bool operator==( const FRotator& src ) const {
            return ( src.Pitch == Pitch ) && ( src.Yaw == Yaw ) && ( src.Roll == Roll );
        }

        __forceinline bool operator!=( const FRotator& src ) const {
            return ( src.Pitch != Pitch ) || ( src.Yaw != Yaw ) || ( src.Roll != Roll );
        }

        __forceinline double FMod( double a1, double a2 ) {
            if ( a2 > 0.00000001 || a2 < -0.00000001 ) {
                double result = a1 - ( int )( a1 / a2 ) * a2;
                return result;
            }
            else {
                return 0.0;
            }
        }

        __forceinline double ClampAxis( double Angle ) {
            // returns Angle in the range (-360,360)
            Angle = FMod( Angle, ( double )360.f );

            if ( Angle < ( double )0.f ) {
                // shift to [0,360) range
                Angle += ( double )360.f;
            }

            return Angle;
        }

        __forceinline double NormalizeAxis( double Angle ) {
            // returns Angle in the range [0,360)
            Angle = ClampAxis( Angle );

            if ( Angle > ( double )180.f ) {
                // shift to (-180,180]
                Angle -= ( double )360.f;
            }

            return Angle;
        }

        __forceinline double Clamp( double value, double min, double max ) {
            if ( value < min ) {
                return min;
            }
            else if ( value > max ) {
                return max;
            }
            else {
                return value;
            }
        }

        __forceinline void Normalize( ) {
            Pitch = NormalizeAxis( Pitch );
            Yaw = NormalizeAxis( Yaw );
            Roll = NormalizeAxis( Roll );
        }

        fvector Euler( ) const
        {
            return fvector( Pitch, Yaw, Roll );
        }
    };

	struct flinearcolor
	{
		flinearcolor( ) :a( ), r( ), g( ), b( ) { }
		flinearcolor( int8_t a, int8_t r, int8_t g, int8_t b ) : a( a ), r( r ), g( g ), b( b ) { }

		int8_t a, r, g, b;
	};

	struct bounds_t {
		float left, right, top, bottom;
	};



}

static const char* KeyNames[] = {
    "...",
    "Left M",
    "Right M",
    "VK_CANCEL",
    "Middle B",
    "Side B",
    "Side B",
    "Unknown",
    "VK_BACK",
    "VK_TAB",
    "Unknown",
    "Unknown",
    "VK_CLEAR",
    "VK_RETURN",
    "Unknown",
    "Unknown",
    "SHIFT",
    "VK_CONTROL",
    "VK_MENU",
    "VK_PAUSE",
    "VK_CAPITAL",
    "VK_KANA",
    "Unknown",
    "VK_JUNJA",
    "VK_FINAL",
    "VK_KANJI",
    "Unknown",
    "VK_ESCAPE",
    "VK_CONVERT",
    "VK_NONCONVERT",
    "VK_ACCEPT",
    "VK_MODECHANGE",
    "SPACE",
    "VK_PRIOR",
    "VK_NEXT",
    "VK_END",
    "VK_HOME",
    "VK_LEFT",
    "VK_UP",
    "VK_RIGHT",
    "VK_DOWN",
    "VK_SELECT",
    "VK_PRINT",
    "VK_EXECUTE",
    "VK_SNAPSHOT",
    "VK_INSERT",
    "VK_DELETE",
    "VK_HELP",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "VK_LWIN",
    "VK_RWIN",
    "VK_APPS",
    "Unknown",
    "VK_SLEEP",
    "VK_NUMPAD0",
    "VK_NUMPAD1",
    "VK_NUMPAD2",
    "VK_NUMPAD3",
    "VK_NUMPAD4",
    "VK_NUMPAD5",
    "VK_NUMPAD6",
    "VK_NUMPAD7",
    "VK_NUMPAD8",
    "VK_NUMPAD9",
    "VK_MULTIPLY",
    "VK_ADD",
    "VK_SEPARATOR",
    "VK_SUBTRACT",
    "VK_DECIMAL",
    "VK_DIVIDE",
    "VK_F1",
    "VK_F2",
    "VK_F3",
    "VK_F4",
    "VK_F5",
    "VK_F6",
    "VK_F7",
    "VK_F8",
    "VK_F9",
    "VK_F10",
    "VK_F11",
    "VK_F12",
    "VK_F13",
    "VK_F14",
    "VK_F15",
    "VK_F16",
    "VK_F17",
    "VK_F18",
    "VK_F19",
    "VK_F20",
    "VK_F21",
    "VK_F22",
    "VK_F23",
    "VK_F24",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "VK_NUMLOCK",
    "VK_SCROLL",
    "VK_OEM_NEC_EQUAL",
    "VK_OEM_FJ_MASSHOU",
    "VK_OEM_FJ_TOUROKU",
    "VK_OEM_FJ_LOYA",
    "VK_OEM_FJ_ROYA",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "SHIFT",
    "SHIFT",
    "VK_LCONTROL",
    "VK_RCONTROL",
    "VK_LMENU",
    "VK_RMENU"
};
static const int KeyCodes[] = {
    0x0,  //Undefined
    0x01,
    0x02,
    0x03,
    0x04,
    0x05,
    0x06,
    0x07, //Undefined
    0x08,
    0x09,
    0x0A, //Reserved
    0x0B, //Reserved
    0x0C,
    0x0D,
    0x0E, //Undefined
    0x0F, //Undefined
    0x10,
    0x11,
    0x12,
    0x13,
    0x14,
    0x15,
    0x16, //IME On
    0x17,
    0x18,
    0x19,
    0x1A, //IME Off
    0x1B,
    0x1C,
    0x1D,
    0x1E,
    0x1F,
    0x20,
    0x21,
    0x22,
    0x23,
    0x24,
    0x25,
    0x26,
    0x27,
    0x28,
    0x29,
    0x2A,
    0x2B,
    0x2C,
    0x2D,
    0x2E,
    0x2F,
    0x30,
    0x31,
    0x32,
    0x33,
    0x34,
    0x35,
    0x36,
    0x37,
    0x38,
    0x39,
    0x3A, //Undefined
    0x3B, //Undefined
    0x3C, //Undefined
    0x3D, //Undefined
    0x3E, //Undefined
    0x3F, //Undefined
    0x40, //Undefined
    0x41,
    0x42,
    0x43,
    0x44,
    0x45,
    0x46,
    0x47,
    0x48,
    0x49,
    0x4A,
    0x4B,
    0x4C,
    0x4B,
    0x4E,
    0x4F,
    0x50,
    0x51,
    0x52,
    0x53,
    0x54,
    0x55,
    0x56,
    0x57,
    0x58,
    0x59,
    0x5A,
    0x5B,
    0x5C,
    0x5D,
    0x5E, //Rservered
    0x5F,
    0x60, //Numpad1
    0x61, //Numpad2
    0x62, //Numpad3
    0x63, //Numpad4
    0x64, //Numpad5
    0x65, //Numpad6
    0x66, //Numpad7
    0x67, //Numpad8
    0x68, //Numpad8
    0x69, //Numpad9
    0x6A,
    0x6B,
    0x6C,
    0x6D,
    0x6E,
    0x6F,
    0x70, //F1
    0x71, //F2
    0x72, //F3
    0x73, //F4
    0x74, //F5
    0x75, //F6
    0x76, //F7
    0x77, //F8
    0x78, //F9
    0x79, //F10
    0x7A, //F11
    0x7B, //F12
    0x7C, //F13
    0x7D, //F14
    0x7E, //F15
    0x7F, //F16
    0x80, //F17
    0x81, //F18
    0x82, //F19
    0x83, //F20
    0x84, //F21
    0x85, //F22
    0x86, //F23
    0x87, //F24
    0x88, //Unkown
    0x89, //Unkown
    0x8A, //Unkown
    0x8B, //Unkown
    0x8C, //Unkown
    0x8D, //Unkown
    0x8E, //Unkown
    0x8F, //Unkown
    0x90,
    0x91,
    0x92, //OEM Specific
    0x93, //OEM Specific
    0x94, //OEM Specific
    0x95, //OEM Specific
    0x96, //OEM Specific
    0x97, //Unkown
    0x98, //Unkown
    0x99, //Unkown
    0x9A, //Unkown
    0x9B, //Unkown
    0x9C, //Unkown
    0x9D, //Unkown
    0x9E, //Unkown 
    0x9F, //Unkown
    0xA0,
    0xA1,
    0xA2,
    0xA3,
    0xA4,
    0xA5
};