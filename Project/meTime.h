#pragma once
#include "DEFAULT.h"

namespace me
{
	class Time
	{
	public:
		static void Init();
		static void Update();
		static void Render(HDC hdc);

		static float GetDeltaTime() { return mDeltaTime; }
		static float GetTime() { return time; }

	private:
		static LARGE_INTEGER mCpuFreq;
		static LARGE_INTEGER mCurFreq;
		static LARGE_INTEGER mPrevFreq;

		static float mDeltaTime;

		static float time;
	};
}

