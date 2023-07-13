#include "meTime.h"

namespace me
{
	LARGE_INTEGER Time::mCpuFreq = {};
	LARGE_INTEGER Time::mCurFreq = {};
	LARGE_INTEGER Time::mPrevFreq = {};

	float Time::mDeltaTime = 0.f;

	float Time::time = 0.f;

	void Time::Init()
	{
		QueryPerformanceFrequency(&mCpuFreq);
		QueryPerformanceCounter(&mPrevFreq);
	}

	void Time::Update()
	{
		QueryPerformanceCounter(&mCurFreq);

		float diffrenceFreq = static_cast<float>(mCurFreq.QuadPart - mPrevFreq.QuadPart);

		mDeltaTime = diffrenceFreq / static_cast<float>(mCpuFreq.QuadPart);
		mPrevFreq.QuadPart = mCurFreq.QuadPart;

		time += mDeltaTime;
	}

	void Time::Render(HDC hdc)
	{
		wchar_t buffer[50] = {};
		float fps = 1.0 / mDeltaTime;

		swprintf_s(buffer, L"fps : %f", fps);
		int strLen = wcsnlen_s(buffer, 50);

		TextOut(hdc, 10, 10, buffer, strLen);
	}
}