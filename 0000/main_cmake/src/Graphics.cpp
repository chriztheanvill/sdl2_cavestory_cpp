#include "./Graphics.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fmt/color.h>

#include "./Constants.h"

Graphics::Graphics( ) {
	/* Create for main Screen monitor */
	mWindow = SDL_CreateWindow(
		"CaveStory",
		// Choose display
		// 0 == main
		SDL_WINDOWPOS_CENTERED_DISPLAY(Constants::SECOND_SCREEN),
		SDL_WINDOWPOS_CENTERED_DISPLAY(Constants::SECOND_SCREEN),
		Constants::SCREEN_WIDTH,
		Constants::SCREEN_HEIGHT,
		SDL_WINDOW_OPENGL);

	// mRender = SDL_CreateRenderer(mWindow, -1, 0);
	mRender = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

	/* ########################### Not accuracy ########################### */
	// if (SDL_CreateWindowAndRenderer(Constants::SCREEN_WIDTH,
	// 								Constants::SCREEN_HEIGHT,
	// 								SDL_WINDOW_OPENGL,
	// 								&mWindow,
	// 								&mRender) != 0) {
	// 	fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
	// 			   "--- Error!!! Create Window and Render --- {}\n\n",
	// 			   SDL_GetError( ));
	// 	exit(1);
	// }
	// SDL_SetWindowTitle(mWindow, "CaveStory");

	//	fmt::print("\n--- Window Display: {}\n",
	//			   SDL_GetWindowDisplayIndex(mWindow));

	// fmt::print("\n--- Num render drivers: {}\n", SDL_GetNumRenderDrivers( ));
	/* ########################### Not accuracy ########################### */

	fmt::print(fmt::emphasis::bold | fg(fmt::color::azure),
			   "--- Success!!! Create Window and Render ---\n\n");
}

Graphics::~Graphics( ) {
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRender);
}

SDL_Surface* Graphics::LoadImage(const std::string& path) {
	if (mSpriteSheets.count(path) == 0) {
		SDL_Surface* img = IMG_Load(path.c_str( ));
		if (!img) {
			fmt::print("\n---------------- Error loading IMAGE "
					   "---------------- {} \n\n",
					   path);
		}
		mSpriteSheets[path] = img;
	}
	return mSpriteSheets[path];
}

void Graphics::blitSurface(SDL_Texture* texture,
						   SDL_Rect* sourceRect,
						   SDL_Rect* destinationRect) {
	SDL_RenderCopy(mRender, texture, sourceRect, destinationRect);
}

void Graphics::Flip( ) { SDL_RenderPresent(mRender); }

void Graphics::Clear( ) {
	SDL_SetRenderDrawColor(mRender, 0, 0, 0, 255);
	SDL_RenderClear(mRender);
}

SDL_Renderer* Graphics::GetRenderer( ) const { return mRender; }
