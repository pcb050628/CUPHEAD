#pragma once
#include "meGameObject.h"

namespace me
{	
	class Dust : public GameObject
	{
	public:
		Dust(const std::wstring& name);
		virtual ~Dust() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:
		float hp;

		Transform* mTransform;
		CircleCollider* mCollider;
		Animator* mAnimator;

		bool crash;
	};
}

