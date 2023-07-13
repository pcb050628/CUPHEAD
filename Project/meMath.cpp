#include "meMath.h"
#include "DEFAULT.h"

namespace me::math
{
	Vector2 Vector2::One = Vector2(1.f, 1.f);
	Vector2 Vector2::Zero = Vector2(0.f, 0.f);
	Vector2 Vector2::Up = Vector2(0.f, -1.f);
	Vector2 Vector2::Right = Vector2(1.f, 0.f);
	Vector2 Vector2::Client_Size = Vector2(CLIENT_WIDTH / 2, CLIENT_HEIGHT / 2);
}