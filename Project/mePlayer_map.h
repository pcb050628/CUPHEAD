#pragma once
#include "meGameObject.h"

namespace me
{
	class Player_map : public GameObject
	{
	public:
		Player_map(const std::wstring& name);
		virtual ~Player_map() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

	private:
		Transform* mTransform;
		Animator* mAnimator;
	};
}

