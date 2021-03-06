/**
 * @file main.cpp
 * @author Cristian Nieto (chriztheanvill@gmail.com)
 * @brief Just a Game
 * @version 0.1
 * @date 2021-02-09
 *
 * @copyright Copyright (c) 2021
 *
 */

// My libs

// System
#include <iostream>
#include <memory>
#include <fmt/color.h>

// // For this, in Cmake on Graphics, enable X11
// // #include <X11/Xlib.h>

#include "./src/Game.h"

// NOTE
// DONE
// WARNING
// BUG
// ERROR
// FIXME
// TODO(cris):

/* NOTE to check the program process:
	# Glances
	## Simple
	## glances -612 -t 0.5 -f name:.*program_name*
	## With left panel
	## glances -61 -t 0.5 -f name:.*program_name*
	### Shortcuts:
		q = exit
	# htop
	# htop --filter=program_name
		f10 = exit
*/

/* TODO
 * Crear Entidades
 * * Entity Manager
 *
 * Dejar de usar Singleton
 *
 * Separar Sprite y colisionador
 *
 * La clase controller, solo debe Inicializar y detectar
 * * Crear sub-clase que maneje el Event
 *
 * */

/* Main */
int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
	std::unique_ptr<Game> mGame { std::make_unique<Game>( ) };

	mGame = nullptr;

	fmt::print("\nExitGame\n");

	// Display* d { XOpenDisplay(nullptr) };
	// Screen* s { XDefaultScreenOfDisplay(d) };

	// std::unique_ptr<Game> First { std::make_unique<Game>( ) };
	// First->Run( );

	/* ################################################# */

	return 0;
}
