#pragma once
#include "meBullet.h"

namespace me
{
	class Chaser : public Bullet
	{
	public:
		Chaser(const std::wstring& name);
		virtual ~Chaser() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

	private:
		Transform*	mTransform;
		Animator*	mAnimator;
		math::Vector2* Target;

	};
}

