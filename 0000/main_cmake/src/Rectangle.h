#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "./Constants.h"
#include <fmt/color.h>

/**
 * @brief Kind of SDL_Rect.
 *
 */
class Rectangle {
  public:
	Rectangle( )
		: Rectangle(0, 0, 0, 0) {}

	Rectangle(int x, int y, int w, int h)
		: mX(x)
		, mY(y)
		, mW(w)
		, mH(h) {}

	/**
	 * @brief Just for testing: DELETE AFTER
	 */
	virtual ~Rectangle( ) = default;

	// Rectangle& operator=(const Rectangle& other) {
	// 	if (this != &other) {
	// 		mX = other.mX;
	// 		mY = other.mY;
	// 		mW = other.mW;
	// 		mH = other.mH;
	// 	}
	// 	/**/
	// }

	// void operator( )(const Rectangle& other) {
	// 	mX = other.mX;
	// 	mY = other.mY;
	// 	mW = other.mW;
	// 	mH = other.mH;
	// }

	void operator( )(const int& x, const int& y, const int& w, const int& h) {
		mX = x;
		mY = y;
		mW = w;
		mH = h;
	}

	constexpr int getCenterX( ) const { return mX + mW / 2; }
	constexpr int getCenterY( ) const { return mY + mH / 2; }

	constexpr int getLeft( ) const { return mX; }
	constexpr int getRight( ) const { return mX + mW; }
	constexpr int getTop( ) const { return mY; }
	constexpr int getBottom( ) const { return mY + mH; }

	constexpr int getWidth( ) const { return mW; }
	constexpr int getHeight( ) const { return mH; }

	constexpr int getSide(const Sides::Side side) const {
		return side == Sides::Side::LEFT   ? getLeft( ) :
			   side == Sides::Side::RIGHT  ? getRight( ) :
			   side == Sides::Side::TOP	   ? getTop( ) :
			   side == Sides::Side::BOTTOM ? getBottom( ) :
											   side == Sides::Side::NONE;
	}

	constexpr bool collidesWith(const Rectangle& other) const {
		return getRight( ) >= other.getLeft( ) &&
			   getLeft( ) <= other.getRight( ) &&
			   getTop( ) <= other.getBottom( ) &&
			   getBottom( ) >= other.getTop( );
	}

	constexpr bool isValidRectangle( ) const {
		return (mX >= 0 && mY >= 0 && mW >= 0 && mH >= 0);
	}

	constexpr bool isZeroRectangle( ) const {
		return (mX == 0 && mY == 0 && mW == 0 && mH == 0);
	}

	void Update(int x, int y, int w, int h) {
		mX = x;
		mY = y;
		mW = w;
		mH = h;
	}

  private:
	int mX;
	int mY;
	int mW;
	int mH;
};

#endif	 // RECTANGLE_H

/*
 * 3 5  -  8 11
 * 5 7
 * Bottom 10
 *
 * Top 7
 *
 * Bottom 14
 *
 * */
