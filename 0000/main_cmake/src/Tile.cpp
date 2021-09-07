//
// Created by cris on 29/04/21.
//

/* Tiled
Orientation: Orthogonal
Tile layer format: CSV
Tile render order: Right Down

Map Size:
W: 20 tiles
H: 16 Tiles

Tile size:
W: 16 px
H: 16 px

New TileSet
Name: PrtCave
Type: Based on Tileset Image
*/

#include "Tile.h"
#include "./Graphics.h"

#include <SDL2/SDL.h>
#include <fmt/color.h>

// Tile::Tile( ) {
// 	//
// }

Tile::Tile(SDL_Texture* tileset, Vec2 size, Vec2 sourceTile, Vec2 destTile)
	: mTileSet(tileset)
	, mSize(size)
	, mSourceTile(sourceTile)
	, mDestTile(Vec2(destTile.x * Constants::SPRITE_SCALE,
					 destTile.y * Constants::SPRITE_SCALE)) {}

void Tile::Update(float deltaTime) {
	//
}

void Tile::Draw(Graphics& graphics) {
	SDL_Rect dr { mDestTile.x,
				  mDestTile.y,
				  mSize.x * static_cast<int>(Constants::SPRITE_SCALE),
				  mSize.y * static_cast<int>(Constants::SPRITE_SCALE) };

	SDL_Rect sr { mSourceTile.x, mSourceTile.y, mSize.x, mSize.y };

	graphics.blitSurface(mTileSet, &sr, &dr);
}
