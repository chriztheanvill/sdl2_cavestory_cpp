#include "./Level.h"
#include "./Graphics.h"
#include "Constants.h"

#include <fmt/core.h>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <SDL2/SDL.h>

#include <fmt/color.h>

#include <sstream>
#include <algorithm>
#include <cmath>

using nlohmann::json;

// Level::Level( ) {}

Level::Level(const std::string& mapName, Vec2 spawnPoint, Graphics& graphics)
	: mMapName(mapName)
	, mSpawnPoint(spawnPoint)
	, mSize(Vec2( )) {
	// , mSize(Vec2::Zero( )) {
	LoadMap(mapName, graphics);
}

// Level::~Level(){}

// TODO(Cris) Slice this code
void Level::LoadMap(const std::string& mapName, Graphics& graphics) {
	/* #######################################################
############## Get Main JSON ###############
####################################################### */
	std::stringstream ssMap { };

	if (mMapName.empty( )) {
		ssMap << "assets/tilemaps/" << mapName << ".json";
	} else {
		ssMap << "assets/tilemaps/" << mMapName << ".json";
	}

	std::ifstream ifsTileSet(ssMap.str( ));
	/* *********************** Check ERROR *********************** */
	if (!ifsTileSet.is_open( )) {
		fmt::print("Error loading JSON File --TILESET-- !!!");
		exit(1);
	}

	json jTileSet;
	ifsTileSet >> jTileSet;
	/* *********************** Check ERROR *********************** */
	if (jTileSet.empty( )) {
		fmt::print("Error - JSON TileSet File is EMPTY!!!");
		exit(1);
	}

	/* #########################################################################
############################# Get 1st gid #############################
######################################################################### */

	/* ############################################### Check if are tilesets */

	if (jTileSet["tilesets"].empty( )) {
		fmt::print("Error, THERE IS NOT TILESETS!!!\n\n ");
		exit(1);
	}
	// std::cout << jTileSet["layers"][0]["data"] << "\n";

	// std::cout << "\n Gids Amount: " << jTileSet["tilesets"].size( ) <<
	// "\n\n";

	int tile_increment { };

	if (jTileSet["tilesets"].size( ) > 1) { tile_increment = 1; }

	for (const auto& v : jTileSet["tilesets"]) {
		// std::cout << "ImageName: " << v["source"] << "\n";
		// std::cout << "firstgid: " << v["firstgid"] << "\n";
		// std::cout << "Nextgid: "
		// 		  << jTileSet["tilesets"][tile_increment]["firstgid"] << "\n";

		std::string imagePath = v["source"].get<std::string>( );

		int lastGid =
			jTileSet["tilesets"].size( ) == 1 ?
				  0 :
			jTileSet["tilesets"].size( ) == tile_increment ?
				  jTileSet["tilesets"][tile_increment - 1]["firstgid"]
						.get<int>( ) *
					2 :
				  jTileSet["tilesets"][tile_increment]["firstgid"].get<int>( );

		// std::cout << "tile increment: " << tile_increment << "\n";
		// std::cout << "lastGig: " << lastGid << "\n\n";

		if (tile_increment < jTileSet["tilesets"].size( )) { tile_increment++; }
		// if (tile_increment < jTileSet["tilesets"].size( ) - 1) {
		// 	tile_increment++;
		// }

		mTileSets.emplace_back(	  //
			Tileset(
				SDL_CreateTextureFromSurface(
					graphics.GetRenderer( ),
					graphics.LoadImage(std::string(
						"assets/images/" +
						imagePath.substr(0, imagePath.size( ) - 5) + ".png"))),
				v["source"].get<std::string>( ),
				v["firstgid"].get<int>( ),
				lastGid));
	}

	/* ###################################################################
######################################################################
################################################################### */

	// Image size
	int screenWidth = jTileSet["width"].get<int>( );
	int screenHeight = jTileSet["height"].get<int>( );
	mSize = Vec2(screenWidth, screenHeight);

	// Tiles sizes
	int tileW = jTileSet["tilewidth"].get<int>( );
	int tileH = jTileSet["tileheight"].get<int>( );
	mTileSize = Vec2(tileW, tileH);

	/* #################################################### Get 1st gid */
	/* ************************************************* */
	/* ************************************************* */

	Tileset tls;

	fmt::print("\n Layers Amount: {}\n", jTileSet["layers"].size( ));
	// std::cout << "\n Layers Amount: " << jTileSet["layers"].size( ) <<
	// "\n\n";

	for (const auto& val : jTileSet["layers"]) {
		// std::cout << val << "\n";
		// std::cout << val["data"] << "\n";
		int xx { };
		int yy { };
		/* ############################### CHECK ALL Data Values */
		// Data :: tile of the image

		fmt::print("\n--Type values: {}", val["type"].get<std::string>( ));

		// Checks, is a TileLayer
		if (val["type"].get<std::string>( ) == "tilelayer") {
			//
			// fmt::print("++++tilelayer data: {}\n", val["data"].empty( ));
			// fmt::print("####################### gidCounter: {}\n",
			// gidCounter);

			for (int tileCounter { }; const auto& data_gid : val["data"]) {
				/* data_gid == 0, Nothing to DRAW */
				if (data_gid != 0) {   // Has a value to DRAW
					/* **************** Go through all values ****************
					 */
					// GET THE DESTINATION X, Y

					/*	Will check all columns,
						  Width is the limit with mod, then start again */
					xx = tileW * (tileCounter % screenWidth);
					// xx = tileCounter % screenWidth;
					// xx *= tileW;

					yy = tileH * (tileCounter / screenWidth);
					/* (tileCounter / screenWidth)
					   Works as Integer, so if the result is 21/16 == 1 */

					Vec2 destTile(xx, yy);
					/* *************** ~Go through all values *************** */

					/* ************Get the correct tileset ************ */
					if (jTileSet["tilesets"].size( ) > 1) {
						for (const auto& t : mTileSets) {
							// std::cout << "++++++++++++++++++++True\n";
							// std::cout << "t.first: " << t.mFirstGid
							// 		  << " - t.next: " << t.mNextGid
							// 		  << " - t.Source: " << t.mImageName
							// 		  << "\n gid: " << data_gid << "\n\n";
							if (data_gid >= t.mFirstGid &&
								data_gid < t.mNextGid) {
								// std::cout << "++++ ++++ t.first: " <<
								// t.mFirstGid
								// 		  << " - t.next: " << t.mNextGid
								// 		  << " - t.Source: " << t.mImageName
								// 		  << "\n    gid: " << data_gid <<
								// "\n\n";
								tls.mFirstGid = t.mFirstGid;
								tls.mNextGid = t.mNextGid;
								tls.mTexture = t.mTexture;
							} else {
								// std::cout << "- t.first: " << t.mFirstGid
								// 		  << " - t.next: " << t.mNextGid
								// 		  << "\n    gid: " << data_gid <<
								// "\n\n";
							}	// Else
						}	// For
					} else {   // There is only ONE tileset
						// std::cout << "-------------------------else\n";
						tls.mFirstGid = mTileSets.begin( )->mFirstGid;
						tls.mNextGid = mTileSets.begin( )->mNextGid;
						tls.mTexture = mTileSets.begin( )->mTexture;
					}
					/* ************Get the correct tileset ************ */

					int tileQueryW { };
					int tileQueryH { };
					SDL_QueryTexture(tls.mTexture,
									 nullptr,
									 nullptr,
									 &tileQueryW,
									 &tileQueryH);

					// static_cast<int>(data_gid) % (tileQueryW / tileH) - 1;
					// --------- 34 -------------------- 256 ------- 16 ---- 1
					// --------- 33 -------------------- 256 ------- 16 ---- 1

					/* TODO implement for many gids */

					// int n_data { };
					// if (jTileSet["tilesets"].size( ) > 1 &&
					// 	data_gid.get<int>( ) != 0) {
					// 	fmt::print("\ndatagid: {} \n", data_gid.get<int>( ));
					// 	fmt::print("++++ div: {} \n",
					// 			   data_gid.get<int>( ) /
					// 				   jTileSet["tilesets"].size( ));
					// 	n_data =
					// 		data_gid.get<int>( ) / jTileSet["tilesets"].size( );
					// }

					// GET THE SOURCE X, Y

					// fmt::print("tile size W: {}\n", tileQueryW);
					// fmt::print("tile size H: {}\n", tileQueryH);

					int tsxx { data_gid.get<int>( ) % (tileQueryW / tileW) -
							   1 };
					tsxx *= tileW;

					int tsyy { };
					int amt { data_gid.get<int>( ) / (tileQueryW / tileH) };
					tsyy = tileH * amt;

					Vec2 sourceTile(tsxx, tsyy);

					Tile tile(tls.mTexture,
							  Vec2(tileW, tileH),
							  sourceTile,
							  destTile);

					mTileList.push_back(tile);

					//				std::cout << "tsxx: " << tsxx << "\n";
					//				std::cout << "Datagid: " << data_gid <<
					//"\n";
				}	// if data_gid

				tileCounter++;
				// std::cout << "\n";
			}	// Data values
		}	// IF

		// std::cout << "\n\n ----------------------------";

		/* ######################## Get collisions ######################## */
		if (val["type"].get<std::string>( ) == "objectgroup") {
			for (const auto& ob : val["objects"]) {
				/* #################### Collision #################### */
				if (val["name"].get<std::string>( ) == "Collisions") {
					// fmt::print("\n++++++++++++++++++++++++++Collisions\n");

					mCollisionRects.emplace_back(
						Rectangle(std::ceil(ob["x"].get<int>( )) *
									  Constants::SPRITE_SCALE,
								  std::ceil(ob["y"].get<int>( )) *
									  Constants::SPRITE_SCALE,
								  std::ceil(ob["width"].get<int>( )) *
									  Constants::SPRITE_SCALE,
								  std::ceil(ob["height"].get<int>( )) *
									  Constants::SPRITE_SCALE));

					/* #################### Spawn Point #################### */
				} else if (val["name"].get<std::string>( ) == "Spawn_Point") {
					mSpawnPoints.emplace(	//
						ob["name"].get<std::string>( ),
						Vec2(std::ceil(ob["x"].get<int>( )) *
								 Constants::SPRITE_SCALE,
							 std::ceil(ob["y"].get<int>( )) *
								 Constants::SPRITE_SCALE));

					fmt::print("\n Amount of SpawnPoints: {}",
							   mSpawnPoints.size( ));
					fmt::print("\n SpawnPoints x: {} - y: {}\n",
							   mSpawnPoints["Player"].x,
							   mSpawnPoints["Player"].y);

					/* ####################### Slopes ####################### */
				} else if (val["name"].get<std::string>( ) == "Slopes") {
					fmt::print("\n\n+++++++++++++++Slope: \n");
					// Slope Position
					// fmt::print("\nX: {}", ob["x"].get<int>( ));
					// fmt::print("\nY: {}", ob["y"].get<int>( ));

					/* Each polyline */
					for (int pass { }; const auto& poly : ob["polyline"]) {
						// Quitar primer coordenada
						// (0,0)
						if (poly["x"].get<int>( ) != 0 &&
							poly["y"].get<int>( ) != 0) {
							// fmt::print("\npolyX: {}", poly["x"].get<int>( ));
							// fmt::print("\npolyY: {}", poly["y"].get<int>( ));
							// fmt::print("\n----\
							//

							//
							//
							int obX = std::ceil(ob["x"].get<int>( ));
							int obY = std::ceil(ob["y"].get<int>( ));
							int polX = poly["x"].get<int>( );
							int polY = poly["y"].get<int>( );
							int sumX = polX + obX;
							int sumY = polY + obY;

							fmt::print("\nobX: {}", obX);
							fmt::print("\nobY: {}", obY);
							fmt::print("\npolyX: {}", polX);
							fmt::print("\npolyY: {}", polY);
							fmt::print("\nSumX: {}", sumX);
							fmt::print("\nSumY: {}", sumY);
							fmt::print("\n----\n");

							/* A cada Slope,
							 *	* Se le Quita la primer coordenada
							 *	*	* Que es (0, 0)
							 *	* Se le suma el punto de origen
							 *	(x, y).
							 */
							mSlopes.emplace_back(Slope(
								// P1
								Vec2(obX * Constants::SPRITE_SCALE,
									 obY * Constants::SPRITE_SCALE),   // Vec
								// P2
								Vec2(sumX * Constants::SPRITE_SCALE,
									 sumY * Constants::SPRITE_SCALE)   // Vec
								)	// Slope
							);	 // Vector Slope

							// -------------------------------
							// mSlopes.emplace_back(Slope(
							// 	// P1
							// 	Vec2(std::ceil(ob["x"].get<int>( )),
							// 		 std::ceil(ob["y"].get<int>( ))),	// Vec
							// 	// P2
							// 	Vec2(std::ceil(ob["x"].get<int>( )) +
							// 			 poly["x"].get<int>( ) *
							// 				 Constants::SPRITE_SCALE,
							// 		 std::ceil(ob["y"].get<int>( )) +
							// 			 poly["y"].get<int>( ) *
							// 				 Constants::SPRITE_SCALE)	// Vec
							// 	)	// Slope
							// );	 // Vector Slope
						}	// If pass != 0

						// fmt::print("\npass: {}\n", pass);
						pass++;
					}	// For PolyLine
				}	// Else if Slopes
			}	// For Objects
		}	// if objectgroup
		/* ######################## Get collisions ######################## */
		// std::cout << "\n\n ----------------------------";
	}	// for layers
	/* ######################################### */
}	// LoadMap

// #####################################################################
// #####################################################################
void Level::Update(float DeltaTime) {
	//	SDL_Log("\nLevel Update.");
}	// Update

// #####################################################################
// #####################################################################
void Level::Draw(Graphics& graphics) {
	for (auto& tl : mTileList) { tl.Draw(graphics); }
}

// #####################################################################
// #####################################################################
std::vector<Rectangle> Level::checkTileCollisions(const Rectangle& other) {
	std::vector<Rectangle> rect_collided;

	if (!other.isZeroRectangle( )) {   // Los valores son mayor a 0
		for (const auto& v : mCollisionRects) {
			if (v.collidesWith(other)) { rect_collided.push_back(v); }
		}
	} else {   // Esta vacio el rectangulo
		fmt::print("\n\nother empty");
	}

	return rect_collided;
}

std::vector<Slope> Level::checkSlopeCollisions(const Rectangle& other) {
	std::vector<Slope> rect_return;
	for (int slopes { }; const auto& s : mSlopes) {
		if (s.collidesWith(other)) { rect_return.emplace_back(s); }
	}

	return rect_return;
}
