#include "./Game.h"

#include <SDL2/SDL.h>
#include "./Tile.h"
#include "./Time.h"

#include <fmt/color.h>
#include <fmt/core.h>

#include <cpuid.h>

/* ---------------- Singleton ---------------- */
// Game* Game::sGame = nullptr;
/* ---------------- Singleton ---------------- */

// SDL_Event Game::mEvent;

Game::Game( ) {
	/* Start Game Libs */
	initLibs( );

	/* Start pointers */
	// mTiles = std::make_unique<Tile>( );

	// SDL_Rect source { 0, 0, 16, 16 };
	// SDL_Rect pos { 400, 200, 0, 0 };
	// mPlayer = std::make_unique<Player>(*graphics, source, pos);

	mLevel = std::make_unique<Level>("Testing_00", Vec2(100, 100), *graphics);

	// mPlayer = std::make_unique<Player>(*graphics,
	// 								   SDL_Rect { 0, 0, 16, 16 },	// Source
	// 								   SDL_Rect { 177, 134, 0, 0 });   // Dest

	mPlayer =
		std::make_unique<Player>(*graphics,
								 SDL_Rect { 0, 0, 16, 16 },	  // Source
								 SDL_Rect { mLevel->getPlayerSpawnPoint( ).x,
											mLevel->getPlayerSpawnPoint( ).y,
											0,
											0 });	// Dest
	/* ~Start pointers */

	Loop( );
}

/* ********************************************************** */
Game::~Game( ) {
	// TTF_Quit( );
	// IMG_Quit( );
	// Mix_Quit( );
	fmt::print("\nJust for fun!\n");
	SDL_Quit( );
	// delete sGame;
}

void Game::initLibs( ) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "--- Error!!! INIT EVERYTHING --- {}\n\n",
				   SDL_GetError( ));
		exit(1);
	}

	/* ----------------------------- Monitors ----------------------------- */
	fmt::print("\n Number of monitors: {}\n ", SDL_GetNumVideoDisplays( ));

	SDL_DisplayMode dm;

	if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
		fmt::print("SDL_GetDesktopDisplayMode failed: {}\n", SDL_GetError( ));
		exit(1);
	}
	// auto width = dm.w;
	// auto height = dm.h;

	fmt::print("Window size: Width {}\n Height: {}\n", dm.w, dm.h);
	// fmt::print("Window size: Width {}\n Height: {}\n", width, height);
	/* ----------------------------- Monitors ----------------------------- */

	is_running = true;
	// Loop( );
	Control->Check( );
}

/* ********************************************************** */
void Game::ProcessImputWhile( ) {
	input->BeginNewFrame( );

	// SDL_Event mEvent;
	SDL_Event mEvent;
	while (SDL_PollEvent(&mEvent)) {
		Control->ControllEvents(mEvent);
		// Pressed
		if (mEvent.type == SDL_KEYDOWN) {
			// fmt::print("--- Repeat\n\n");
			if (mEvent.key.repeat == 0) {
				// fmt::print("--- Not repeat\n\n");
				input->KeyDownEvent(mEvent);
			}
			// Released
		} else if (mEvent.type == SDL_KEYUP) {
			input->KeyUpEvent(mEvent);
		}

		switch (mEvent.type) {
			/*******************************/
			// GUI: Window button X
			case SDL_QUIT:
				fmt::print("\n------Pressed click to X\n");
				is_running = false;
				break;
			// Keys: Q, Escape
			case SDL_KEYDOWN:
				switch (mEvent.key.keysym.sym) {
					case SDLK_q:
						fmt::print("\n------Key Q to exit\n");
						is_running = false;
						break;
					case SDLK_ESCAPE:
						fmt::print("\n------Key ESCAPE to exit\n");
						is_running = false;
						break;
					case SDLK_t:
						fmt::print("\n------Testing\n");
						// is_running = false;
						break;
				}
				break;
				/*******************************/
				// switch (mEvent.key.repeat) {
				// 	case 0: fmt::print("\n+++++++++++++pressed\n"); break;
				// }
			default: break;
		}

	}	// WHILE SDL_POLLEVENTS

}	// ProcessInputWhile

/* ********************************************************** */

// void Game::ProcessImputIf( ) {
// 	input->BeginNewFrame( );

// 	// SDL_Event mEvent;
// 	if (SDL_PollEvent(&mEvent)) {
// 		Control->ControllEvents(mEvent);

