#include "meCagneyCarnation_Boss.h"
#include "meResourceManager.h"
#include "meSceneManager.h"
#include "meBoomerang.h"
#include "mePollen.h"
#include "meBullet.h"

namespace me
{
	CagneyCarnation_Boss::CagneyCarnation_Boss(const std::wstring& name) : Boss(name)
		//default
		, mTransform(nullptr), mMainSensor(nullptr), mHitSensor(nullptr), mMainAnimator(nullptr)
		// all pattern
		, canAttack(true), prevAttackTime(-1)								
		// boomerang
		, createStartTime(-1), mbCreateBoomerang(false), isCreate(false)	
		// Face Attack
		, mFASensor(nullptr), mbFaceHighAttack(false), mbFaceLowAttack(false), faStartTime(-1)
		// vine intro
		, mVineIntroAnimator(nullptr), mVineFloorSensor(nullptr)
		// transition
		, transitionStartTime(-1)
		// firing pollen
		, mbFiringPollen(false), fpStartTime(-1), isFire(false)
		// vine stab
		, mVineStabAnimatorOne(nullptr), mVineStabAnimatorTwo(nullptr), mbVineStab(false), vsStartTime(-1)
		, vineStabT(-1), mVineStabSensorOne(nullptr), mVineStabSensorTwo(nullptr)
	{
	}
	CagneyCarnation_Boss::~CagneyCarnation_Boss()
	{
		SceneManager::Destroy(mMainSensor);
		SceneManager::Destroy(mHitSensor);
		SceneManager::Destroy(mFASensor);
		SceneManager::Destroy(mVineFloorSensor);
		SceneManager::Destroy(mVineStabSensorOne);
		SceneManager::Destroy(mVineStabSensorTwo);
		mMainSensor = nullptr;
		mFASensor = nullptr;
		mHitSensor = nullptr;
		mVineFloorSensor = nullptr;
		mVineStabSensorOne = nullptr;
		mVineStabSensorTwo = nullptr;
	}

