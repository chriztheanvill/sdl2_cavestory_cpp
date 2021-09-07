#include "./Player.h"
#include "./Graphics.h"
#include "./Rectangle.h"
#include "Constants.h"

#include <fmt/color.h>

namespace {
	const float WALK_SPEED = 400;

	constexpr float GRAVITY = 9.81F;
	// constexpr float GRAVITY = 9.81F * 1000;
	// Time to fall: Like Coyote time
	constexpr float GRAVITY_VELOCITY = 5;
	// constexpr float GRAVITY_VELOCITY = 0.009F;
	constexpr float GRAVITY_MAX = 150.0F;
	// constexpr float GRAVITY_MAX = 350.0F;
	constexpr float UNI_MASS { 1.0F };
	constexpr float FORCE { .005F };

	// constexpr int JUMPFORCE = 50;
	constexpr int JUMPFORCE = 300;

}	// namespace

// Player::Player( ) {
// 	//
// }

Player::Player(Graphics& graphics, const SDL_Rect& source, const SDL_Rect& pos)
	: AnimatedSprite(graphics, "assets/images/MyChar.png", source, pos, 50)
	, mX(0)
	, mY(0)
	// , mYY(pos.y)
	, mYY(0)
	, mFacing(Direction::RIGHT)
	, mGrounded(false) {
	graphics.LoadImage("assets/images/MyChar.png");
	SetupAnimation( );
	PlayAnimation("RunRight");
}

/* #################################################################### */
void Player::Update(float DeltaTime) {
	mYY = std::min(mYY + GRAVITY, GRAVITY_MAX);

	mPos.y += static_cast<int>(mYY * DeltaTime);

	// fmt::print("++----++ mY {}\n", mY);
	fmt::print("++----++ mYY {}\n", mYY);
	fmt::print("++----++ mPos.y {}\n", mPos.y);
	fmt::print("++----++ Grounded {}\n\n", mGrounded);

	mPos.x += static_cast<int>(mX * DeltaTime);
	// fmt::print("mPos: x {} - y {}\n", mPos.x, mPos.y);

	AnimatedSprite::Update(DeltaTime);
}

void Player::Draw(Graphics& graphics) { AnimatedSprite::Draw(graphics, mPos); }

void Player::AnimationDone(std::string currentAnimation) {
	// TODO(cris):
}

void Player::SetupAnimation( ) {
	SDL_Rect RunLeft { 0, 0, 16, 16 };
	SDL_Rect RunRight { 0, 16, 16, 16 };
	SDL_Rect IdleLeft { 0, 0, 16, 16 };
	SDL_Rect IdleRight { 0, 16, 16, 16 };
	AddAnimation(1, "IdleLeft", IdleLeft, Vec2(0, 0));
	AddAnimation(1, "IdleRight", IdleRight, Vec2(0, 0));
	AddAnimation(3, "RunLeft", RunLeft, Vec2(0, 0));
	AddAnimation(3, "RunRight", RunRight, Vec2(0, 0));
}

void Player::MoveLeft( ) {
	mX = -WALK_SPEED;
	PlayAnimation("RunLeft");
	mFacing = Direction::LEFT;
}

void Player::MoveRight( ) {
	mX = WALK_SPEED;
	PlayAnimation("RunRight");
	mFacing = Direction::RIGHT;
}

void Player::Jump( ) {
	if (mGrounded) {
		mYY = 0;
		mYY = -JUMPFORCE;
		mGrounded = false;
	}
}

void Player::StopMoving( ) {
	mX = 0.0F;
	PlayAnimation(mFacing == Direction::RIGHT ? "IdleRight" : "IdleLeft");
}

void Player::handleTileCollisions(std::vector<Rectangle>& others) {
	// Figure out what side the collision happened on and move the player
	// accordingly

	for (const auto& i : others) {
		Sides::Side collisionSide = Sprite::getCollisionSide(i);
		// fmt::print("\nCollision side: {}\n", collisionSide);
		/* If hits the bottom collider: Moves ONE step */
		switch (collisionSide) {
			/* ################################### */
			case Sides::Side::TOP:
				// Un paso Abajo.
				if (!mGrounded) {
					mPos.y = i.getBottom( ) + 1;
					mGrounded = false;
					fmt::print(
						"\n vvvvvvvvv^^^^^^^^^ touched top and grounded\n");
					mYY = 0;   // Reset GRAVITY
				} else {
					/* Si esta en el suelo y techo:
					Se detiene el personaje,
					y se recorre un poco de lado contrario */
					mX = 0;
					mPos.x -= mFacing == Direction::RIGHT ? 1 : -1;
				}
				// mY = 0;	  // Reset GRAVITY
				fmt::print("\n ^^^^^^^^^^^^^^^^^^ touched top\n");
				break;
			/* ################################### */
			case Sides::Side::BOTTOM:
				// Un paso mas Arriba:
				// El valor de la colision - el tamaño de el jugador, - 1
				mPos.y = i.getTop( ) - mBoundingBox->getHeight( ) - 1;

				// mYY = 0;
				// mY = 0;
				fmt::print("\n vvvvvvvvvvvvvvvv mPos.y: {}\n", mPos.y);
				fmt::print("\n vvvvvvvvvvvvvvvv touched Bottom\n");
				mGrounded = true;
				break;
			/* ################################### */
			case Sides::Side::LEFT:
				// Un paso mas a la derecha
				mPos.x = i.getRight( ) + 1;
				fmt::print("\n <<<<<<<<<<<<<<<<<< touched left\n");
				// mGrounded = false;
				break;
			/* ################################### */
			case Sides::Side::RIGHT:
				// Un paso mas a la Izquierda
				mPos.x = i.getLeft( ) - mBoundingBox->getWidth( ) - 1;
				// mGrounded = false;
				break;
			/* ################################### */
			case Sides::Side::NONE:
				// No esta tocando nada.
				fmt::print("\n ------------------- touched Nothing\n");
				// mGrounded = false;
				break;
		}	// Switch
		// if (collisionSide != Sides::Side::BOTTOM) { mGrounded = false; }
	}	// FOR
}	// HandleTileCollisions

void Player::handleSlopeCollision(std::vector<Slope>& others) {
	/* Usando y = mx + b
	"y" y "x" = Es la ubicacion del slope
	b = es la interseccion del slope

	Solo se SIMULARA como si estuviesemos arriba del Slope
	*/

	// First calculate b (slope intercept) bottom center is touching
	for (const auto& o : others) {
		// b (slope intercept) using one of the points
		// b = y - mx
		int b = (o.getP1( ).y - (o.getSlope( ) * fabs(o.getP1( ).x)));

		// Get Players center x
		int centerX = mBoundingBox->getCenterX( );

		// Pass X in to the equation y = mx + b ( Using our newly found b and x
		// ) to get new "y" position
		int newY =
			// (o.getSlope( ) * centerX) + b;
			(o.getSlope( ) * centerX) + b -
			(mBoundingBox->getHeight( ) / 4);	// Temporary to fix a problem

		// TODO(cris) Slope grounded
		if (mGrounded) {
			mPos.y = newY - mBoundingBox->getHeight( );

			// Resuelve el bug 00
		} else if (mPos.y >= newY - mBoundingBox->getHeight( )) {
			mPos.y = newY - mBoundingBox->getHeight( );

			mGrounded = true;
		}
	}	// For others
}	// HandleSlopeCollision
