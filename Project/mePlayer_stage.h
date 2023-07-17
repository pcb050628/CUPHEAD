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
		bool mIsRun;
		bool mIsDuck;
		bool mIsShooting;
		bool mIsJumping;
		bool mIsLookUp;
		bool mIsLookDiagonalUp;
		bool mIsLookDown;
		bool mIsLookDiagonalDown;
		float mJumpMaxHeight;
		float mJumpStartHeight;
	};
}
