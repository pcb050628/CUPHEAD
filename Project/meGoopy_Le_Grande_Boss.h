#pragma once
#include "meBoss.h"
#include "meSensor.h"

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

		void Jump();
		void MoveUp();
		void MoveDown();

		void Punch();

		void Smash();

	private:
		Transform* mTransform;
		Animator* mAnimator;

		CircleCollider* mMainCollider;

		Sensor* mPunchCollider;
		Sensor* mPunchSensor;
		bool mIsPunching;
		bool stretch;
		bool back;
		float PunchHoldingTime;
		float startTime;
		float punchCooldown;

		BoxCollider* mSmashCollider;

		bool mIsGround;

		bool mIsJumping;
		float mJumpMaxHeight;
		float mJumpStartPoint;

		bool mFlip;
	};
}

