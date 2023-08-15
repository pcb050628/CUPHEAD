#pragma once
#include "meGameObject.h"

namespace me
{
	class CarrotMissile : public GameObject
	{
	public:
		CarrotMissile(const std::wstring& name);
		virtual ~CarrotMissile() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void SetTarget(GameObject* target) { Target = target->GetComponent<Transform>(); }

	private:
		float hp;

		Transform* mTransform;
		CircleCollider* mCollider;
		SpriteRenderer* mSpriteRenderer;
		Transform* Target;
		bool crash;

		float timeCount;
	};
}

