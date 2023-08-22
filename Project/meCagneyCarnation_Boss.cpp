#include "meCagneyCarnation_Boss.h"
#include "meResourceManager.h"
#include "meSceneManager.h"
#include "meBoomerang.h"
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
		// vines
		, mVineIntroAnimator(nullptr), mVineStabAnimator(nullptr)			
	{
	}
	CagneyCarnation_Boss::~CagneyCarnation_Boss()
	{
		SceneManager::Destroy(mMainSensor);
		SceneManager::Destroy(mHitSensor);
		SceneManager::Destroy(mFASensor);
		mMainSensor = nullptr;
		mFASensor = nullptr;
	}

	void CagneyCarnation_Boss::Init()
	{
		Boss::Init();

		SetHP(1500);

		mTransform = GetComponent<Transform>();

		mMainSensor = SceneManager::Instantiate<Sensor>(L"carnation_stage", enums::eLayer::Sensor, mTransform->GetPos(), L"MainSensor");
		mMainSensor->SetOwner(this);
		mHitSensor = SceneManager::Instantiate<Sensor>(L"carnation_stage", enums::eLayer::Sensor, mTransform->GetPos(), L"HitSensor");
		mHitSensor->SetOwner(this);
		mMainAnimator = AddComponent<Animator>(L"MainAnimator");
		mVineIntroAnimator = AddComponent<Animator>(L"VineIntroAnimator");
		mVineStabAnimator = AddComponent<Animator>(L"VineStabAnimator");
		mFASensor = SceneManager::Instantiate<Sensor>(L"carnation_stage", enums::eLayer::Sensor, mTransform->GetPos(), L"FASensor");
		mFASensor->SetOwner(this);

		mMainSensor->SetColliderSize(math::Vector2(200, 600));
		mMainSensor->AddTargetType(enums::eGameObjType::player);

		mHitSensor->SetOffset(math::Vector2(0, -150));
		mHitSensor->SetColliderSize(math::Vector2(200, 200));
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

		mVineIntroAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Vine_intro", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Final Form\\Vines\\main\\"));
		mVineStabAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Vine_stab", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Final Form\\Vines\\platform\\"));

		mFASensor->AddTargetType(enums::eGameObjType::player);
		mFASensor->SetActive(false);
		mFASensor->SetColliderSize(math::Vector2(100, 100));
		mFASensor->SetOffset(math::Vector2(0, 100));
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
		// 랜덤으로 패턴 실행하기 / 2 페이즈도 똑같이 랜덤으로 진행하기 
		// 랜덤 함수는 체력 + 시간 + deltaTime 으로 시드값 주기 // //;

		srand((unsigned int)(GetHP() +  Time::GetTime() + Time::GetDeltaTime()));

		if (canAttack)
		{
			if (!mbCreateBoomerang && !mbFaceHighAttack && !mbFaceLowAttack)
			{
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
	}
	void CagneyCarnation_Boss::Phase3()
	{
	}
	void CagneyCarnation_Boss::Death()
	{
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

		if (fabs(faStartTime - Time::GetTime()) > 1.3f)
		{
			if (mHitSensor->GetOffset().x < 0)
				mHitSensor->SetOffset(mHitSensor->GetOffset() + math::Vector2(1000 * Time::GetDeltaTime(), 0));

			if (mHitSensor->GetColliderSize().x >= 200)
				mHitSensor->SetColliderSize(mHitSensor->GetColliderSize() + math::Vector2(-1500 * Time::GetDeltaTime(), 0));

			if (mHitSensor->GetOffset().x >= 0 && mHitSensor->GetColliderSize().x <= 200)
			{
				mHitSensor->SetOffset(math::Vector2(0, -150));
				mHitSensor->SetColliderSize(math::Vector2(200, 200));

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
		if(mHitSensor->GetOffset().y == -150)
			mHitSensor->SetOffset(mHitSensor->GetOffset() + math::Vector2(0, 300));

		if (fabs(faStartTime - Time::GetTime()) > 1.1f)
		{
			if (mHitSensor->GetOffset().x < 0)
				mHitSensor->SetOffset(mHitSensor->GetOffset() + math::Vector2(1100 * Time::GetDeltaTime(), 0));

			if (mHitSensor->GetColliderSize().x >= 200)
				mHitSensor->SetColliderSize(mHitSensor->GetColliderSize() + math::Vector2(-1600 * Time::GetDeltaTime(), 0));

			if (mHitSensor->GetOffset().x >= 0 && mHitSensor->GetColliderSize().x <= 200)
			{
				mHitSensor->SetOffset(math::Vector2(0, -150));
				mHitSensor->SetColliderSize(math::Vector2(200, 200));

				mbFaceLowAttack = false;
				faStartTime = -1;
				canAttack = false;
				prevAttackTime = Time::GetTime();
			}
		}
		else if (fabs(faStartTime - Time::GetTime()) > 0.3f)
		{
			if (mHitSensor->GetOffset().x > -500)
				mHitSensor->SetOffset(mHitSensor->GetOffset() + math::Vector2(-1100 * Time::GetDeltaTime(), 0));

			if (mHitSensor->GetColliderSize().x < 900)
				mHitSensor->SetColliderSize(mHitSensor->GetColliderSize() + math::Vector2(1600 * Time::GetDeltaTime(), 0));
		}
	}

	void CagneyCarnation_Boss::FiringPollen()
	{
	}
	void CagneyCarnation_Boss::VineStab()
	{
	}

	void CagneyCarnation_Boss::TransitionToPh2()
	{
	}
}