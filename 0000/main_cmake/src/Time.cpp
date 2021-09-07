#include "./Time.h"

#include <SDL2/SDL.h>
#include "./Constants.h"
#include <fmt/color.h>

namespace Cris {
	void Time::Init( ) {
		// mDeltaTime = (static_cast<float>(SDL_GetTicks( )) - mLastUpdate) *
		// 			 (mFPS / SECONDS);

		// fmt::print("\n DeltaTime: {}\n", mDeltaTime);
		// /*
		// Frecuente:
		// 0
		// 0.03
		// Raro:
		// 0.06
		// 1.14
		// 0.5399999996
		// */
		// if (mDeltaTime > mFPSLimit) { mDeltaTime = mFPSLimit; }

		// mLastUpdate = static_cast<float>(SDL_GetTicks( ));

		// #########################################
		// fmt::print("\nRest: {}\n", (SDL_GetTicks( ) - mLastTime));

		// Cuanto va a esperar
		int timeToWait = static_cast<int>(Constants::FRAME_TARGET_TIME -
										  (SDL_GetTicks( ) - mLastTime));

		// fmt::print("timeToWait: {}\n", timeToWait);

		if (timeToWait > 0 && timeToWait <= Constants::FRAME_TARGET_TIME) {
			// fmt::print("+++ Waiting timeToWait: {}\n", timeToWait);
			SDL_Delay(timeToWait);
		} else {
			// fmt::print("----------------- ELSE: {}\n", timeToWait);
		}

		// mDeltaTime = (SDL_GetTicks( ) - mLastTime);
		mDeltaTime = (SDL_GetTicks( ) - mLastTime) / SECONDS;
		// fmt::print("SDL_GetTicks: {}\n", SDL_GetTicks( ));
		// fmt::print("deltaTime: {}\n", mDeltaTime);

		// Debug
		mDeltaTime = (mDeltaTime > 0.05F) ? 0.05F : mDeltaTime;
		mLastTime = SDL_GetTicks( );
	}
}	// namespace Cris

/*



 */
