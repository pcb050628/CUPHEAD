#pragma once

namespace me::math
{
	struct Vector2
	{
		static Vector2 One;
		static Vector2 Zero;
		static Vector2 Up;
		static Vector2 Right;
		static Vector2 Client_Size;

		float x;
		float y;

		Vector2()
			:x(0.0f)
			, y(0.0f)
		{

		}

		Vector2(float _x, float _y)
			: x(_x)
			, y(_y)
		{

		}

		void Clear()
		{
			x = 0.f;
			y = 0.f;
		}

		float Length()
		{
			return sqrtf(pow(x, 2) + pow(y, 2));
		}

		Vector2& normalize()
		{
			float distance = Length();

			x /= distance;
			y /= distance;

			return *this;
		}

		void operator+=(const Vector2& other)
		{
			x += other.x;
			y += other.y;
		}

		void operator-=(const Vector2& other)
		{
			x -= other.x;
			y -= other.y;
		}

		bool operator==(const Vector2& other)
		{
			return x == other.x && y == other.y;
		}

		Vector2& operator-()
		{
			x = -x;
			y = -y;
		
			return *this;
		}

		Vector2 operator/(const int& other)
		{
			Vector2 value(x / other, y / other);
			return value;
		}

		Vector2 operator/(const float& other)
		{
			Vector2 value(x / other, y / other);
			return value;
		}

		Vector2 operator-(const Vector2& other)
		{
			Vector2 value(x - other.x, y - other.y);
			return value;
		}

		Vector2 operator+(const Vector2& other)
		{
			Vector2 value(x + other.x, y + other.y);
			return value;
		}

		Vector2 operator*(const Vector2& other)
		{
			Vector2 value(x * other.x, y * other.y);
			return value;
		}

		Vector2 operator*(const float& other)
		{
			Vector2 value(x * other, y * other);
			return value;
		}
	};
}