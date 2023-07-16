#pragma once
#include "meGameObject.h"

namespace me
{
	class Player_stage : public GameObject
	{
	public:
		Player_stage(const std::wstring& name);
		virtual ~Player_stage() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		Animator* mAnimator;

		bool mIsAim;
		bool mIsDuck;
		bool mIsJumping;
		float mJumpMaxHeight;
		float mJumpStartHeight;
	};
}
