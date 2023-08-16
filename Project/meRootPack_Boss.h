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

		void PotatoIntro();
		void OnionIntro();
		void CarrotIntro();

		void PotatoShoot();
		void OnionCry();
		void CarrotAttack();

		void PotatoOutro();
		void OnionOutro();
		void CarrotOutro();

		void DustSpawn();

	private:
		CircleCollider* mMainCollider;
		Animator* mMainAnimator;

		float phSavedTime;

		bool canAttack;
		float prevAttackTime;

		int potatoShootCount;
		bool potatoCanShoot;
		float prevShootTime;

		bool CheckOne;
		bool CheckTwo;
		bool CheckThree;
	};
}

