#pragma once
#include "meGameObject.h"

namespace me
{	
	class Tear : public GameObject
	{
	public:
		Tear(const std::wstring& name);
		virtual ~Tear() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:
		Transform* mTransform;
		Rigidbody* mRigidbody;
		CircleCollider* mCollider;
		Animator* mAnimator;
		SpriteRenderer* mSpriteRenderer;

		bool splash;
	};
}

