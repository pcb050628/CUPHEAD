#include "meCagneyCarnation_Boss.h"
#include "meResourceManager.h"
#include "meSceneManager.h"
#include "meBoomerang.h"

namespace me
{
	CagneyCarnation_Boss::CagneyCarnation_Boss(const std::wstring& name) : Boss(name)
		, mTransform(nullptr), mMainCollider(nullptr), mMainAnimator(nullptr)
		, mFASensor(nullptr)
		, mVineIntroAnimator(nullptr), mVineStabAnimator(nullptr)
	{
	}
	CagneyCarnation_Boss::~CagneyCarnation_Boss()
	{
		SceneManager::Destroy(mFASensor);
		mFASensor = nullptr;
	}

	void CagneyCarnation_Boss::Init()
	{
		Boss::Init();

		mTransform = GetComponent<Transform>();

		mMainCollider = AddComponent<BoxCollider>(enums::eComponentType::Collider);
		mMainAnimator = AddComponent<Animator>(L"MainAnimator");
		mVineIntroAnimator = AddComponent<Animator>(L"VineIntroAnimator");
		mVineStabAnimator = AddComponent<Animator>(L"VineStabAnimator");
		mFASensor = SceneManager::Instantiate<Sensor>(L"carnation_stage", enums::eLayer::Sensor, mTransform->GetPos(), L"FASensor");

		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Carnation_intro", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Intro\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Carnation_idle", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Idle\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Carnation_FA_high", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Face Attack\\High\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Carnation_FA_low", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Face Attack\\Low\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Carnation_creat_boomerang", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Create Object\\"));

		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Carnation_Final_intro", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Final Form\\Intro\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Carnation_Final_idle", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Final Form\\Idle\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Carnation_Final_firing", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Final Form\\Firing Pollen\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Carnation_death", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Death\\"));

		mVineIntroAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Vine_intro", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Final Form\\Vines\\main\\"));
		mVineStabAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Vine_stab", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Final Form\\Vines\\platform\\"));

		mFASensor->SetTargetType(enums::eGameObjType::player);
		mFASensor->SetActive(false);
		//mFASensor->SetColliderSize();
		//mFASensor->SetOffset();
	}
	void CagneyCarnation_Boss::Update()
	{
		Boss::Update();
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
	}
	void CagneyCarnation_Boss::Phase1()
	{
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
}