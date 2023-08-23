#pragma once
#include "meGameObject.h"

namespace me
{
	class Pollen : public GameObject
	{
	public:
		Pollen(const std::wstring& name);
		virtual ~Pollen() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:
		Transform*			mTransform;
		CircleCollider*		mCollider;
		Animator*			mAnimator;

		bool				button;
	};
}

