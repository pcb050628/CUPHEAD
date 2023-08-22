#pragma once
#include "meBoss.h"
#include "meSensor.h"

namespace me
{
	class CagneyCarnation_Boss : public Boss
	{
	public:
		CagneyCarnation_Boss(const std::wstring& name);
		virtual ~CagneyCarnation_Boss() override;

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

		//첫 페이즈
		void CreateBoomerang();
		void FaceAttack();

		// 두번쨰 페이즈
		void FiringPollen();
		void VineStab();


		void TransitionToPh2();

	private:
		//default
		Transform*		mTransform;
		Sensor*			mMainSensor;
		Sensor*			mHitSensor;
		Animator*		mMainAnimator;

		//ph1
		Sensor*			mFASensor;

		//final form
		Animator*		mVineIntroAnimator;
		Animator*		mVineStabAnimator;

	};
}

