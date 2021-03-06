/**
 * @brief AnimatedTile.h --
 *
 * Written on miércoles, 15 septiembre 2021.
 */

#ifndef _AnimatedTile_H
#define _AnimatedTile_H

//-------------------------------//

#include "./Tile.h"

#include <SDL2/SDL.h>

#include <vector>

class AnimatedTile : public Tile {
  public:
	AnimatedTile(std::vector<Vec2> tilesetPos,
				 int duration,
				 SDL_Texture* tileset,
				 Vec2 size,
				 Vec2 pos);

	// AnimatedTile(const AnimatedTile&);
	// AnimatedTile(AnimatedTile&&) noexcept;
	// AnimatedTile& operator=(const AnimatedTile&);
	// AnimatedTile& operator=(AnimatedTile&&) noexcept;
	~AnimatedTile( );

	/**
	 * @brief Sometext
	 *
	 * @params DeltaTime
	 */
	void update(float deltaTime);
	void draw(Graphics& graphics);

  protected:
	float mAmountOfTime { };
	bool mNotDone { };

  private:
	std::vector<Vec2> mTilePositions;
	int mTileToDraw;
	int mDuration;
};

//-------------------------------//

struct AnimatedTileInfo {
	//
	int TilesetsFirstGid;
	int StartTileId;
	std::vector<int> TileIds;
	int Duration;
};

#endif	 //  _AnimatedTile_H
