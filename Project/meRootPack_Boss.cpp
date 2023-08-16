#include "meRootPack_Boss.h"
#include "meResourceManager.h"
#include "meSceneManager.h"
#include "meDust.h"
#include "meTear.h"
#include "meCarrotMissile.h"

namespace me
{
	RootPack_Boss::RootPack_Boss(const std::wstring& name) : Boss(name)
		, mMainCollider(nullptr)
		, mMainAnimator(nullptr)
		, canAttack(true)
		, prevAttackTime(NULL)
		, potatoShootCount(NULL)
		, potatoCanShoot(true)
		, prevShootTime(NULL)
		, CheckOne(false)
		, CheckTwo(false)
		, CheckThree(false)
		, phSavedTime(-1)
	{
	}
	RootPack_Boss::~RootPack_Boss()
	{
	}
	void RootPack_Boss::Init()
	{
		Boss::Init();

		SetHP(900); // 1300

		mMainCollider = AddComponent<CircleCollider>(enums::eComponentType::Collider);

		mMainAnimator = AddComponent<Animator>(enums::eComponentType::Animator);

		//potato anim
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"potato_anim_intro", L"..\\content\\Scene\\BossFight\\The Root Pack\\potato\\intro\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"potato_anim_shoot", L"..\\content\\Scene\\BossFight\\The Root Pack\\potato\\shoot\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"potato_anim_death", L"..\\content\\Scene\\BossFight\\The Root Pack\\potato\\death\\"));
		mMainAnimator->GetAnim(L"potato_anim_intro")->SetLoop(false);

		//onion anim
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"onion_anim_intro", L"..\\content\\Scene\\BossFight\\The Root Pack\\onion\\Body\\intro\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"onion_anim_idle", L"..\\content\\Scene\\BossFight\\The Root Pack\\onion\\Body\\idle\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"onion_anim_death", L"..\\content\\Scene\\BossFight\\The Root Pack\\onion\\Body\\death\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"onion_anim_cry_start", L"..\\content\\Scene\\BossFight\\The Root Pack\\onion\\Body\\cry\\start\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"onion_anim_cry_loop", L"..\\content\\Scene\\BossFight\\The Root Pack\\onion\\Body\\cry\\loop\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"onion_anim_cry_end", L"..\\content\\Scene\\BossFight\\The Root Pack\\onion\\Body\\cry\\end\\"));
		mMainAnimator->GetAnim(L"onion_anim_intro")->SetLoop(false);

		//carrot anim
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"carrot_anim_intro", L"..\\content\\Scene\\BossFight\\The Root Pack\\carrot\\intro\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"carrot_anim_death", L"..\\content\\Scene\\BossFight\\The Root Pack\\carrot\\death\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"carrot_anim_attack", L"..\\content\\Scene\\BossFight\\The Root Pack\\carrot\\attack\\idle\\"));
		mMainAnimator->GetAnim(L"carrot_anim_intro")->SetLoop(false);
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
		PotatoIntro();
	}
	void RootPack_Boss::Phase1()
	{
		if (GetHP() <= 900)
		{
			PotatoOutro();
		}
		else
			PotatoShoot();
	}
	void RootPack_Boss::Phase2()
	{
		if (GetHP() <= 475)
		{
			OnionOutro();
		}
		else
			OnionCry();
	}
	void RootPack_Boss::Phase3()
	{
		if (GetHP() <= 0)
		{
			SetState(BossPhase_state::death);
		}
		else
			CarrotAttack();
	}
	void RootPack_Boss::Death()
	{
		CarrotOutro();
	}

	void RootPack_Boss::PotatoIntro()
	{
		mMainAnimator->PlayAnim(L"potato_anim_intro");

		if (mMainAnimator->GetCurAnim()->IsComplete())
			SetState(BossPhase_state::phase1);
	}
	void RootPack_Boss::OnionIntro()
	{
		mMainAnimator->PlayAnim(L"onion_anim_intro");
		
		// 위치를 중간으로 옮기기
		// 애니메이션 오프셋으로 아래에서 올라오는 연출 만들기

		if (mMainAnimator->GetCurAnim()->IsComplete())
		{
			SetState(BossPhase_state::phase2);
			CheckOne = false;
		}
	}
	void RootPack_Boss::CarrotIntro()
	{
	}

	void RootPack_Boss::PotatoShoot()
	{
		mMainAnimator->PlayAnim(L"potato_anim_shoot");

		if (potatoCanShoot)
		{
			DustSpawn();
			prevShootTime = Time::GetTime();
			potatoCanShoot = false;
		}
		else if (fabs(prevShootTime - Time::GetTime()) > 1.5f)
		{
			potatoCanShoot = true;
		}
	}
	void RootPack_Boss::OnionCry()
	{
	}
	void RootPack_Boss::CarrotAttack()
	{
	}

	void RootPack_Boss::PotatoOutro()
	{
		if (!CheckOne)
		{
			if (phSavedTime == -1)
				phSavedTime = Time::GetTime();

			mMainAnimator->PlayAnim(L"potato_anim_death");

			mMainAnimator->SetOffset(mMainAnimator->GetOffset() + math::Vector2(0, 200 * Time::GetDeltaTime()));

			if (fabs(phSavedTime - Time::GetTime()) > 2.f)
			{
				CheckOne = true;
				phSavedTime = -1;
			}
		}
		else if (CheckOne)
		{
			OnionIntro();
		}
	}
	void RootPack_Boss::OnionOutro()
	{
	}
	void RootPack_Boss::CarrotOutro()
	{
	}

	void RootPack_Boss::DustSpawn()
	{
		SceneManager::Instantiate<Dust>(enums::eLayer::Bullet, math::Vector2());
		potatoShootCount++;
	}
}