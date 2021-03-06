/**
 *
 * @brief Class Name: AnimatedTile.cpp --
 *
 * Written on viernes, 17 septiembre 2021.
 ***/

//-------------------------------//

#include "AnimatedTile.h"
#include "Graphics.h"

//-------------------------------//

// Constructor:
AnimatedTile::AnimatedTile(std::vector<Vec2> tilesetPos,
						   int duration,
						   SDL_Texture* tileset,
						   Vec2 size,
						   Vec2 pos)
	: Tile(tileset, size, tilesetPos.at(0), pos)
	, mTilePositions(tilesetPos)
	, mDuration(duration)
	, mTileToDraw(0) {
	// Code...
}
//-------------------------------//

// Destructor:
AnimatedTile::~AnimatedTile( ) {
	// Code...
}
//-------------------------------//

void AnimatedTile::update(float deltaTime) {
	if (mAmountOfTime <= 0) {
		if (mTileToDraw == mTilePositions.size( ) - 1) {
			mTileToDraw = 0;
		} else {
			mTileToDraw++;
		}
		mAmountOfTime = mDuration;
	} else {
		mAmountOfTime -= (deltaTime * 1000);
	}

	Tile::Update(deltaTime);
}

void AnimatedTile::draw(Graphics& graphics) {
	SDL_Rect destRect { mDestTile.x,
						mDestTile.y,
						mSize.x * Constants::SPRITE_SCALE,
						mSize.y * Constants::SPRITE_SCALE };

	SDL_Rect sourceRect { mTilePositions.at(mTileToDraw).x,
						  mTilePositions.at(mTileToDraw).y,
						  mSize.x,
						  mSize.y };

	graphics.blitSurface(mTileSet, &sourceRect, &destRect);
}
