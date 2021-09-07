#ifndef SLOPE_H
#define SLOPE_H

#include "./Constants.h"
#include <cmath>
#include "./Rectangle.h"

class Slope {
  public:
	Slope( )
		: Slope(Vec2( ), Vec2( )) {}

	Slope(Vec2 p1, Vec2 p2)
		: mP1(p1)
		, mP2(p2) {
		/* Calcular Slope
			m = y1 - y2 / x1 - x2 */
		if (mP2.x - mP1.x != 0) {
			mSlope = (fabs(mP2.y) - fabs(mP1.y)) / (fabs(mP2.x) - fabs(mP1.x));
		}
	}

	constexpr float getSlope( ) const { return mSlope; }

	constexpr bool collidesWith(const Rectangle& other) const {
		return	 // Bottom to Top
			(/* Right Top
				P1 esta de lado derecho Arriba
				P2 esta de lado Izquierdo Abajo */
			 other.getRight( ) >= mP2.x &&	 //
			 other.getLeft( ) <= mP1.x &&	//
			 other.getTop( ) <= mP2.y &&   //
			 other.getBottom( ) >= mP1.y   //
			 ) ||	// OR
			(/* Right Top
			 P2 esta de lado derecho Arriba
			 P1 esta de lado Izquierdo Abajo */
			 other.getRight( ) >= mP1.x &&	 //
			 other.getLeft( ) <= mP2.x &&	//
			 other.getTop( ) <= mP1.y &&   //
			 other.getBottom( ) >= mP2.y   //
			 ) ||
			(/*	Left
				P1 esta de lado derecho Abajo
				P2 esta de lado Izquierdo Arriba */
			 other.getLeft( ) <= mP1.x &&	//
			 other.getRight( ) >= mP2.x &&	 //
			 other.getTop( ) <= mP1.y &&   //
			 other.getBottom( ) >= mP2.y   //
			 ) ||	//
			(	//
				other.getLeft( ) <= mP2.x &&   //
				other.getRight( ) >= mP1.x &&	//
				other.getTop( ) <= mP2.y &&	  //
				other.getBottom( ) >= mP1.y	  //
			);
	}

	inline Vec2 getP1( ) const { return mP1; }
	inline Vec2 getP2( ) const { return mP2; }

  private:
	Vec2 mP1 { }, mP2 { };
	float mSlope;
};

#endif