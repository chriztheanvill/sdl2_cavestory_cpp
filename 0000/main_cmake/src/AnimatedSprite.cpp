#include "./AnimatedSprite.h"
#include "./Graphics.h"
#include <fmt/color.h>

// AnimatedSprite::AnimatedSprite( ) {}
AnimatedSprite::AnimatedSprite(Graphics& graphics,
							   const std::string& path,
							   SDL_Rect source,
							   SDL_Rect pos,
							   float UpdateTime)
	: Sprite(graphics, path, source, pos)
	, mFrameIndex(0)
	, mTimeToUpdate(UpdateTime)
	, mVisible(true)
	, mCurrentAnimationOnce(false)
	, mCurrentAnimation("") {}

/* ############################################################### */
/* ############################################################### */
void AnimatedSprite::AddAnimation(int frames,
								  const std::string& name,
								  SDL_Rect rect,
								  Vec2 offset) {
	std::vector<SDL_Rect> rectangles;

	for (int i = 0; i < frames; i++) {
		SDL_Rect newRect = { (i + rect.x) * rect.w, rect.y, rect.w, rect.h };
		rectangles.push_back(newRect);
	}

	mAnimations.insert(std::pair(name, rectangles));
	mOffsets.insert(std::pair(name, offset));
}

/* ############################################################### */
/* ############################################################### */
void AnimatedSprite::ResetAnimations( ) {
	mAnimations.clear( );
	mOffsets.clear( );
}

/* ############################################################### */
/* ############################################################### */
void AnimatedSprite::PlayAnimation(const std::string& Animation, bool once) {
	//
	mCurrentAnimationOnce = once;
	if (mCurrentAnimation != Animation) {
		mCurrentAnimation = Animation;
		mFrameIndex = 0;
	}
}

/* ######################################################################### */
void AnimatedSprite::SetVisible(bool visible) { mVisible = visible; }

/* ######################################################################### */
void AnimatedSprite::StopAnimation( ) {
	mFrameIndex = 0;
	AnimationDone(mCurrentAnimation);
}

/* ######################################################################### */
void AnimatedSprite::Update(float DeltaTime) {
	Sprite::Update(DeltaTime);

	if (mAnimations[mCurrentAnimation].size( ) > 1) {
		mTimeElapsed += 10;
		// mTimeElapsed += (DeltaTime * 1000);
	} else {
		mTimeElapsed = 0;
	}

	// fmt::print("Deltatime: {}\n", DeltaTime);
	// fmt::print("Deltatime * 1000: {}\n", DeltaTime * 1000);
	// fmt::print("mTimeElapsed: {}\n", mTimeElapsed);
	// fmt::print("TimeToUpdate: {}\n", mTimeToUpdate);
	if (mTimeElapsed > mTimeToUpdate) {
		mTimeElapsed = 0;
		// mTimeElapsed -= mTimeToUpdate;
		if (mFrameIndex < mAnimations[mCurrentAnimation].size( ) - 1) {
			mFrameIndex++;
		} else {
			if (mCurrentAnimationOnce) { SetVisible(false); }
			mFrameIndex = 0;
			AnimationDone(mCurrentAnimation);
		}
	}
}

/* ######################################################################### */
void AnimatedSprite::Draw(Graphics& graphics, SDL_Rect& pos) {
	if (mVisible) {
		SDL_Rect dest;
		dest.x = pos.x + mOffsets[mCurrentAnimation].x;
		dest.y = pos.y + mOffsets[mCurrentAnimation].y;
		dest.w = mSource.w * Constants::SPRITE_SCALE;
		dest.h = mSource.h * Constants::SPRITE_SCALE;

		SDL_Rect sourceRect = mAnimations[mCurrentAnimation][mFrameIndex];
		graphics.blitSurface(mSpriteSheet, &sourceRect, &dest);
	}
}

// void AnimatedSprite::SetupAnimation( ) {
// 	SDL_Rect RunLeft { 0, 0, 16, 16 };
// 	SDL_Rect RunRight { 0, 16, 16, 16 };
// 	AddAnimation(3, "RunLeft", RunLeft, Vec2(50, -100));
// 	AddAnimation(3, "RunRight", RunRight, Vec2(50, -100));
// }
