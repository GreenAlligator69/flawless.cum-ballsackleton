#ifndef FRAMEWORK_HPP
#define FRAMEWORK_HPP

using request = enum {
	m_endframe,
	m_rectangle,
	m_fill_rect,
	m_line,
	m_circle,
	m_text,
	m_boundingbox,
	m_boundingcorner,
	m_icon
};

using vec2 = struct {
	float x, y;
};

using rect_t = struct {
	float x, y, height, width;
};

using rectangle_t = struct {

	rect_t object;
	uemath::flinearcolor color;
	vec2 radius;
	bool rounded;

};

using bounding_t = struct {
	float left, right, top, bottom;
	uemath::flinearcolor color;
	bool rounded;
};

using line_t = struct {
	vec2 point1, point2;
	uemath::flinearcolor color;
	float stroke;
};

using icon_t = struct {
	vec2 point;
	uemath::flinearcolor color;
	float fontSize;
	int icon;
};

using circle_t = struct {
	vec2 point;
	float radius;
	uemath::flinearcolor color;
	float stroke;
	bool filled;
};

using text_t = struct {

	std::uint32_t text_length;
	std::string text;
	vec2 point;
	uemath::flinearcolor color;
	float fontSize;
	bool center;
	bool menu;
	int weight;
};

class c_framework {

public:

	// use a class constructor 
	explicit c_framework( ) { };

	void initializer( );

	[[nodiscard]] uemath::flinearcolor get_color( std::int8_t r, std::int8_t g, std::int8_t b, std::int8_t a = 255 );
	[[nodiscard]] bool send_cmd( void* data, request code );

	void end_scene( );
	void begin_scene( );
	void release( );

	void bounding_corner( const uemath::fvector& position, const uemath::fvector& size, uemath::flinearcolor color );
	void text( const std::string& input, float x, float y, uemath::flinearcolor color, float fontSize, bool center, int weight = 1, bool menu = false );
	void rect( float x, float y, float width, float height, uemath::flinearcolor color, bool rounded = false, float _x = 0, float _y = 0 );
	void filled_rect( float x, float y, float width, float height, uemath::flinearcolor color, bool rounded = false, float _x = 0, float _y = 0 );
	void line( float x1, float y1, float x2, float y2, uemath::flinearcolor color, float stroke = 1.0f );
	void circle( float x, float y, float radius, uemath::flinearcolor color, float stroke, bool filled = false );

	void crosshair( );
	void fov( );


}; inline auto framework = std::make_unique<c_framework>( );

#endif