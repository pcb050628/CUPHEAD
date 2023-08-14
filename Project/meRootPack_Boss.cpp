#include "meRootPack_Boss.h"
#include "meResourceManager.h"

namespace me
{
	RootPack_Boss::RootPack_Boss(const std::wstring& name) : Boss(name)
	{
	}
	RootPack_Boss::~RootPack_Boss()
	{
	}
	void RootPack_Boss::Init()
	{
		Boss::Init();

		mMainCollider = AddComponent<CircleCollider>(enums::eComponentType::Collider);

		mMainAnimator = AddComponent<Animator>(enums::eComponentType::Animator);

		//potato anim
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"potato_anim_intro", L"..\\content\\Scene\\BossFight\\The Root Pack\\potato\\intro\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"potato_anim_shoot", L"..\\content\\Scene\\BossFight\\The Root Pack\\potato\\shoot\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"potato_anim_death", L"..\\content\\Scene\\BossFight\\The Root Pack\\potato\\death\\"));

		//onion anim
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"onion_anim_intro", L"..\\content\\Scene\\BossFight\\The Root Pack\\onion\\Body\\intro\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"onion_anim_idle", L"..\\content\\Scene\\BossFight\\The Root Pack\\onion\\Body\\idle\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"onion_anim_death", L"..\\content\\Scene\\BossFight\\The Root Pack\\onion\\Body\\death\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"onion_anim_cry_start", L"..\\content\\Scene\\BossFight\\The Root Pack\\onion\\Body\\cry\\start\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"onion_anim_cry_loop", L"..\\content\\Scene\\BossFight\\The Root Pack\\onion\\Body\\cry\\loop\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"onion_anim_cry_end", L"..\\content\\Scene\\BossFight\\The Root Pack\\onion\\Body\\cry\\end\\"));

		//carrot anim
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"carrot_anim_intro", L"..\\content\\Scene\\BossFight\\The Root Pack\\carrot\\intor\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"carrot_anim_death", L"..\\content\\Scene\\BossFight\\The Root Pack\\carrot\\death\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"carrot_anim_attack", L"..\\content\\Scene\\BossFight\\The Root Pack\\carrot\\attack\\idle\\"));
	}
	void RootPack_Boss::Update()
	{
		Boss::Update();
	}
	void RootPack_Boss::Render(HDC hdc)
	{
		Boss::Render(hdc);
	}

	void RootPack_Boss::OnCollisionEnter(Collider* other)
	{
	}
	void RootPack_Boss::OnCollisionStay(Collider* other)
	{
	}
	void RootPack_Boss::OnCollisionExit(Collider* other)
	{
	}

	void RootPack_Boss::Intro()
	{
	}
	void RootPack_Boss::Phase1()
	{
	}
	void RootPack_Boss::Phase2()
	{
	}
	void RootPack_Boss::Phase3()
	{
	}

	void RootPack_Boss::Death()
	{
	}
}