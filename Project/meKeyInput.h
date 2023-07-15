#pragma once
#include "DEFAULT.h"

namespace me
{
	enum class KeyCode
	{
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P,
		Q, R, S, T, U, V, W, X, Y, Z,
		Space, Enter, UpArrow, DownArrow, RightArrow, LeftArrow, ESC,
		END
	};

	enum class KeyState
	{
		Up, Down, Pressed, Released, None
	};

	class KeyInput
	{
	public:
		struct Key
		{
			KeyCode code;
			KeyState state;
			bool Pressed;

			Key(KeyCode code)
				: code(code)
				, state(KeyState::None)
				, Pressed(false)
			{

			}
		};

		KeyInput();
		~KeyInput();

		static void Init();
		static void Update();

		static bool GetKeyDown(KeyCode code) { return mKeys[(int)code].state == KeyState::Down; }
		static bool GetKeyUp(KeyCode code) { return mKeys[(int)code].state == KeyState::Up; }
		static bool GetKeyReleased(KeyCode code) { return mKeys[(int)code].state == KeyState::Released; }
		static bool GetKey(KeyCode code) { return mKeys[(int)code].Pressed; }

	private:
		static std::vector<Key> mKeys;
	};
}