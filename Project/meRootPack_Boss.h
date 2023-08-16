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
		void PotatoShoot();
		void PotatoOutro();

		void OnionIntro();
		void OnionCry();
		void OnionOutro();

		void CarrotIntro();
		void CarrotAttack();

		void DustSpawn();
		void TearSpawn(int idx);

	private:
		Transform* mTransform;
		CircleCollider* mMainCollider;
		Animator* mMainAnimator;

		float phSavedTime;

		bool canAttack;
		float prevAttackTime;

		int potatoShootCount;
		bool potatoCanShoot;
		float prevShootTime;

		float tearPosX[10] = {-700, -560, -390, -170, -80, 110, 230, 300, 430, 590};
		float prevStartTime;

		bool CheckOne;
		bool CheckTwo;
		bool CheckThree;
	};
}

