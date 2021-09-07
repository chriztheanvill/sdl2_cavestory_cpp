#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <string>
#include <memory>

#include "./Rectangle.h"

class Graphics;

class Sprite {
  public:
	Sprite( ) = default;
	Sprite(Graphics& graphics,
		   const std::string& path,
		   SDL_Rect& source,
		   SDL_Rect& pos);

	virtual ~Sprite( ) = default;

	virtual void Update(float DeltaTime);
	void Draw(Graphics& graphics, SDL_Rect& pos);

	/**
	 * @brief Get the Bounding Box object
	 *
	 * @return Rectangle*
	 */
	Rectangle* getBoundingBox( );

	/**
	 * @brief Get the Collision Side object: Determine whitch side of the
	 * collision is overlapping (Sobrepuesta)
	 *
	 * @param other
	 * @return const Sides::Side
	 */
	// TODO (cris) Check if I can make a: "is_on_floor, cealing, wall"
	const Sides::Side getCollisionSide(const Rectangle& other) const;

	// Change to a function protected
  protected:
	/**
	 * @brief Posicion del Sprite(SDL_Rect Source)
	 *
	 */
	SDL_Rect mSource;

	SDL_Texture* mSpriteSheet;

	/**
	 * @brief Posicion en pantalla(SDL_Rect Dest)
	 *
	 */
	SDL_Rect mPos { };

	/**
	 * @brief Colisionador
	 */
	std::unique_ptr<Rectangle> mBoundingBox;

  private:
};

#endif	 //	SPRITE_H
