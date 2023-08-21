#pragma once
#include "meGameObject.h"

namespace me
{
	class Boomerang : public GameObject
	{
	public:
		Boomerang(const std::wstring& name);
		virtual ~Boomerang() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:
		Transform*		mTransform;
		BoxCollider*	mCollider;
		Animator*		mAnimator;

		//Sound*			mSound; // 이동하는 소리 구하면 적용

	};
}

