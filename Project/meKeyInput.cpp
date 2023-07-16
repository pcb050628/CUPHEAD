#include "meKeyInput.h"

namespace me
{
	std::vector<KeyInput::Key> KeyInput::mKeys = {};
	bool KeyInput::mAllKeyUp = true;

	int ASCII[(int)KeyCode::END] =
	{
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L','M','N','O','P',
		'Q','R','S','T','U','V','W','X','Y','Z',
		VK_SPACE, VK_RETURN, VK_UP, VK_DOWN, VK_RIGHT, VK_LEFT, VK_ESCAPE
	};

	KeyInput::KeyInput()
	{

	}

	KeyInput::~KeyInput()
	{

	}

	void KeyInput::Init()
	{
		for (int i = 0; i < (int)KeyCode::END; i++)
		{
			mKeys.push_back((KeyCode)i);
		}
	}

	void KeyInput::Update()
	{
		mAllKeyUp = true;
		for (int i = 0; i < mKeys.size(); i++)
		{
			if (GetAsyncKeyState(ASCII[i]) && 0x8000)
			{
				if (mKeys[i].Pressed)
					mKeys[i].state = KeyState::Pressed;
				else
					mKeys[i].state = KeyState::Down;

				mKeys[i].Pressed = true;
				mAllKeyUp = false;
			}
			else
			{
				if (mKeys[i].state == KeyState::Down || mKeys[i].state == KeyState::Pressed)
					mKeys[i].state = KeyState::Released;
				else
					mKeys[i].state = KeyState::Up;

				mKeys[i].Pressed = false;
			}
		}
	}
}