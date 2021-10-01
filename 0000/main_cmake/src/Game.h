#ifndef GAME_H
#define GAME_H

// #include "./Sprite.h"
// #include "./AnimatedSprite.h"

#include <memory>

#include "./Player.h"
#include "./Level.h"
#include "./Input.h"
#include "./Controllers.h"
#include "./Graphics.h"
#include "./Time.h"

class Graphics;
class Tile;

class Game {
  public:
	/* ---------------- Singleton ---------------- */
	Game( );
	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;
	/* ---------------- Singleton ---------------- */
	~Game( );

	/**
	 * @brief Get the Singleton object: TODO Remove this, because it is a static
	 * value
	 *
	 * @return Game*
	 */
	// static Game* GetSingleton( ) { return sGame ?: new Game; }

	constexpr bool IsRunning( ) const { return is_running; }

	void ProcessImputWhile( );
	//	void ProcessImputIf( );
	//	void ProcessImput( );

	void Draw( );
	void Update(float deltaTime);

  private:
	/* ---------------- Singleton ---------------- */
	// Game(); // Si se quiere usar singleton. Mantener el Constructor en
	// privado
	// static Game* sGame;
	//	SDL_Event mEvent;
	// static SDL_Event mEvent;
	/* ---------------- Singleton ---------------- */

	/**
	 * @brief Check and Initiate libs:
	 *
	 * * SDL_EVERYTHING
	 * * Controllers
	 *
	 */
	void initLibs( );

	/**
	 * @brief Main Game
	 *
	 */
	void Loop( );

	void checkCPUInfo( );

	bool is_running { false };

	//	Player mPlayer;
	//	Level mLevel;
	std::unique_ptr<Graphics> graphics { std::make_unique<Graphics>( ) };
	std::unique_ptr<Controllers> Control { std::make_unique<Controllers>( ) };
	std::unique_ptr<Input> input { std::make_unique<Input>( ) };
	std::unique_ptr<Player> mPlayer;
	std::unique_ptr<Level> mLevel;
	std::unique_ptr<Tile> mTiles;
	Cris::Time deltaTime;
};

#endif	 //	GAME_H
