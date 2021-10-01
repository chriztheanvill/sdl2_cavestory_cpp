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
#include <vector>

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
	// ifsTileSet.close( );
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

	int AmountTileSets = jTileSet["tilesets"].size( );

	fmt::print("\n Gids Amount: {}\n", jTileSet["tilesets"].size( ));

	int tile_increment { };
	if (jTileSet["tilesets"].size( ) > 1) { tile_increment = 1; }

	std::ifstream ifsTilePath;
	json jTilePath;

	for (const auto& v : jTileSet["tilesets"]) {
		std::cout << "ImageName: " << v["source"] << "\n";
		std::cout << "firstgid: " << v["firstgid"] << "\n";

		/* Get the first, if is 1 = 0
		 Solo se usa para sumar */

		int firstGidSum = v["firstgid"].get<int>( ) - 1;

		// int firstGidSum =
		// 	v["firstgid"].get<int>( ) == 1 ? 0 : v["firstgid"].get<int>( );

		/* Get first git, Detect */

		int firstGid = v["firstgid"].get<int>( );

		/* Get last Gid, if is 1, last is 0, else is 4 times the last */

		int lastGid =
			// Si solo hay un solo tile, = 0
			AmountTileSets == 1 ? 0 :
			AmountTileSets == tile_increment ?
									// Si es el ultimo tile, se multiplica por 5
				  /* jTileSet["tilesets"][tile_increment - 1]["firstgid"] */
				  /* .get<int>( ) * */
				  firstGid * 5 :
				  // Se obtiene el tile
				  jTileSet["tilesets"][tile_increment]["firstgid"].get<int>( );

		if (tile_increment < AmountTileSets) { tile_increment++; }
		// if (tile_increment < jTileSet["tilesets"].size( ) - 1) {
		// tile_increment++; }

		/* Get the path of the tiles */

		const std::string imagePath = v["source"].get<std::string>( );

		ifsTilePath.open(std::string("assets/images/" + imagePath));
		fmt::print("imagepath: {}\n",
				   std::string("assets/images/" + imagePath));

		/* Obtener la info del archivo */

		if (!ifsTilePath.is_open( )) {
			fmt::print("\nError, Cant find tiles path\n");
			exit(1);
		}

		ifsTilePath >> jTilePath;
		if (jTilePath.empty( )) {
			fmt::print("\nError - JSON TilePath is EMPTY!!!");
			exit(1);
		}

		/* Add Animated Tiles */
		bool IsAnimated { };

		if (jTilePath["tiles"] != nullptr) {
			// fmt::print("\n Es un Tile Animado\n");

			IsAnimated = true;
			/* Cada tile Animado */

			for (const auto& v2 : jTilePath["tiles"]) {
				AnimatedTileInfo ati;
				int Tileid = v2["id"].get<int>( );
				// fmt::print("Tile id: {}\n", Tileid);

				/* Se obtiene la ubicacion en el mapa */
				int TileAnimado = Tileid + firstGid;

				// fmt::print("TileAnimado: {}\n", TileAnimado);

				ati.StartTileId = TileAnimado;
				ati.TilesetsFirstGid = firstGid;

				/* Cada animacion */

				for (const auto& v3 : v2["animation"]) {
					ati.TileIds.push_back(v3["tileid"].get<int>( ) + firstGid);
					ati.Duration = v3["duration"].get<int>( );
				}	// for v3
				mAnimatedTileInfos.push_back(ati);
			}	// For v2
		}	// If jTilePath != nullptr

		/* Add single tiles */

		mTileSets.emplace_back(Tileset(
			SDL_CreateTextureFromSurface(
				graphics.GetRenderer( ),
				graphics.LoadImage(std::string(
					"assets/images/" +
					imagePath.substr(0, imagePath.size( ) - 5) + ".png"))),
			/* v["source"].get<std::string>( ), */
			imagePath,
			firstGid,
			lastGid,
			jTilePath["columns"].get<int8_t>( ),
			IsAnimated));

		/* Clear ifstream and Json */

		jTilePath.clear( );
		ifsTilePath.close( );
	}	// For tilesets

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

			/* ########################## TILES ############################ */

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
					if (mTileSets.size( ) > 1) {
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
								tls.mImageName = t.mImageName;
								tls.mColumns = t.mColumns;
								tls.mIsAnimated = t.mIsAnimated;
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
					Vec2 sourceTile = getTilesetPosition(tls,
														 data_gid.get<int>( ),
														 tileW,
														 tileH);

					if (tls.mIsAnimated) {
						//
						std::vector<Vec2> TilesetsPositions;
						for (const auto& eAnimation : mAnimatedTileInfos) {
							if (eAnimation.StartTileId ==
								data_gid.get<int>( )) {
								for (const auto& tiles : eAnimation.TileIds) {
									//
									TilesetsPositions.push_back(
										getTilesetPosition(tls,
														   tiles,
														   tileW,
														   tileH));

								}	// For tiles

								mAnimatedTileList.emplace_back(
									AnimatedTile(TilesetsPositions,
												 eAnimation.Duration,
												 tls.mTexture,
												 Vec2(tileW, tileH),
												 destTile));

								break;
							}	// if
						}
					} else {
						Tile tile(tls.mTexture,
								  Vec2(tileW, tileH),
								  sourceTile,
								  destTile);

						mTileList.push_back(tile);
					}

					//				std::cout << "tsxx: " << tsxx << "\n";
					//				std::cout << "Datagid: " << data_gid <<
					//"\n";
				}	// if data_gid

				tileCounter++;
				// std::cout << "\n";
			}	// for Data values
		}	// IF is a Tiler

		// std::cout << "\n\n ----------------------------";

		/* ######################## Get collisions ######################## */
		if (val["type"].get<std::string>( ) == "objectgroup") {
			for (const auto& ob : val["objects"]) {
				//
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
					// fmt::print("\n\n+++++++++++++++Slope: \n");
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
							// fmt::print("\n----\n");

							int obX = std::ceil(ob["x"].get<int>( ));
							int obY = std::ceil(ob["y"].get<int>( ));
							int polX = poly["x"].get<int>( );
							int polY = poly["y"].get<int>( );
							int sumX = polX + obX;
							int sumY = polY + obY;

							// fmt::print("\nobX: {}", obX);
							// fmt::print("\nobY: {}", obY);
							// fmt::print("\npolyX: {}", polX);
							// fmt::print("\npolyY: {}", polY);
							// fmt::print("\nSumX: {}", sumX);
							// fmt::print("\nSumY: {}", sumY);
							// fmt::print("\n----\n");

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

							// mSlopes.emplace_back(Slope(
							// 	// P1
							// 	Vec2(std::ceil(ob["x"].get<int>( )) *
							// 			 Constants::SPRITE_SCALE,
							// 		 std::ceil(ob["y"].get<int>( )) *
							// 			 Constants::SPRITE_SCALE),	 // Vec
							// 	// P2
							// 	Vec2((std::ceil(ob["x"].get<int>( )) +
							// 		  poly["x"].get<int>( )) *
							// 			 Constants::SPRITE_SCALE,
							// 		 (std::ceil(ob["y"].get<int>( )) +
							// 		  poly["y"].get<int>( )) *
							// 			 Constants::SPRITE_SCALE)	// V// ec
							// 	)	// Slo// pe
							// );	 // Vec						pe

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
	for (auto& tla : mAnimatedTileList) { tla.update(DeltaTime); }
}	// Update

// #####################################################################
// #####################################################################
void Level::Draw(Graphics& graphics) {
	for (auto& tl : mTileList) { tl.Draw(graphics); }
	for (auto& tla : mAnimatedTileList) { tla.draw(graphics); }
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

Vec2 Level::getTilesetPosition(Tileset& tls, int gid, int tileW, int tileH) {
	//

	int tileQueryW { };
	int tileQueryH { };
	SDL_QueryTexture(tls.mTexture, nullptr, nullptr, &tileQueryW, &tileQueryH);

	int gid_rest = tls.mFirstGid - 1;
	int sum_gids = gid - gid_rest;
	// ------------------------------------------
	// ------------------------------------------

	// fmt::print("\ntls firstgid: {}\n", tls.mFirstGid);
	// // fmt::print("+++counter: {}\n", tileCounter);
	// fmt::print("data_gid: {}\n", data_gid.get<int>( ));
	// // fmt::print("gid sum: {}\n",
	// // data_gid.get<int>( ) - gid_rest);

	// fmt::print("image name: {}\n", tls.mImageName);
	// // std::cout << "texture: " << tls.mTexture << "\n";

	// fmt::print("Columns: {}\n", tls.mColumns);
	// fmt::print("tileW: {}\n", tileW);
	// fmt::print("tileH: {}\n", tileH);
	// fmt::print("tileQueryW: {}\n", tileQueryW);
	// fmt::print("tileQueryH: {}\n", tileQueryH);

	// ------------------------------------------
	// ------------------------------------------

	int tsxx { sum_gids % tls.mColumns - 1 };

	// int tsxx { data_gid.get<int>( ) % (tileQueryW / tileW) -
	// 		   1 };

	// Evita el bug: Puedes usar el ultimo tile de la derecha
	if (tsxx == -1) {
		// Cuando tienes mas de 2 tilesets
		tsxx = tileW * (tls.mColumns - 1);
		// tsxx = tileW * ((tileQueryW / tileW) - 1);

		// Cuando solo tienes un solo tileset
		// tsxx = tileW * (tileW - 1);
	} else {
		tsxx *= tileW;
	}

	int tsyy { };
	/* Permite usar varios tilesets; Ya que regresa el valor a 0
	 * como base */
	int amt { (gid - gid_rest) / (tileQueryW / tileW) };

	// Evita el bug: Puedes usar el ultimo tile de la derecha
	if ((gid % (tileQueryW / tileW)) == 0) { amt -= 1; }

	tsyy = tileH * amt;

	// fmt::print("amt: {}\n", amt);
	// fmt::print("tileW: {}\n", tileW);
	// fmt::print("tileH: {}\n", tileH);
	// fmt::print("tsxx: {}\n", tsxx);
	// fmt::print("tsyy: {}\n", tsyy);

	Vec2 sourceTile = Vec2(tsxx, tsyy);
	return sourceTile;
}
