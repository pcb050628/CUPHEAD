#pragma once
#include <cmath>

namespace me::math
{
#define PI 3.141592

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

		void clear()
		{
			x = 0.f;
			y = 0.f;
		}

		float length()
		{
			return sqrtf(x * x + y * y);
		}

		Vector2 normalize()
		{
			float len = length();
			x /= len;
			y /= len;

			return *this;
		}

		bool operator==(const Vector2& other)
		{
			return (x == other.x && y == other.y);
		}

		bool operator!=(const Vector2& other)
		{
			return (x != other.x && y != other.y);
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

		bool operator<=(const Vector2& other)
		{
			return x <= other.x && y <= other.y;
		}

		bool operator>=(const Vector2& other)
		{
			return x >= other.x && y >= other.y;
		}

		Vector2& operator *=(const float& value)
		{
			x *= value;
			y *= value;

			return *this;
		}

		Vector2 operator-()
		{		
			return Vector2(-x, -y);
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


	inline Vector2 Rotate(Vector2 vector, float degree)
	{
		float radian = (degree / 180.f) * PI;
		vector.normalize();
		float x = cosf(radian) * vector.x - sinf(radian) * vector.y;
		float y = sinf(radian) * vector.x + cosf(radian) * vector.y;

		return Vector2(x, y);
	}

	inline float Dot(Vector2& v1, Vector2& v2)
	{
		return (v1.x * v2.x) + (v1.y * v2.y);
	}

	inline float Cross(Vector2 v1, Vector2 v2)
	{
		return (v1.x * v2.y) - (v1.y * v2.x);
	}
}