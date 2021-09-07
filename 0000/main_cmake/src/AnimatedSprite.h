#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <map>
#include <vector>
#include <string>
#include "./Sprite.h"
#include "./Constants.h"

class Graphics;

class AnimatedSprite : public Sprite {
  public:
	AnimatedSprite( ) = default;
	AnimatedSprite(Graphics& graphics,
				   const std::string& path,
				   SDL_Rect source,
				   SDL_Rect pos,
				   float UpdateTime);

	void PlayAnimation(const std::string& Animation, bool once = false);

	void Update(float DeltaTime) override;
	void Draw(Graphics& graphics, SDL_Rect& pos);

  protected:
	double mTimeToUpdate;
	bool mCurrentAnimationOnce { };
	std::string mCurrentAnimation { };

	/**
	 * @brief Add Animation
	 *
	 * @param frames How many frames to animate
	 * @param name Animation nate
	 * @param rect Position and Size
	 * @param offset
	 *
	 * @return void
	 *
	 * @details Add Animation by rect
	 *
	 * */
	void AddAnimation(int frames, std::string name, SDL_Rect rect, Vec2 offset);
	void ResetAnimations( );
	void StopAnimation( );
	void SetVisible(bool visible);

	virtual void AnimationDone(std::string currentAnimation) = 0;
	virtual void SetupAnimation( ) = 0;

  private:
	std::map<std::string, std::vector<SDL_Rect>> mAnimations;
	std::map<std::string, Vec2> mOffsets;

	int mFrameIndex;
	double mTimeElapsed;
	bool mVisible;
};

#endif	 //	ANIMATED_SPRITE_H
