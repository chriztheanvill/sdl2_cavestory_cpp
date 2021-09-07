//
// Created by cris on 26/04/21.
//

#ifndef CONTROLLERS_H
#define CONTROLLERS_H

typedef struct _SDL_Joystick SDL_Joystick;
typedef union SDL_Event SDL_Event;

// struct SDL_Joystick;
// struct SDL_Event;

/**
 * @brief Handles the controllers
 *
 */
class Controllers {
  public:
	Controllers( );
	~Controllers( );

	/**
	 * @brief Starts the use of Controlls
	 *
	 */
	void Init( );

	/**
	 * @brief Checks how many controllers are connected
	 *
	 */
	void Check( );

	/**
	 * @brief Handles the controller/s input
	 *
	 * @param e
	 */
	void ControllEvents(SDL_Event& e);

  private:
	SDL_Joystick* joy;
};

#endif	 // CONTROLLERS_H
