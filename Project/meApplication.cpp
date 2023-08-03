#include "meApplication.h"
#include "meSceneManager.h"
#include "meColliderManager.h"
#include "meCamera.h"
#include "meSoundManager.h"

me::Application::Application()
	: mHwnd(NULL)
	, mHdc(NULL)
	, mBackBuffer(NULL)
	, mBackHdc(NULL)
	, mWidth(NULL)
	, mHeight(NULL)
{

}

me::Application::~Application()
{

}

void me::Application::Init(HWND hwnd)
{
	mHwnd = hwnd;
	mHdc = GetDC(hwnd);
	mWidth = 1280;
	mHeight = 720;

	RECT rect = { 0, 0, mWidth, mHeight };
	DWORD Style, ExStyle;

	Style = GetWindowLong(mHwnd, GWL_STYLE);
	ExStyle = GetWindowLong(mHwnd, GWL_EXSTYLE);

	AdjustWindowRectEx(&rect, Style, GetMenu(mHwnd) != NULL, ExStyle);

	SetWindowPos(mHwnd, nullptr, 0, 0, rect.right - rect.left, rect.bottom - rect.top, 0);
	ShowWindow(mHwnd, SW_SHOWNORMAL);

	mBackBuffer = CreateCompatibleBitmap(mHdc, mWidth, mHeight);
	mBackHdc = CreateCompatibleDC(mHdc);

	HDC defaultDC = (HDC)SelectObject(mBackHdc, mBackBuffer);

	DeleteObject(defaultDC);

	RECT tmp = {};

	GetClientRect(mHwnd, &tmp);

	me::CLIENT_WIDTH = (float)tmp.right;
	me::CLIENT_HEIGHT = (float)tmp.bottom;

	math::Vector2::Client_Size = math::Vector2(CLIENT_WIDTH, CLIENT_HEIGHT);

	Time::Init();
	KeyInput::Init();
	Camera::Init();
	ColliderManager::Init();
	SoundManager::Init();
	SceneManager::Init();
}

void me::Application::Run()
{
	Update();
	Render();
}

void me::Application::Update()
{
	Time::Update();
	KeyInput::Update();
	Camera::Update();
	SceneManager::Update();
	ColliderManager::Update();
}

void me::Application::Render()
{
	Rectangle(mBackHdc, -1, -1, mWidth + 1, mHeight + 1);

	SceneManager::Render(mBackHdc);
	Time::Render(mBackHdc);

	BitBlt(mHdc, 0, 0, mWidth, mHeight, mBackHdc, 0, 0, SRCCOPY);
}
