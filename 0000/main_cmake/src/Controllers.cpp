//
// Created by cris on 26/04/21.
//

#include "Controllers.h"
#include "SDL_joystick.h"
#include <iostream>
#include <SDL2/SDL.h>

#include <fmt/color.h>

Controllers::Controllers( ) {
	//
	Init( );
}

Controllers::~Controllers( ) {
	// SDL_JoystickClose(joy);
	if (SDL_NumJoysticks( ) >= 1) { SDL_JoystickClose(joy); }
}

void Controllers::Init( ) {
	if (SDL_Init(SDL_INIT_JOYSTICK) != 0) {
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "--- Error!!! SDL_INIT_EVERYTHING --- {}",
				   SDL_GetError( ));
		exit(1);
	}
}

void Controllers::Check( ) {
	if (SDL_NumJoysticks( ) < 1) {
		fmt::print(fmt::emphasis::bold | fg(fmt::color::yellow),
				   "\n--- WARNING!!! NO JOYSTICKS CONNECTED ---\n");
	} else {
		fmt::print("Num of Joysticks: {}", SDL_NumJoysticks( ));
		joy = SDL_JoystickOpen(0);
		//	SDL_Joystick* joy = SDL_JoystickOpen(0);
		if (!joy) {
			fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
					   "--- Error!!! JOYSTICK ---");
			exit(1);
		}

		std::cout << "\nJoystick name: " << SDL_JoystickName(joy) << "\n";
	}

	//	std::cout << "\nJoystick Index: " <<
	// SDL_JoystickGetDevicePlayerIndex(joy.) << "\n"; 	std::cout << "\nJoystick
	// index: " << SDL_JoystickIndex(joy) << "\n";

	// fmt::print("\nJoystick name {}\n", SDL_JoystickName(joy));
	// fmt::print("\nJoystick num Axes {}\n", SDL_JoystickNumAxes(joy));
	// fmt::print("\nJoystick num Buttons {}\n", SDL_JoystickNumButtons(joy));
	// fmt::print("\nJoystick num Balls {}\n", SDL_JoystickNumBalls(joy));
	// fmt::print("\nJoystick num Hats {}\n", SDL_JoystickNumHats(joy));
}

void Controllers::ControllEvents(SDL_Event& e) {
	switch (e.type) {
		case SDL_JOYBUTTONDOWN:

			fmt::print("\nPressed:\n");
			fmt::print("\nSDL_JoystickGetButton(joy, 0): {}\n",
					   SDL_JoystickGetButton(joy, 0));
			fmt::print("\nSDL_JoystickGetButton(joy, 1): {}\n",
					   SDL_JoystickGetButton(joy, 1));
			fmt::print("\nSDL_JoystickGetButton(joy, 2): {}\n",
					   SDL_JoystickGetButton(joy, 2));
			fmt::print("\nSDL_JoystickGetButton(joy, 3): {}\n",
					   SDL_JoystickGetButton(joy, 3));
			// if () {}

			break;

		case SDL_JOYAXISMOTION:
			if (e.jaxis.which == 0) {
				if (e.jaxis.axis == 0) {   // Left / Right
					fmt::print("\n Joystick Axis 0 = {}\n", e.jaxis.value);
				}
				if (e.jaxis.axis == 1) {   // Up / Down
					fmt::print("\n Joystick Axis 1 = {}\n", e.jaxis.value);
				}
			}
			//			fmt::print("Movement\n"); break;
		default: break;
	}
}
