#pragma once
#include "meCollider.h"

namespace me
{
	class CircleCollider : public Collider
	{
	public:
		CircleCollider(GameObject* gobj, const std::wstring& name);
		virtual ~CircleCollider() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		virtual float GetVerticalRadius() { return mVerticalRadius; }
		virtual float GetHorizontalRadius() { return mHorizontalRadius; }

	private:
		float mVerticalRadius;
		float mHorizontalRadius;

	};
}

