#include "meGoopy_Le_Grande_Boss.h"
#include "meResourceManager.h"

namespace me
{
#define PunchMaxDist 400

	Goopy_Le_Grande_Boss::Goopy_Le_Grande_Boss(const std::wstring& name) : Boss(name)
		, mAnimator(nullptr)
		, mFlip(false)
		, mMainCollider(nullptr)
		, mPunchCollider(nullptr)
		, mSmashCollider(nullptr)
	{
	}
	Goopy_Le_Grande_Boss::~Goopy_Le_Grande_Boss()
	{
	}
	void Goopy_Le_Grande_Boss::Init()
	{
		Boss::Init();

		SetHP(1200);

		mMainCollider = AddComponent<BoxCollider>(L"Main");
		mMainCollider->SetSize(math::Vector2(200, 200));

		mPunchCollider = AddComponent<BoxCollider>(L"Punch");
		mPunchCollider->SetOffset(math::Vector2(-PunchMaxDist, -100));
		mPunchCollider->SetSize(math::Vector2(250, 250));

		mSmashCollider = AddComponent<BoxCollider>(L"Smash");

		//mMainCollider->SetActivate(false);
		mPunchCollider->SetActivate(false);
		mSmashCollider->SetActivate(false);

		mAnimator = AddComponent<Animator>(enums::eComponentType::Animator);

		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_intro", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Intro\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_air_down_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Air Down_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_air_down_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Air Down_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_air_up_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Air Up_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_air_up_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Air Up_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_jump_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Jump_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_jump_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Jump_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_punch_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Punch_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_punch_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Punch_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_transition_to_ph2_first", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Transition To Ph2_L\\First\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_transition_to_ph2_second", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Transition To Ph2_L\\Second\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_transition_to_ph2_third", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Transition To Ph2_L\\Third\\"));
		mAnimator->GetAnim(L"Goopy Le Grande_intro")->SetOffset(math::Vector2(-90, -90));
		mAnimator->GetAnim(L"Goopy Le Grande_punch_L")->SetOffset(math::Vector2(0, -10));
		mAnimator->GetAnim(L"Goopy Le Grande_intro")->SetLoop(false);
		mAnimator->GetAnim(L"Goopy Le Grande_transition_to_ph2_first")->SetLoop(false);
		mAnimator->GetAnim(L"Goopy Le Grande_transition_to_ph2_second")->SetLoop(false);
		mAnimator->GetAnim(L"Goopy Le Grande_transition_to_ph2_third")->SetLoop(false);
		mAnimator->PlayAnim(L"Goopy Le Grande_intro");
	}
	void Goopy_Le_Grande_Boss::Update()
	{
		Boss::Update();

		
	}
	void Goopy_Le_Grande_Boss::Render(HDC hdc)
	{
		Boss::Render(hdc);
	}

	void Goopy_Le_Grande_Boss::Intro()
	{
		mAnimator->PlayAnim(L"Goopy Le Grande_intro");
		if (mAnimator->GetCurAnim()->IsComplete())
			SetState(me::BossPhase_state::phase1);
	}

	void Goopy_Le_Grande_Boss::Phase1()
	{
	}
	void Goopy_Le_Grande_Boss::Phase2()
	{
	}
	void Goopy_Le_Grande_Boss::Phase3()
	{
	}
	void Goopy_Le_Grande_Boss::Death()
	{
	}

	void Goopy_Le_Grande_Boss::Jump()
	{
	}
	void Goopy_Le_Grande_Boss::Punch()
	{
	}
	void Goopy_Le_Grande_Boss::Smash()
	{
	}
}
