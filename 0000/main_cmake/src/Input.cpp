#include "./Input.h"
// #include <fmt/color.h>

/* Enter at the beginning in each frame
to reset the keys are no longer relevant*/
void Input::BeginNewFrame( ) {
	mPressedKeys.clear( );
	mReleasedKeys.clear( );
}

void Input::KeyUpEvent(const SDL_Event& event) {
	mReleasedKeys[event.key.keysym.scancode] = true;
	mHeldKeys[event.key.keysym.scancode] = false;

	// fmt::print("\n- KeyUp:\nReleased {}\nHeld: {}\n",
	// 		   mReleasedKeys.size( ),
	// 		   mHeldKeys.size( ));
}

void Input::KeyDownEvent(const SDL_Event& event) {
	mPressedKeys[event.key.keysym.scancode] = true;
	mHeldKeys[event.key.keysym.scancode] = true;

	// fmt::print("\n- KeyDown:\nPressed {}\nHeld: {}\n",
	// 		   mPressedKeys.size( ),
	// 		   mHeldKeys.size( ));
}

bool Input::WasKeyPressed(SDL_Scancode key) { return mPressedKeys[key]; }

bool Input::WasKeyReleased(SDL_Scancode key) { return mReleasedKeys[key]; }

bool Input::IsKeyHeld(SDL_Scancode key) { return mHeldKeys[key]; }
