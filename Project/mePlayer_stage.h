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
		int HP;

		Animator* mAnimator;

		Player_state mState;

		BoxCollider* mGroundCheckBox;
		float mJumpMaxHeight;
		float mJumpStartHeight;
	};
}
