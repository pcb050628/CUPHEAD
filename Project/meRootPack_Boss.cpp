#include "meRootPack_Boss.h"
#include "meResourceManager.h"
#include "meSceneManager.h"
#include "meDust.h"
#include "meTear.h"
#include "meCarrotMissile.h"

namespace me
{
	RootPack_Boss::RootPack_Boss(const std::wstring& name) : Boss(name)
		, mTransform(nullptr)
		, mMainCollider(nullptr)
		, mMainAnimator(nullptr)
		, canAttack(true)
		, prevAttackTime(-1)
		, potatoShootCount(0)
		, potatoCanShoot(false)
		, prevShootTime(-1)
		, prevStartTime(-1)
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

		SetHP(1300); // 1300

		mTransform = GetComponent<Transform>();

		mMainCollider = AddComponent<BoxCollider>(enums::eComponentType::Collider);
		mMainCollider->SetSize(math::Vector2(300, 400));
		mMainCollider->SetOffset(math::Vector2(0, 60));

		mMainAnimator = AddComponent<Animator>(enums::eComponentType::Animator);
		mMainAnimator->SetFlashingDuration(0.01f);

		//potato anim
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"potato_anim_intro", L"..\\content\\Scene\\BossFight\\The Root Pack\\potato\\intro\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"potato_anim_shoot", L"..\\content\\Scene\\BossFight\\The Root Pack\\potato\\shoot\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"potato_anim_death", L"..\\content\\Scene\\BossFight\\The Root Pack\\potato\\death\\"));
		mMainAnimator->GetAnim(L"potato_anim_intro")->SetLoop(false);
		mMainAnimator->GetAnim(L"potato_anim_shoot")->SetDuration(0.07f);

		//onion anim
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"onion_anim_intro", L"..\\content\\Scene\\BossFight\\The Root Pack\\onion\\Body\\intro\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"onion_anim_idle", L"..\\content\\Scene\\BossFight\\The Root Pack\\onion\\Body\\idle\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"onion_anim_death", L"..\\content\\Scene\\BossFight\\The Root Pack\\onion\\Body\\death\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"onion_anim_cry_start", L"..\\content\\Scene\\BossFight\\The Root Pack\\onion\\Body\\cry\\start\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"onion_anim_cry_loop", L"..\\content\\Scene\\BossFight\\The Root Pack\\onion\\Body\\cry\\loop\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"onion_anim_cry_end", L"..\\content\\Scene\\BossFight\\The Root Pack\\onion\\Body\\cry\\end\\"));
		mMainAnimator->GetAnim(L"onion_anim_intro")->SetLoop(false);
		mMainAnimator->GetAnim(L"onion_anim_cry_start")->SetOffset(math::Vector2(0, -50));
		mMainAnimator->GetAnim(L"onion_anim_cry_end")->SetLoop(false);
		mMainAnimator->GetAnim(L"onion_anim_cry_loop")->SetOffset(math::Vector2(0, -50));

		//carrot anim
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"carrot_anim_intro", L"..\\content\\Scene\\BossFight\\The Root Pack\\carrot\\intro\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"carrot_anim_death", L"..\\content\\Scene\\BossFight\\The Root Pack\\carrot\\death\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"carrot_anim_attack", L"..\\content\\Scene\\BossFight\\The Root Pack\\carrot\\attack\\idle\\"));
		mMainAnimator->GetAnim(L"carrot_anim_intro")->SetLoop(false);
		mMainAnimator->GetAnim(L"carrot_anim_attack")->SetDuration(0.07f);
	}
	void RootPack_Boss::Update()
	{
		Boss::Update();
	}
	void RootPack_Boss::Render(HDC hdc)
	{
		Boss::Render(hdc);

		if (GetIsHIt())
		{
			SetIsHit(false);
			mMainAnimator->FlashingStart();
		}
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
		{
			if (prevShootTime == -1)
				prevShootTime = Time::GetTime() - 0.7f;

			PotatoShoot();
		}
	}
	void RootPack_Boss::Phase2()
	{
		if (GetHP() <= 475)
		{
			OnionOutro();
		}
		else if (canAttack)
		{
			OnionCry();
		}
		else
		{
			if (fabs(prevAttackTime - Time::GetTime()) > 1.f)
			{
				mMainAnimator->PlayAnim(L"onion_anim_cry_start");
				canAttack = true;
			}
			else
			{
				mMainAnimator->PlayAnim(L"onion_anim_idle");
			}
		}
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
		mMainAnimator->PlayAnim(L"carrot_anim_death");
	}

	void RootPack_Boss::PotatoIntro()
	{
		mMainAnimator->PlayAnim(L"potato_anim_intro");

		if (mMainAnimator->GetCurAnim()->IsComplete())
			SetState(BossPhase_state::phase1);
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

	void RootPack_Boss::OnionIntro()
	{
		mMainAnimator->PlayAnim(L"onion_anim_intro");
		
		mTransform->SetPos(math::Vector2());

		if (50 < mMainAnimator->GetOffset().y)
		{
			mMainAnimator->SetOffset(mMainAnimator->GetOffset() + math::Vector2(0, -2000 * Time::GetDeltaTime()));
		}

		if (mMainAnimator->GetCurAnim()->IsComplete())
		{
			SetState(BossPhase_state::phase2);
			CheckOne = false;
		}
	}
	void RootPack_Boss::OnionCry()
	{
		if (fabs(prevShootTime - Time::GetTime()) > 0.5f)
		{
			srand((unsigned int)(GetHP() + prevIdx + Time::GetTime() + Time::GetDeltaTime()));

			TearSpawn((unsigned int)(rand() % 10));
		}

		if (fabs(prevStartTime - Time::GetTime()) > 5)
		{
			canAttack = false;
			prevStartTime = Time::GetTime();
			mMainAnimator->PlayAnim(L"onion_anim_cry_end");
		}
		else
		{
			mMainAnimator->NextPlayAnim(L"onion_anim_cry_loop");
		}
	}
	void RootPack_Boss::OnionOutro()
	{
		if (!CheckOne)
		{
			if (phSavedTime == -1)
				phSavedTime = Time::GetTime();

			mMainAnimator->PlayAnim(L"onion_anim_death");

			mMainAnimator->SetOffset(mMainAnimator->GetOffset() + math::Vector2(0, 200 * Time::GetDeltaTime()));

			if (fabs(phSavedTime - Time::GetTime()) > 2.f)
			{
				CheckOne = true;
				phSavedTime = -1;
			}
		}
		else if (CheckOne)
		{
			CarrotIntro();
		}
	}

	void RootPack_Boss::CarrotIntro()
	{
		mMainAnimator->PlayAnim(L"carrot_anim_intro");

		mTransform->SetPos(math::Vector2());

		if (50 < mMainAnimator->GetOffset().y)
		{
			mMainAnimator->SetOffset(mMainAnimator->GetOffset() + math::Vector2(0, -2000 * Time::GetDeltaTime()));
		}

		if (mMainAnimator->GetCurAnim()->IsComplete())
		{
			SetState(BossPhase_state::phase3);
			CheckOne = false;
		}

	}
	void RootPack_Boss::CarrotAttack()
	{
		mMainAnimator->PlayAnim(L"carrot_anim_attack");

		if (fabs(prevShootTime - Time::GetTime()) > 2.5f)
		{
			srand((unsigned int)(GetHP() + prevIdx + Time::GetTime() + Time::GetDeltaTime()));

			MissileSpawn((unsigned int)(rand() % 10));
		}
	}


	void RootPack_Boss::DustSpawn()
	{
		SceneManager::Instantiate<Dust>(enums::eLayer::Bullet, mTransform->GetPos() + math::Vector2(-200, 200));
		potatoShootCount++;
	}
	void RootPack_Boss::TearSpawn(int idx)
	{
		SceneManager::Instantiate<Tear>(enums::eLayer::Bullet, math::Vector2(tearPosX[idx], -400));
		prevShootTime = Time::GetTime(); 
		prevIdx = idx;
	}
	void RootPack_Boss::MissileSpawn(int idx)
	{
		CarrotMissile* cm = SceneManager::Instantiate<CarrotMissile>(enums::eLayer::Bullet, math::Vector2(tearPosX[idx], -400));
		cm->SetTarget(SceneManager::GetCurScene()->GetGameObj(enums::eLayer::Player, L"CupHead_stage"));
		prevShootTime = Time::GetTime();
	}
}