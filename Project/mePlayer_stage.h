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
		};

		Player_stage(const std::wstring& name);
		virtual ~Player_stage() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(BoxCollider* other) override;
		virtual void OnCollisionStay(BoxCollider* other) override;
		virtual void OnCollisionExit(BoxCollider* other) override;

		void Idle();
		void Aim();
		void Run();
		void Duck();
		void Shooting();
		void Jump();

		void SpawnBullet();

	private:
		int HP;

		float shootDelay;
		float shootPrevTime;

		Animator* mAnimator;

		Player_state mState;

		bool mIsGround;
		bool mIsJumping;
		float mJumpMaxHeight;
		float mJumpStartHeight;
	};
}
