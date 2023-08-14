#pragma once
#include "meBoss.h"
#include "meSensor.h"

namespace me
{
	class RootPack_Boss : public Boss
	{
	public:
		RootPack_Boss(const std::wstring& name);
		virtual ~RootPack_Boss() override;

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


	private:
		CircleCollider* mMainCollider;
		Animator* mMainAnimator;

		// Èëµ¢ÀÌ¶û ´«¹° Åº¸· ¸¸µé±â
	};
}

