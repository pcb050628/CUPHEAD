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
		mAnimator->SetOffset(math::Vector2(-50, -50));
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
