#pragma once
#include "meBoss.h"
#include "meSensor.h"
#include "meSound.h"
#include "meRigidbody.h"

namespace me
{	
	class Goopy_Le_Grande_Boss : public Boss
	{
	public:
		Goopy_Le_Grande_Boss(const std::wstring& name);
		virtual ~Goopy_Le_Grande_Boss() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		virtual void Intro() override;
		virtual void Phase1() override;
		virtual void Phase2() override;
		virtual void Phase3() override;
		virtual void Death() override;

		void TransitionToPh2();
		void TransitionToPh3();
		void Ph3Intro();

		void Jump();
		void JumpEffect();

		void Punch();

		void Smash();
		void TombMove();

	private:
		Transform*	mTransform;
		Rigidbody*	mRigidbody;

		Animator*	mMainAnimator;
		Animator*	mPh2DustAnimator;
		Animator*	mPh3IntroAnimator;

		CircleCollider* mMainCollider;

		float attackTime;
		float attackCooldown;
		Sensor* mPlayerSensor;

		Sensor* mPunchCollider;
		bool mIsPunching;
		bool stretch;
		bool back;
		float punchStartTime;
		float smallPunchHoldingTime;
		float bigPunchHoldingTime;
		Sound* stretchSound;

		bool mIsSmashing;
		Sensor* mSmashCollider;

		bool mIsJumping;
		bool jumpUp;
		bool jumpDown;
		float prevVelocity;
		float mJumpMaxHeight;
		Sound* smallJumpSound;
		Sound* smallLandSound;
		Sound* bigJumpSound;
		Sound* bigLandSound;

		bool mFlip;

		bool phCheckOne;
		bool phCheckTwo;
		bool phCheckThree;

		float startTimePh;
	};
}