// 		// Pressed
// 		if (mEvent.type == SDL_KEYDOWN) {
// 			fmt::print("--- Repeat\n\n");
// 			if (mEvent.key.repeat == 0) {
// 				fmt::print("--- Not repeat\n\n");
// 				input->KeyDownEvent(mEvent);
// 			}
// 			// Released
// 		} else if (mEvent.type == SDL_KEYUP) {
// 			input->KeyUpEvent(mEvent);
// 		}
// 		// else if (mEvent.type == SDL_QUIT) {
// 		// 	is_running = false;
// 		// }

// 		switch (mEvent.type) {
// 			// GUI: Window button X
// 			case SDL_QUIT:
// 				fmt::print("\n------Pressed click to X\n");
// 				is_running = false;
// 				break;
// 			// Keys: Q, Escape
// 			case SDL_KEYDOWN:
// 				switch (mEvent.key.keysym.sym) {
// 					case SDLK_q:
// 						fmt::print("\n------Key Q to exit\n");
// 						is_running = false;
// 						break;
// 					case SDLK_ESCAPE:
// 						fmt::print("\n------Key ESCAPE to exit\n");
// 						is_running = false;
// 						break;
// 				}
// 				break;
// 		}
// 		// if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_q ||
// 		// 	event.key.keysym.sym == SDLK_ESCAPE) {
// 		// 	fmt::print("\n------Pressed click to exit\n");

// 		// 	is_running = false;
// 		// }	// QUIT
// 	}	// If POLLEVENT

// 	// if(input->WasKeyPressed(SDL_SCANCODE_ESCAPE) == true){ }

// 	if (input->IsKeyHeld(SDL_SCANCODE_LEFT)) {
// 		mPlayer->MoveLeft( );
// 		//			fmt::print("left\n");
// 	}

// 	if (input->IsKeyHeld(SDL_SCANCODE_RIGHT)) {
// 		mPlayer->MoveRight( );
// 		//			fmt::print("Right\n");
// 	}

// 	if (!input->IsKeyHeld(SDL_SCANCODE_LEFT) &&
// 		!input->IsKeyHeld(SDL_SCANCODE_RIGHT)) {
// 		mPlayer->StopMoving( );
// 	}
// }

/* ********************************************************** */

// void Game::ProcessImput( ) {
// 	input->BeginNewFrame( );

// 	// SDL_Event event;
// 	SDL_PollEvent(&mEvent);
// 	Control->ControllEvents(mEvent);

// 	// Pressed
// 	if (mEvent.type == SDL_KEYDOWN) {
// 		fmt::print("--- Repeat\n\n");
// 		if (mEvent.key.repeat == 0) {
// 			fmt::print("--- Not repeat\n\n");
// 			input->KeyDownEvent(mEvent);
// 		}
// 		// Released
// 	} else if (mEvent.type == SDL_KEYUP) {
// 		input->KeyUpEvent(mEvent);
// 	}

// 	switch (mEvent.type) {
// 		// GUI: Window button X
// 		case SDL_QUIT:
// 			fmt::print("\n------Pressed click to X\n");
// 			is_running = false;
// 			break;
// 		// Keys: Q, Escape
// 		case SDL_KEYDOWN:
// 			switch (mEvent.key.keysym.sym) {
// 				case SDLK_q:
// 					fmt::print("\n------Key Q to exit\n");
// 					is_running = false;
// 					break;
// 				case SDLK_ESCAPE:
// 					fmt::print("\n------Key ESCAPE to exit\n");
// 					is_running = false;
// 					break;
// 			}
// 			break;
// 	}
// 	// if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_q ||
// 	// 	event.key.keysym.sym == SDLK_ESCAPE) {
// 	// 	fmt::print("\n------Pressed click to exit\n");

// 	// 	is_running = false;
// 	// }	// QUIT

// 	// if(input->WasKeyPressed(SDL_SCANCODE_ESCAPE) == true){ }

// 	if (input->IsKeyHeld(SDL_SCANCODE_LEFT)) {
// 		mPlayer->MoveLeft( );
// 		//			fmt::print("left\n");
// 	}

// 	if (input->IsKeyHeld(SDL_SCANCODE_RIGHT)) {
// 		mPlayer->MoveRight( );
// 		//			fmt::print("Right\n");
// 	}

