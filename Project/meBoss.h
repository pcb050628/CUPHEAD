#pragma once
#include "meGameObject.h"

namespace me
{
	enum class BossPhase_state
	{
		intro,
		phase1,
		phase2,
		phase3,
		death,
	};

	class Boss : public GameObject
	{
	public:
		Boss(const std::wstring& name);
		virtual ~Boss() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		virtual void Intro();
		virtual void Phase1();
		virtual void Phase2();
		virtual void Phase3();
		virtual void Death();

		virtual void SetState(BossPhase_state state) { mState = state; }
		virtual BossPhase_state GetState() { return mState; }

		virtual int GetHP() { return mHP; }
		virtual void SetHP(int value) { mHP = value; }

	private:
		BossPhase_state mState;

		int mHP;

	};
}
