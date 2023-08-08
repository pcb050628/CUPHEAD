#pragma once
#include "meGameObject.h"
#include "meSound.h"

namespace me
{
	class Player_stage : public GameObject
	{
	public:
		enum class Player_state
		{
			none,
			Idle,
			Aim,
			Run,
			Duck,
			Shooting,
			Jump,
			Hit,
			Dash,
		};

		Player_stage(const std::wstring& name);
		virtual ~Player_stage() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void Idle();
		void Aim();
		void Run();
		void Duck();
		void Shooting();
		void Jump();
		void Parry();
		void Hit();
		void Dash();

		bool isParrySuccess() { return parrySuccess; }

		void SpawnBullet(math::Vector2 dir = math::Vector2(1, 0));

		void GetHit();

		int GetHP() { return HP; }

	private:
		int HP;

		float shootDelay;
		float shootPrevTime;

		Animator* mShootAnim_R;
		Animator* mShootAnim_L;
		Animator* mAnimator;
		Transform* mTransform;
		BoxCollider* mCollider;

		Sound* jumpSound;
		Sound* shootSound;
		Sound* hitSound;
		Sound* dashSound;
		Sound* parrySound;

		Player_state mCurState;
		Player_state mPrevState;

		bool mIsGround;

		bool mIsHit;
		float mHitStartTime;
		float mHitHoldingTime;
		float mInvincibleTime;

		bool mIsJumping;
		float mJumpMaxHeight;
		float mJumpStartHeight;

		bool canParry;
		bool mIsParrying;
		float mParryStartTime;
		float mParryHoldingTime;

		bool parrySuccess;

		bool mIsDash;
		float mDashStartPoint;
		float mDashMaxDist;
		bool mDashFlip;
	};
}
