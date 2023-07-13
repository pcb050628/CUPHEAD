#pragma once
#include "meGameObject.h"

namespace me
{
	class Player : public GameObject
	{
	public:
		Player(const std::wstring& name);
		virtual ~Player() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		SpriteRenderer* mFront_sr;
		SpriteRenderer* mBack_sr;
		SpriteRenderer* mHorizontal_sr;

		Animator* mFront_anim;
		Animator* mBack_anim;
		Animator* mHorizontal_anim;
	};
}

