#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <map>
#include <string>

struct SDL_Rect;
struct SDL_Texture;
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

class Graphics {
  public:
	Graphics( );
	~Graphics( );

	/**
	 * @brief Loads image into map: Each image will only be loaded once
	 *
	 * @param path Loading image path
	 * @return SDL_Surface*
	 */
	SDL_Surface* LoadImage(const std::string& path);

	/**
	 * @brief Uses SDL_RenderCopy: Copy the texture to render.
	 *
	 * @param texture
	 * @param sourceRect
	 * @param destinationRect
	 */
	void blitSurface(SDL_Texture* texture,
					 SDL_Rect* sourceRect,
					 SDL_Rect* destinationRect);

	/**
	 * @brief Shows the painted render
	 */
	void Flip( );

	/**
	 * @brief Paints the screen with color black.
	 */
	void Clear( );

	SDL_Renderer* GetRenderer( ) const;

  private:
	SDL_Renderer* mRender;
	SDL_Window* mWindow;

	/**
	 * @brief Map of images
	 */
	std::map<std::string, SDL_Surface*> mSpriteSheets;
};

#endif	 //	GRAPHICS_H
