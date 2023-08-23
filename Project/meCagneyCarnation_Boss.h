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
		virtual void Death() override;

		//첫 페이즈
		void CreateBoomerang();
		void FaceHighAttack();
		void FaceLowAttack();

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

		// 모든 패턴의 공용 쿨타임
		bool canAttack;
		float prevAttackTime;

		//boomerang
		bool			mbCreateBoomerang;
		float			createStartTime;
		bool			isCreate;

		//Face Attack
		Sensor* mFASensor;
		bool	mbFaceHighAttack;
		bool	mbFaceLowAttack;
		float	faStartTime;

		//final form
		float transitionStartTime;

		Animator*		mVineIntroAnimator;
		Sensor*			mVineFloorSensor;

		// firing pollen
		bool			mbFiringPollen;
		float			fpStartTime;
		bool			isFire;

		//vine stab
		//animator offset y : 10 / x : -350, -600, -850
		int				vineStabT;
		bool			mbVineStab;
		float			vsStartTime;
		Animator*		mVineStabAnimatorOne;
		Animator*		mVineStabAnimatorTwo;
		Sensor*			mVineStabSensorOne;
		Sensor*			mVineStabSensorTwo;

	};
}