// 	if (!input->IsKeyHeld(SDL_SCANCODE_LEFT) &&
// 		!input->IsKeyHeld(SDL_SCANCODE_RIGHT)) {
// 		mPlayer->StopMoving( );
// 	}
// }

/* ********************************************************** */

void Game::Loop( ) {
	while (is_running) {
		ProcessImputWhile( );
		// ProcessImputIf( );
		// ProcessImput( );
		deltaTime.Init( );
		Update(deltaTime.GetDeltaTime( ));

		Draw( );
	}
}

void Game::checkCPUInfo( ) {
	std::string CPUBrandString;
	CPUBrandString.resize(49);
	uint* CPUInfo = reinterpret_cast<uint*>(CPUBrandString.data( ));
	for (uint i = 0; i < 3; i++)
		__cpuid(0x80000002 + i,
				CPUInfo[i * 4 + 0],
				CPUInfo[i * 4 + 1],
				CPUInfo[i * 4 + 2],
				CPUInfo[i * 4 + 3]);
	CPUBrandString.assign(CPUBrandString.data( ));	 // correct null terminator
	// std::cout << CPUBrandString << std::endl;
	fmt::print("\nCPU info: {}\n", CPUBrandString);
}

void Game::Draw( ) {
	graphics->Clear( );
	mLevel->Draw(*graphics);
	mPlayer->Draw(*graphics);
	graphics->Flip( );
}

void Game::Update(float deltaTime) {
	/* Player Move */
	if (input->IsKeyHeld(SDL_SCANCODE_LEFT) ||
		input->IsKeyHeld(SDL_SCANCODE_A)) {
		mPlayer->MoveLeft( );
		// fmt::print("left\n");
	}

	if (input->IsKeyHeld(SDL_SCANCODE_RIGHT) ||
		input->IsKeyHeld(SDL_SCANCODE_D)) {
		mPlayer->MoveRight( );
		// fmt::print("Right\n");
	}

	if (input->IsKeyHeld(SDL_SCANCODE_UP)) {
		mPlayer->lookUp( );
	} else if (input->IsKeyHeld(SDL_SCANCODE_DOWN)) {
		mPlayer->lookDown( );
	}

	if (input->WasKeyReleased(SDL_SCANCODE_UP)) { mPlayer->stopLookingUp( ); }
	if (input->WasKeyReleased(SDL_SCANCODE_DOWN)) {
		mPlayer->stopLookingDown( );
	}

	if (input->WasKeyPressed(SDL_SCANCODE_UP) ||
		input->IsKeyHeld(SDL_SCANCODE_W)) {
		mPlayer->Jump( );
		fmt::print("Jump\n");
	}

	if (   // Left
		(!input->IsKeyHeld(SDL_SCANCODE_LEFT) &&
		 !input->IsKeyHeld(SDL_SCANCODE_A)) &&
		// Right
		(!input->IsKeyHeld(SDL_SCANCODE_RIGHT) &&	//
		 !input->IsKeyHeld(SDL_SCANCODE_D))	  //
	) {
		mPlayer->StopMoving( );
	}

	/* Player Move */

	// mTiles->Update(deltaTime);
	mLevel->Update(deltaTime);

	mPlayer->Update(deltaTime);

	// Rectangle rTest = *mPlayer->getBoundingBox( );

	// fmt::print("\nrTest: {}", rTest.getBottom( ));

	// if ((others = mLevel->checkTileCollisions(*mPlayer->getBoundingBox(
	// ))) 		.size( ) > 0) { if (!(others =
	// mLevel->checkTileCollisions(rTest)).empty( )) {

	// Check collisions
	std::vector<Rectangle> others;
	std::vector<Slope> otherSlopes;
	if (!(others = mLevel->checkTileCollisions(*mPlayer->getBoundingBox( )))
			 .empty( )) {
		// fmt::print("\n++++++++++++++testing Check collisions\n");
		// Player collided with at least one tile.
		mPlayer->handleTileCollisions(others);
	}

	if (!(otherSlopes =
			  mLevel->checkSlopeCollisions(*mPlayer->getBoundingBox( )))
			 .empty( )) {
		mPlayer->handleSlopeCollision(otherSlopes);
	}

	if (others.empty( ) && otherSlopes.empty( )) {
		// fmt::print("\nothers and othersSlope are empty\n");
		mPlayer->setGrounded(false);
	}

	// fmt::print("\n#################################\n");
}
