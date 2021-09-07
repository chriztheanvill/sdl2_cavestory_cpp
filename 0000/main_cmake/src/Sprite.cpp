#include "./Sprite.h"
#include "./Graphics.h"
#include "./Constants.h"

#include <fmt/color.h>

// Sprite::Sprite( ) {}
//
// Sprite::~Sprite( ) {}

Sprite::Sprite(Graphics& graphics,
			   const std::string& path,
			   SDL_Rect& source,
			   SDL_Rect& pos)
	: mSource(source)
	, mPos(pos) {
	// Obtener Surface
	mSpriteSheet = SDL_CreateTextureFromSurface(graphics.GetRenderer( ),
												graphics.LoadImage(path));

	/* ************************** Check error ************************** */
	if (!mSpriteSheet) {
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "Error!!! Loading Image");
		exit(1);
	}

	// Crear colisionador
	mBoundingBox =
		std::make_unique<Rectangle>(mPos.x,
									mPos.y,
									mSource.w * Constants::SPRITE_SCALE,
									mSource.h * Constants::SPRITE_SCALE);
}	// Constructor

/* ####################################################################### */
/* ####################################################################### */
void Sprite::Draw(Graphics& graphics, SDL_Rect& pos) {
	SDL_Rect dest {
		pos.x,
		pos.y,
		static_cast<int>(mSource.w * Constants::SPRITE_SCALE),
		static_cast<int>(mSource.h * Constants::SPRITE_SCALE)	//
	};

	graphics.blitSurface(mSpriteSheet, &mSource, &dest);
}	// DRAW

/* ####################################################################### */
/* ####################################################################### */
void Sprite::Update(float DeltaTime) {
	// fmt::print("Sprite Update\n\n");

	// Example
	// mBoundingBox = Rectangle(mPos.x,
	// 						 mPos.y,
	// 						 mSource.w * Constants::SPRITE_SCALE,
	// 						 mSource.h * Constants::SPRITE_SCALE);

	// El colisionador sigue a el sprite.
	(*mBoundingBox)(mPos.x,
					mPos.y,
					mSource.w * Constants::SPRITE_SCALE,
					mSource.h * Constants::SPRITE_SCALE);

	// mBoundingBox->Update(mPos.x,
	// 					 mPos.y,
	// 					 mSource.w * Constants::SPRITE_SCALE,
	// 					 mSource.h * Constants::SPRITE_SCALE);
}

/* ####################################################################### */
/* ####################################################################### */
Rectangle* Sprite::getBoundingBox( ) { return mBoundingBox.get( ); }

/* ####################################################################### */
/* ####################################################################### */
const Sides::Side Sprite::getCollisionSide(const Rectangle& other) const {
	// What is biggest amount is INSIDE of the other rectangle

	int amtRight = abs(mBoundingBox->getRight( ) - other.getLeft( ));
	int amtLeft = abs(other.getRight( ) - mBoundingBox->getLeft( ));
	int amtTop = abs(other.getBottom( ) - mBoundingBox->getTop( ));
	int amtBottom = abs(mBoundingBox->getBottom( ) - other.getTop( ));

	int lowest = amtRight;
	for (const int low : { amtRight, amtLeft, amtTop, amtBottom }) {
		if (low < lowest) { lowest = low; }
	}

	return lowest == amtRight  ? Sides::Side::RIGHT :
		   lowest == amtLeft   ? Sides::Side::LEFT :
		   lowest == amtTop	   ? Sides::Side::TOP :
		   lowest == amtBottom ? Sides::Side::BOTTOM :
								   Sides::Side::NONE;
}
