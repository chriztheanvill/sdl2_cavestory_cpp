#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants {

	constexpr unsigned int FIRST_SCREEN = 0;
	constexpr unsigned int SECOND_SCREEN = 1;

	constexpr int SCREEN_WIDTH = 600;
	constexpr int SCREEN_HEIGHT = 600;

	constexpr int SPRITE_SCALE { 2 };

	// constexpr int FPS = 30;
	inline constexpr unsigned int FPS = 60;
	// How much EACH frame should take in milliseconds to run
	inline constexpr unsigned int FRAME_TARGET_TIME = 1000 / FPS;
}	// namespace Constants

namespace Sides {
	enum class Side { TOP, BOTTOM, LEFT, RIGHT, NONE };

	constexpr Side getOppositeSide(Side side) {
		return side == Side::TOP	? Side::BOTTOM :
			   side == Side::BOTTOM ? Side::TOP :
			   side == Side::LEFT	? Side::RIGHT :
			   side == Side::RIGHT	? Side::LEFT :
										Side::NONE;
	}
}	// namespace Sides

enum class Direction { LEFT, RIGHT, UP, DOWN };

/* TODO Make a class of Vec2D */
struct Vec2 {
	int x { };
	int y { };
	Vec2( )
		: Vec2(0, 0) {}
	Vec2(int xx, int yy)
		: x(xx)
		, y(yy) {}

	// const static Vec2 Zero;
	// static const Vec2 Zero;
	// static Vec2 Zero( ) { return Vec2( ); }
	// Vec2 Zero( ) { return Vec2( ); }
	Vec2 Zero( ) { return { }; }
};

#endif	 //	CONSTANTS_H
