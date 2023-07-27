#include "meGoopy_Le_Grande_Boss.h"
#include "meResourceManager.h"

namespace me
{
	Goopy_Le_Grande_Boss::Goopy_Le_Grande_Boss(const std::wstring& name) : Boss(name)
		, mAnimator(nullptr)
	{
	}
	Goopy_Le_Grande_Boss::~Goopy_Le_Grande_Boss()
	{
	}
	void Goopy_Le_Grande_Boss::Init()
	{
		Boss::Init();

		SetHP(1200);

		AddComponent<BoxCollider>(enums::eComponentType::Collider);

		mAnimator = AddComponent<Animator>(enums::eComponentType::Animator);

		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_intro", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Intro\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_air_down_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Air Down_L\\"));
		//mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_air_down_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Air Down_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_air_up_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Air Up_L\\"));
		//mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_air_up_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Air Up_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_jump_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Jump_L\\"));
		//mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_jump_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Jump_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_punch_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Punch_L\\"));
		//mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_punch_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Punch_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_transition_to_ph2", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Transition To Ph2_L\\"));
		mAnimator->GetAnim(L"Goopy Le Grande_intro")->SetOffset(math::Vector2(-75, -75));
		mAnimator->GetAnim(L"Goopy Le Grande_intro")->SetLoop(false);
		mAnimator->GetAnim(L"Goopy Le Grande_punch_L")->SetLoop(false);
		mAnimator->PlayAnim(L"Goopy Le Grande_punch_L");
		//mAnimator->NextPlayAnim(L"Goopy Le Grande_punch_L");
	}
	void Goopy_Le_Grande_Boss::Update()
	{
		Boss::Update();
	}
	void Goopy_Le_Grande_Boss::Render(HDC hdc)
	{
		Boss::Render(hdc);
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
