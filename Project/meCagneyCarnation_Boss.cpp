#include "meCagneyCarnation_Boss.h"
#include "meResourceManager.h"
#include "meSceneManager.h"
#include "meBoomerang.h"
#include "meBullet.h"

namespace me
{
	CagneyCarnation_Boss::CagneyCarnation_Boss(const std::wstring& name) : Boss(name)
		, mTransform(nullptr), mMainSensor(nullptr), mMainAnimator(nullptr)
		, mFASensor(nullptr)
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
		mMainAnimator->PlayAnim(L"Carnation_idle");
		// 랜덤으로 패턴 실행하기 / 2 페이즈도 똑같이 랜덤으로 진행하기 
		// 랜덤 함수는 체력 + 시간 + deltaTime 으로 시드값 주기 //srand((unsigned int)(GetHP() + prevIdx + Time::GetTime() + Time::GetDeltaTime())); //rand();
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
	}
	void CagneyCarnation_Boss::FaceAttack()
	{
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