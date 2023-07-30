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
			Jump,
			Hit,
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
		void Hit();

		void SpawnBullet(math::Vector2 dir = math::Vector2(1, 0));

	private:
		int HP;

		float shootDelay;
		float shootPrevTime;

		Animator* mAnimator;
		Animator* mShootAnim;
		Transform* mTransform;
		BoxCollider* mCollider;

		Player_state mState;

		bool mIsGround;

		bool mIsHit;
		float mHitStartTime; // 수정해야하는 부분
		float mHitHoldingTime; // 피격 유지 시간
		float mInvincibleTime;

		bool mIsJumping;
		float mJumpMaxHeight;
		float mJumpStartHeight;
	};
}
