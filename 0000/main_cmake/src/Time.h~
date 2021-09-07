#ifndef TIME_H
#define TIME_H

namespace Cris {
	class Time {
	  public:
		Time( ) { Init( ); }

		[[nodiscard]] float GetDeltaTime( ) const { return mDeltaTime; }
		// [[nodiscard]] float GetMillliSeconds( ) const {
		// 	return mDeltaTime * 1000.0F;
		// }

		void Init( );
		void SetFPS(float fps) { mFPS = fps; }
		void SetFPSLimit(float fpsl) { mFPSLimit = fpsl; }

		/* Cast the class as a Float */
		// operator float( ) const { return mTime; }

	  private:
		const float SECONDS = 1000.0F;

		// float mLastTime { };
		int mLastTime { };
		float mFPS = 30;
		float mFPSLimit = 1.5F;

		float mDeltaTime { };
		float mLastUpdate { };
		float mCurrentUpdate { };
	};
}	// namespace Cris

#endif	 //	TIME_H