	void CagneyCarnation_Boss::Init()
	{
		Boss::Init();

		SetHP(1500); // 1500

		mTransform = GetComponent<Transform>();

		mMainSensor = SceneManager::Instantiate<Sensor>(L"carnation_stage", enums::eLayer::Sensor, mTransform->GetPos(), L"MainSensor");
		mMainSensor->SetOwner(this);
		mHitSensor = SceneManager::Instantiate<Sensor>(L"carnation_stage", enums::eLayer::Sensor, mTransform->GetPos(), L"HitSensor");
		mHitSensor->SetOwner(this);
		mMainAnimator = AddComponent<Animator>(L"MainAnimator");
		mFASensor = SceneManager::Instantiate<Sensor>(L"carnation_stage", enums::eLayer::Sensor, mTransform->GetPos(), L"FASensor");
		mFASensor->SetOwner(this);
		mVineIntroAnimator = AddComponent<Animator>(L"VineIntroAnimator");
		mVineStabAnimatorOne = AddComponent<Animator>(L"VineStabAnimator");
		mVineStabAnimatorTwo = AddComponent<Animator>(L"VineStabAnimator");
		mVineFloorSensor = SceneManager::Instantiate<Sensor>(L"carnation_stage", enums::eLayer::Sensor, mTransform->GetPos(), L"vine_floor");
		mVineFloorSensor->SetOwner(this);
		mVineStabSensorOne = SceneManager::Instantiate<Sensor>(L"carnation_stage", enums::eLayer::Sensor, mTransform->GetPos(), L"vine_stab_1");
		mVineStabSensorOne->SetOwner(this);
		mVineStabSensorTwo = SceneManager::Instantiate<Sensor>(L"carnation_stage", enums::eLayer::Sensor, mTransform->GetPos(), L"vine_stab_2");
		mVineStabSensorTwo->SetOwner(this);


		mMainSensor->SetColliderSize(math::Vector2(200, 600));
		mMainSensor->AddTargetType(enums::eGameObjType::player);

		mHitSensor->SetOffset(math::Vector2(0, -150));
		mHitSensor->SetColliderSize(math::Vector2(200, 250));
		mHitSensor->AddTargetType(enums::eGameObjType::player);
		mHitSensor->AddTargetType(enums::eGameObjType::bullet);

		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Carnation_intro", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Intro\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Carnation_idle", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Idle\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Carnation_FA_high", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Face Attack\\High\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Carnation_FA_low", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Face Attack\\Low\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Carnation_create_boomerang", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Creating Object\\"));

		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Carnation_Final_intro", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Final Form\\Intro\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Carnation_Final_idle", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Final Form\\Idle\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Carnation_Final_firing", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Final Form\\Firing Pollen\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Carnation_death", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Death\\"));

		mMainAnimator->GetAnim(L"Carnation_intro")->SetLoop(false);
		mMainAnimator->GetAnim(L"Carnation_idle")->SetDuration(0.05f);
		mMainAnimator->GetAnim(L"Carnation_FA_high")->SetDuration(0.1f);
		mMainAnimator->GetAnim(L"Carnation_FA_low")->SetDuration(0.1f);
		mMainAnimator->GetAnim(L"Carnation_create_boomerang")->SetLoop(false);
		mMainAnimator->GetAnim(L"Carnation_Final_intro")->SetDuration(0.1f);
		mMainAnimator->GetAnim(L"Carnation_Final_intro")->SetLoop(false);
		mMainAnimator->GetAnim(L"Carnation_Final_firing")->SetLoop(false);

		mFASensor->AddTargetType(enums::eGameObjType::player);
		mFASensor->SetActive(false);
		mFASensor->SetColliderSize(math::Vector2(100, 100));
		mFASensor->SetOffset(math::Vector2(0, 100));

		mVineIntroAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Vine_intro", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Final Form\\Vines\\main\\"));
		mVineStabAnimatorOne->AddAnim(*ResourceManager::Load<Animation>(L"Vine_stab_start", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Final Form\\Vines\\platform\\start\\"));
		mVineStabAnimatorTwo->AddAnim(*ResourceManager::Load<Animation>(L"Vine_stab_start", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Final Form\\Vines\\platform\\start\\"));
		mVineStabAnimatorOne->AddAnim(*ResourceManager::Load<Animation>(L"Vine_stab_end", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Final Form\\Vines\\platform\\end\\"));
		mVineStabAnimatorTwo->AddAnim(*ResourceManager::Load<Animation>(L"Vine_stab_end", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Final Form\\Vines\\platform\\end\\"));
		
		mVineStabAnimatorOne->GetAnim(L"Vine_stab_start")->SetLoop(false);
		mVineStabAnimatorTwo->GetAnim(L"Vine_stab_start")->SetLoop(false);
		mVineStabAnimatorOne->GetAnim(L"Vine_stab_end")->SetLoop(false);
		mVineStabAnimatorTwo->GetAnim(L"Vine_stab_end")->SetLoop(false);

		mVineIntroAnimator->GetAnim(L"Vine_intro")->SetLoop(false);
		mVineIntroAnimator->GetAnim(L"Vine_intro")->SetOffset(math::Vector2(-600, 250));

		mVineFloorSensor->AddTargetType(enums::eGameObjType::player);
		mVineFloorSensor->SetColliderSize(math::Vector2(1000, 100));
		mVineFloorSensor->SetOffset(math::Vector2(-650, 250));
		mVineFloorSensor->SetActive(false);

		mVineStabSensorOne->SetActive(false);
		mVineStabSensorTwo->SetActive(false);
		mVineStabSensorOne->SetColliderSize(math::Vector2(100, 500));
		mVineStabSensorTwo->SetColliderSize(math::Vector2(100, 500));
	}
	void CagneyCarnation_Boss::Update()
	{
		Boss::Update();

		if (mHitSensor->Sensed(enums::eGameObjType::bullet) == enums::SenseType::Enter)
			GetHit(dynamic_cast<Bullet*>(mHitSensor->GetSensedObj(enums::eGameObjType::bullet))->ReturnDmg());

		if (mHitSensor->Sensed(enums::eGameObjType::player) == enums::SenseType::Enter || mHitSensor->Sensed(enums::eGameObjType::player) == enums::SenseType::Stay)
			dynamic_cast<Player_stage*>(mHitSensor->GetSensedObj(enums::eGameObjType::player))->GetHit();
		if (mMainSensor->Sensed(enums::eGameObjType::player) == enums::SenseType::Enter || mMainSensor->Sensed(enums::eGameObjType::player) == enums::SenseType::Stay)
			dynamic_cast<Player_stage*>(mMainSensor->GetSensedObj(enums::eGameObjType::player))->GetHit();
		if (mVineFloorSensor->GetActive()
			&& mVineFloorSensor->Sensed(enums::eGameObjType::player) == enums::SenseType::Enter || mVineFloorSensor->Sensed(enums::eGameObjType::player) == enums::SenseType::Stay)
			dynamic_cast<Player_stage*>(mVineFloorSensor->GetSensedObj(enums::eGameObjType::player))->GetHit();
		if (mVineStabSensorOne->GetActive()
			&& mVineStabSensorOne->Sensed(enums::eGameObjType::player) == enums::SenseType::Enter || mVineStabSensorOne->Sensed(enums::eGameObjType::player) == enums::SenseType::Stay)
			dynamic_cast<Player_stage*>(mVineStabSensorOne->GetSensedObj(enums::eGameObjType::player))->GetHit();
		if (mVineStabSensorTwo->GetActive()
			&& mVineStabSensorTwo->Sensed(enums::eGameObjType::player) == enums::SenseType::Enter || mVineStabSensorTwo->Sensed(enums::eGameObjType::player) == enums::SenseType::Stay)
			dynamic_cast<Player_stage*>(mVineStabSensorTwo->GetSensedObj(enums::eGameObjType::player))->GetHit();
	

		if (GetIsHIt())
		{
			SetIsHit(false);
			mMainAnimator->FlashingStart();
		}
	}
	void CagneyCarnation_Boss::Render(HDC hdc)
	{
		Boss::Render(hdc);
	}

	void CagneyCarnation_Boss::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetTag() == enums::eGameObjType::player)
			dynamic_cast<Player_stage*>(other->GetOwner())->GetHit();
	}
	void CagneyCarnation_Boss::OnCollisionStay(Collider* other)
	{
		if (other->GetOwner()->GetTag() == enums::eGameObjType::player)
			dynamic_cast<Player_stage*>(other->GetOwner())->GetHit();
	}
	void CagneyCarnation_Boss::OnCollisionExit(Collider* other)
	{
	}

	void CagneyCarnation_Boss::Intro()
	{
		mMainAnimator->PlayAnim(L"Carnation_intro");
		if (mMainAnimator->GetCurAnim()->IsComplete())
			SetState(BossPhase_state::phase1);
	}
	void CagneyCarnation_Boss::Phase1()
	{
		if (GetHP() <= 690)
		{
			if (transitionStartTime == -1)
				transitionStartTime = Time::GetTime();

			TransitionToPh2();
			return;
		}

		if (canAttack)
		{
			if (!mbCreateBoomerang && !mbFaceHighAttack && !mbFaceLowAttack)
			{
				srand((unsigned int)(GetHP() + Time::GetTime() + Time::GetDeltaTime()));

				if ((rand() % 9) < 3)
				{
					mbCreateBoomerang = true;
					createStartTime = Time::GetTime();
				}
				else if ((rand() % 9) < 5)
				{
					mbFaceHighAttack = true;
					faStartTime = Time::GetTime();
				}
				else
				{
					mbFaceLowAttack = true;
					faStartTime = Time::GetTime();
				}
			}
			else
			{
				if (mbCreateBoomerang)
					CreateBoomerang();

				if (mbFaceHighAttack)
					FaceHighAttack();

				if (mbFaceLowAttack)
					FaceLowAttack();
			}
		}
		else
		{
			mMainAnimator->PlayAnim(L"Carnation_idle");
			if (prevAttackTime != -1 && fabs(prevAttackTime - Time::GetTime()) > 2.f)
			{
				canAttack = true;
				prevAttackTime = -1;
			}
		}
	}
	void CagneyCarnation_Boss::Phase2()
	{
		if (GetHP() <= 0)
		{
			SetState(BossPhase_state::death);
			return;
		}

		if (canAttack)
		{
			if (!mbFiringPollen && !mbVineStab)
			{
				srand((unsigned int)(GetHP() + Time::GetTime() + Time::GetDeltaTime()));

				if ((rand() % 10) < 5)
				{
					mbFiringPollen = true;
					fpStartTime = Time::GetTime();
				}
				else
				{
					mbVineStab = true;
					vsStartTime = Time::GetTime();
				}
			}
			else
			{
				if(mbFiringPollen)
					FiringPollen();

				if (mbVineStab)
					VineStab();
			}
		}
		else
		{
			mMainAnimator->PlayAnim(L"Carnation_Final_idle");
			if (prevAttackTime != -1 && fabs(prevAttackTime - Time::GetTime()) > 2.f)
			{
				canAttack = true;
				prevAttackTime = -1;
			}
		}
	}
	void CagneyCarnation_Boss::Death()
	{
		mMainAnimator->PlayAnim(L"Carnation_death");
	}

	void CagneyCarnation_Boss::CreateBoomerang()
	{
		mMainAnimator->PlayAnim(L"Carnation_create_boomerang");

		if ((fabs(createStartTime - Time::GetTime()) > 1.5f) && !isCreate)
		{
			SceneManager::Instantiate<Boomerang>(enums::eLayer::Enemy, math::Vector2(220, 0), L"boomerang");
			isCreate = true;
		}

		if (mMainAnimator->GetCurAnim()->IsComplete())
		{
			mbCreateBoomerang = false;
			isCreate = false;
			createStartTime = -1;
			canAttack = false;
			prevAttackTime = Time::GetTime();
		}
	}

	void CagneyCarnation_Boss::FaceHighAttack()
	{
		mMainAnimator->PlayAnim(L"Carnation_FA_high");
		if (mHitSensor->GetColliderSize().y == 250)
			mHitSensor->SetColliderSize(math::Vector2(200, 300));

		if (fabs(faStartTime - Time::GetTime()) > 1.3f)
		{
			if (mHitSensor->GetOffset().x < 0)
				mHitSensor->SetOffset(mHitSensor->GetOffset() + math::Vector2(1000 * Time::GetDeltaTime(), 0));

			if (mHitSensor->GetColliderSize().x >= 200)
				mHitSensor->SetColliderSize(mHitSensor->GetColliderSize() + math::Vector2(-1500 * Time::GetDeltaTime(), 0));

			if (mHitSensor->GetOffset().x >= 0 && mHitSensor->GetColliderSize().x <= 200)
			{
				mHitSensor->SetOffset(math::Vector2(0, -150));
				mHitSensor->SetColliderSize(math::Vector2(200, 250));

				mbFaceHighAttack = false;
				faStartTime = -1;
				canAttack = false;
				prevAttackTime = Time::GetTime();
			}
		}
		else if (fabs(faStartTime - Time::GetTime()) > 0.5f)
		{
			if(mHitSensor->GetOffset().x > -500)
				mHitSensor->SetOffset(mHitSensor->GetOffset() + math::Vector2(-1000 * Time::GetDeltaTime(), 0));

			if(mHitSensor->GetColliderSize().x < 900)
				mHitSensor->SetColliderSize(mHitSensor->GetColliderSize() + math::Vector2(1500 * Time::GetDeltaTime(), 0));
		}
	}
	void CagneyCarnation_Boss::FaceLowAttack()
	{
		mMainAnimator->PlayAnim(L"Carnation_FA_low");
		if(mHitSensor->GetColliderSize().y == 250)
			mHitSensor->SetColliderSize(math::Vector2(200, 150));

		if(mHitSensor->GetOffset().y == -150)
			mHitSensor->SetOffset(mHitSensor->GetOffset() + math::Vector2(0, 300));

		if (fabs(faStartTime - Time::GetTime()) > 1.3f)
		{
			if (mHitSensor->GetOffset().x < 0)
				mHitSensor->SetOffset(mHitSensor->GetOffset() + math::Vector2(1100 * Time::GetDeltaTime(), 0));

			if (mHitSensor->GetColliderSize().x >= 200)
				mHitSensor->SetColliderSize(mHitSensor->GetColliderSize() + math::Vector2(-1600 * Time::GetDeltaTime(), 0));

			if (mHitSensor->GetOffset().x >= 0 && mHitSensor->GetColliderSize().x <= 200)
			{
				mHitSensor->SetOffset(math::Vector2(0, -150));
				mHitSensor->SetColliderSize(math::Vector2(200, 250));

				mbFaceLowAttack = false;
				faStartTime = -1;
				canAttack = false;
				prevAttackTime = Time::GetTime();
			}
		}
		else if (fabs(faStartTime - Time::GetTime()) > 0.5f)
		{
			if (mHitSensor->GetOffset().x > -500)
				mHitSensor->SetOffset(mHitSensor->GetOffset() + math::Vector2(-1100 * Time::GetDeltaTime(), 0));

			if (mHitSensor->GetColliderSize().x < 900)
				mHitSensor->SetColliderSize(mHitSensor->GetColliderSize() + math::Vector2(1600 * Time::GetDeltaTime(), 0));
		}
	}

	void CagneyCarnation_Boss::FiringPollen()
	{
		mMainAnimator->PlayAnim(L"Carnation_Final_firing");

		if ((fabs(fpStartTime - Time::GetTime()) > 1.f) && !isFire)
		{
			SceneManager::Instantiate<Pollen>(enums::eLayer::Enemy, math::Vector2(220, 0), L"boomerang");
			isFire = true;
		}

		if (mMainAnimator->GetCurAnim()->IsComplete())
		{
			mbFiringPollen = false;
			isFire = false;
			fpStartTime = -1;
			canAttack = false;
			prevAttackTime = Time::GetTime();
		}
	}
	void CagneyCarnation_Boss::VineStab()
	{
		srand((unsigned int)(GetHP() + Time::GetTime() + Time::GetDeltaTime()));
		if(vineStabT == -1)
			vineStabT = (rand() % 3);

		if (vineStabT == 0)			// 1, 3
		{
			mVineStabAnimatorOne->SetOffset(math::Vector2(-850, 10));
			mVineStabAnimatorTwo->SetOffset(math::Vector2(-350, 10));
			mVineStabSensorOne->SetOffset(math::Vector2(-850, -10));
			mVineStabSensorTwo->SetOffset(math::Vector2(-350, -10));
		}
		else if (vineStabT == 1)	// 1, 2
		{
			mVineStabAnimatorOne->SetOffset(math::Vector2(-850, 10));
			mVineStabAnimatorTwo->SetOffset(math::Vector2(-600, 10));
			mVineStabSensorOne->SetOffset(math::Vector2(-850, -10));
			mVineStabSensorTwo->SetOffset(math::Vector2(-600, -10));
		}
		else						// 2, 3
		{	
			mVineStabAnimatorOne->SetOffset(math::Vector2(-600, 10));
			mVineStabAnimatorTwo->SetOffset(math::Vector2(-350, 10));
			mVineStabSensorOne->SetOffset(math::Vector2(-600, -10));
			mVineStabSensorTwo->SetOffset(math::Vector2(-350, -10));
		}

		if ((fabs(vsStartTime - Time::GetTime()) > 1.f)
			&& mVineStabAnimatorOne->GetCurAnim() != mVineStabAnimatorOne->GetAnim(L"Vine_stab_end"))
		{
			mVineStabSensorOne->SetActive(true);
			mVineStabSensorTwo->SetActive(true);
		}

		if (mVineStabAnimatorOne->GetCurAnim() == mVineStabAnimatorOne->GetAnim(L"Vine_stab_end") 
			&& mVineStabAnimatorOne->GetCurAnim()->IsComplete())
		{
			mbVineStab = false;
			vineStabT = -1;
			vsStartTime = -1;
			canAttack = false;
			prevAttackTime = Time::GetTime();

			mVineStabSensorOne->SetActive(false);
			mVineStabSensorTwo->SetActive(false);
			mVineStabAnimatorOne->DisableAnim();
			mVineStabAnimatorTwo->DisableAnim();
		}
		else if (mVineStabAnimatorOne->GetCurAnim() == mVineStabAnimatorOne->GetAnim(L"Vine_stab_start")
			&& mVineStabAnimatorOne->GetCurAnim()->IsComplete())
		{
			mVineStabAnimatorOne->PlayAnim(L"Vine_stab_end");
			mVineStabAnimatorTwo->PlayAnim(L"Vine_stab_end");

			mVineStabSensorOne->SetActive(false);
			mVineStabSensorTwo->SetActive(false);
		}
		else if(mVineStabAnimatorOne->GetCurAnim() != mVineStabAnimatorOne->GetAnim(L"Vine_stab_end"))
		{
			mVineStabAnimatorOne->PlayAnim(L"Vine_stab_start");
			mVineStabAnimatorTwo->PlayAnim(L"Vine_stab_start");
		}
	}

	void CagneyCarnation_Boss::TransitionToPh2()
	{
		mMainAnimator->PlayAnim(L"Carnation_Final_intro");

		if(fabs(transitionStartTime - Time::GetTime()) > 1.7f)
			mVineIntroAnimator->PlayAnim(L"Vine_intro");

		if (fabs(transitionStartTime - Time::GetTime()) > 2.2f)
			mVineFloorSensor->SetActive(true);

		if (mMainAnimator->GetCurAnim()->IsComplete())
		{
			SetState(BossPhase_state::phase2);
		}
	}
}