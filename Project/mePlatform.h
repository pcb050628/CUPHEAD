#pragma once
#include "meGameObject.h"

namespace me
{
	class Platform : public GameObject
	{
	public:
		Platform(const std::wstring& name);
		virtual ~Platform() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:
		Transform*	mTransform;
		Animator*	mAnimator;

	};
}

