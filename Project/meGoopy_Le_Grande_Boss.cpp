#include "meGoopy_Le_Grande_Boss.h"
#include "meResourceManager.h"

namespace me
{
	Goopy_Le_Grande_Boss::Goopy_Le_Grande_Boss(const std::wstring& name) : Boss(name)
		, HP(500.f)
		, mAnimator(nullptr)
	{
	}
	Goopy_Le_Grande_Boss::~Goopy_Le_Grande_Boss()
	{
	}
	void Goopy_Le_Grande_Boss::Init()
	{
		Boss::Init();

		AddComponent<BoxCollider>(enums::eComponentType::Collider);

		mAnimator = AddComponent<Animator>(enums::eComponentType::Animator);

		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"Goopy Le Grande_intro", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Punch_L\\"));
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
}
