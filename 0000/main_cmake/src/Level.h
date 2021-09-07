#ifndef LEVEL_H
#define LEVEL_H

#include "./Constants.h"
#include "./Tile.h"
#include "./Rectangle.h"
#include "./Slope.h"

#include <string>
#include <vector>
#include <map>

class Graphics;
struct SDL_Texture;
struct SDL_Rect;

struct Tileset {
	SDL_Texture* mTexture { };
	int mFirstGid { };
	int mNextGid { };
	std::string mImageName { };

	Tileset( ) {
		mFirstGid = -1;
		mNextGid = -1;
		mImageName = "";
	}

	Tileset(SDL_Texture* texture,
			const std::string& imageName,
			int firstGid,
			int nextGid = -1) {
		mTexture = texture;
		mImageName = imageName;
		mFirstGid = firstGid;
		mNextGid = nextGid;
	}
};

class Level {
  public:
	Level( ) = default;
	Level(const std::string& mapName, Vec2 spawnPoint, Graphics& graphics);

	void Update(float DeltaTime);
	void Draw(Graphics& graphics);
	std::vector<Rectangle> checkTileCollisions(const Rectangle& other);
	std::vector<Slope> checkSlopeCollisions(const Rectangle& other);

	Vec2 getPlayerSpawnPoint( ) { return mSpawnPoints["Player"]; }

  private:
	std::string mMapName;
	Vec2 mSpawnPoint;
	Vec2 mSize;
	Vec2 mTileSize;

	SDL_Texture* mBgTexture { };
	std::vector<Tile> mTileList;
	std::vector<Tileset> mTileSets;
	std::vector<Rectangle> mCollisionRects;
	std::map<std::string, Vec2> mSpawnPoints;
	std::vector<Slope> mSlopes;

	/**
	 * @brief Loads a Map file
	 *
	 * @param mapName string
	 * @param graphics Graphics
	 */
	void LoadMap(const std::string& mapName, Graphics& graphics);
};

#endif	 //	LEVEL_H
