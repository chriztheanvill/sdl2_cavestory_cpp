#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <map>

class Input {
  public:
	void BeginNewFrame( );
	void KeyUpEvent(const SDL_Event& event);
	void KeyDownEvent(const SDL_Event& event);

	bool WasKeyPressed(SDL_Scancode key);
	bool WasKeyReleased(SDL_Scancode key);
	bool IsKeyHeld(SDL_Scancode key);

  private:
	std::map<SDL_Scancode, bool> mHeldKeys;
	std::map<SDL_Scancode, bool> mPressedKeys;
	std::map<SDL_Scancode, bool> mReleasedKeys;
};

#endif	 //	INPUT_H