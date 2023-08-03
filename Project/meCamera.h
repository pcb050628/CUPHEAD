#pragma once
#include "DEFAULT.h"

namespace me
{
	class Camera
	{
	public:
		static void Init();
		static void Update();
		static void Reset();

		static void SetTarget(class GameObject* target) { mTarget = target; }

		static math::Vector2 AffectCameraPos(math::Vector2& pos);

	private:
		static math::Vector2 mLookPos;
		static math::Vector2 mDist;
		static math::Vector2 mResolution;

		static class GameObject* mTarget;
	};
}

