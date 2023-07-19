#pragma once
#include "meGameObject.h"

namespace me
{
	class Player_stage : public GameObject
	{
	public:
		enum class Player_state
		{
			Idle,
			Aim,
			Run,
			Duck,
			Shooting,
			Jumping,
		};

		Player_stage(const std::wstring& name);
		virtual ~Player_stage() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void Idle();
		void Aim();
		void Run();
		void Duck();
		void Shooting();
		void Jumping();

	private:
		Animator* mAnimator;

		Player_state mState;

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
