#ifndef PLAYER_H
#define PLAYER_H

#include "./AnimatedSprite.h"
#include "./Constants.h"
#include "./Slope.h"

class Graphics;

/**
 * @brief Player is a Sprite > AnimatedSprite Class
 *
 * @details Move, the sprite player
 */
class Player : public AnimatedSprite {
  public:
	Player( ) = default;
	Player(Graphics& graphics, const SDL_Rect& source, const SDL_Rect& pos);

	void Update(float DeltaTime) override;
	void Draw(Graphics& graphics);

	void MoveLeft( );
	void MoveRight( );
	void Jump( );

	void lookUp( );
	void stopLookingUp( );

	void lookDown( );
	void stopLookingDown( );

	void StopMoving( );
	bool getGrounded( ) const { return mGrounded; }
	void setGrounded(const bool& ground) { mGrounded = ground; }

	void AnimationDone(std::string currentAnimation) override;
	void SetupAnimation( ) override;

	float getX( ) const { return mX; }
	float getY( ) const { return mY; }

	/**
	 * @brief Hanlde all collisions with all tiles the player is colliding with
	 *
	 * @param others
	 */
	void handleTileCollisions(std::vector<Rectangle>& others);

	void handleSlopeCollision(std::vector<Slope>& others);

  private:
	// TODO(cris): Change to Vector2D
	float mX, mY, mYY;
	Direction mFacing;
	bool mGrounded;

	bool mLookingUp;
	bool mLookingDown;
};

#endif	 //	PLAYER_H
