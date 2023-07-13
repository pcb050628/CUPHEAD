#include "meCamera.h"
#include "meApplication.h"
#include "meSceneManager.h"
#include "meGameObject.h"
#include "meTransform.h"

//extern me::Application app;

namespace me
{
	math::Vector2 Camera::mLookPos = math::Vector2::Zero;
	math::Vector2 Camera::mDist = math::Vector2::Zero;
	math::Vector2 Camera::mResolution = math::Vector2::Zero;

	GameObject* Camera::mTarget = nullptr;

	void Camera::Init()
	{
		mResolution = math::Vector2::Client_Size;

		mDist = mLookPos - (mResolution / 2);
	}

	void Camera::Update()
	{
		if (mTarget != nullptr) 
			mLookPos = mTarget->GetComponent<Transform>()->GetPos();

		mDist = mLookPos - (mResolution / 2);
	}

	math::Vector2 Camera::AffectCameraPos(math::Vector2& pos)
	{
		return pos - mDist;
	}
}