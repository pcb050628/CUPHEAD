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
			Intro,
			Idle,
			Aim,
			Run,
			Duck,
			Shooting,
			Jump,
			Hit,
			Dash,
			Dead
		};

		enum class GroundType
		{
			floor,
			platform,
			none
		};

		enum class ShooterType
		{
			Peashooter,
			Chaser,
		};

		Player_stage(const std::wstring& name);
		virtual ~Player_stage() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void Intro();
		void Idle();
		void Aim();
		void Run();
		void Duck();
		void Shooting();
		void Jump();
		void Parry();
		void Hit();
		void Dash();
		void Dead();

		bool isParrySuccess() { return parrySuccess; }

		void SpawnBullet(math::Vector2 dir = math::Vector2(1, 0));
		void ChangeShooterType() {
			if (shooterType == ShooterType::Peashooter)
				shooterType = ShooterType::Chaser;
			else
				shooterType = ShooterType::Peashooter;
		}

		void GetHit();

		int GetHP() { return HP; }

		bool GetIsGround() { return mIsGround; }
		void SetIsGround(bool value) { mIsGround = value; }

		void SetGroundType(GroundType type) { groundType = type; }

		Player_state GetPrevState() { return mPrevState; }
		Player_state GetCurState() { return mCurState; }

	private:
		int HP;

		ShooterType shooterType;
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

		GroundType groundType;
		bool mIsGround;

		bool mIsHit;
		float mHitStartTime;
		float mHitHoldingTime;
		float mInvincibleTime;

		bool mIsJumping;
		float mJumpMinHeight;
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
