//
// Created by cris on 29/04/21.
//

#ifndef TILE_H
#define TILE_H

#include "./Constants.h"

struct SDL_Texture;
class Graphics;

class Tile {
  public:
	Tile( ) = default;
	Tile(SDL_Texture* tileset, Vec2 size, Vec2 sourceTile, Vec2 destTile);
	void Update(float deltaTime);
	void Draw(Graphics& graphics);

  protected:
	Vec2 mSize;
	Vec2 mSourceTile;
	Vec2 mDestTile;	  // Position
	SDL_Texture* mTileSet;

  private:
};

#endif	 // TILE_H
