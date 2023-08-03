#pragma once
#include "DEFAULT.h"
#include "meScene.h"

namespace me
{
	class Application
	{
	public:
		Application();
		~Application();

		void Init(HWND hwnd);

		void Run();
		void Update();
		void Render();

		void Release();

		HWND GetHwnd() { return mHwnd; }
		HDC GetHDC() { return mHdc; }

		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		HWND mHwnd;
		HDC mHdc;
		HBITMAP mBackBuffer;
		HDC mBackHdc;

		int mWidth;
		int mHeight;
	};
}

