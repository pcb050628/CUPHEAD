#include "meGoopy_Le_Grande_Boss.h"
#include "meSceneManager.h"
#include "meBossFightScene.h"
#include "meResourceManager.h"
#include "meColliderManager.h"
#include "meQuestionMark.h"

namespace me
{
#define PunchMaxDist 400

	Goopy_Le_Grande_Boss::Goopy_Le_Grande_Boss(const std::wstring& name) : Boss(name)
		, mMainAnimator(nullptr)
		, mFlip(true)
		, mMainCollider(nullptr)
		, mPunchCollider(nullptr)
		, attackTime(0)
		, smallPunchHoldingTime(0.45f)
		, bigPunchHoldingTime(0.9f)
		, attackCooldown(5)
		, mSmashCollider(nullptr)
		, mIsJumping(false)
		, mJumpMaxHeight(450)
		, punchStartTime(-1)
		, back(true)
		, stretch(false)
		, startTimePh(-1)
	{
	}
	Goopy_Le_Grande_Boss::~Goopy_Le_Grande_Boss()
	{
		//sensor release
		SceneManager::Destroy(mSmashCollider);
		SceneManager::Destroy(mPunchCollider);
		SceneManager::Destroy(mPlayerSensor);

		mSmashCollider	= nullptr;
		mPunchCollider	= nullptr;
		mPlayerSensor	= nullptr;

		//sound release
		stretchSound	= nullptr;
		smallJumpSound	= nullptr;
		smallLandSound	= nullptr;
		bigJumpSound	= nullptr;
		bigLandSound	= nullptr;
	}
	void Goopy_Le_Grande_Boss::Init()
	{
		Boss::Init();

		SetHP(1400);

		mTransform = GetComponent<Transform>();

		mRigidbody = AddComponent<Rigidbody>(enums::eComponentType::Rigidbody);
		mRigidbody->SetGround(true);

		mMainCollider = AddComponent<CircleCollider>(L"Main");
		mMainCollider->SetRadius(100);

		mPunchCollider = SceneManager::Instantiate<Sensor>(L"slime_stage", enums::eLayer::Sensor, mTransform->GetPos(), L"Punch");
		mPunchCollider->SetOwner(this);
		mPunchCollider->SetTargetType(enums::eGameObjType::player);
		mPunchCollider->SetColliderSize(math::Vector2(250, 250));
		mPunchCollider->SetOffset(math::Vector2(0, -130));
		
		mPlayerSensor = SceneManager::Instantiate<Sensor>(L"slime_stage", enums::eLayer::Sensor, mTransform->GetPos(), L"enemySensor");
		mPlayerSensor->SetOwner(this);
		mPlayerSensor->SetTargetType(enums::eGameObjType::player);
		mPlayerSensor->SetOffset(math::Vector2(-180, 0));
		mPlayerSensor->SetColliderSize(math::Vector2(400, 100));

		mSmashCollider = SceneManager::Instantiate<Sensor>(L"slime_stage", enums::eLayer::Sensor, mTransform->GetPos(), L"Smash");

		mPunchCollider->SetActive(false);
		mSmashCollider->SetActive(false);

		mMainAnimator = AddComponent<Animator>(enums::eComponentType::Animator);
		mMainAnimator->SetFlashingDuration(0.01f);

		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_intro", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 1\\Intro\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_air_down_L", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 1\\Air Down_L\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_air_down_R", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 1\\Air Down_R\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_air_up_L", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 1\\Air Up_L\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_air_up_R", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 1\\Air Up_R\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_jump_L", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 1\\Jump_L\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_jump_R", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 1\\Jump_R\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_punch_back_L", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 1\\Punch_L\\back\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_punch_back_R", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 1\\Punch_R\\back\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_punch_stretch_L", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 1\\Punch_L\\stretch\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_punch_stretch_R", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 1\\Punch_R\\stretch\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_punch_end_L", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 1\\Punch_L\\end\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_punch_end_R", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 1\\Punch_R\\end\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_transition_to_ph2_first", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 1\\Transition To Ph2_L\\First\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_transition_to_ph2_second", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 1\\Transition To Ph2_L\\Second\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_transition_to_ph2_third", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 1\\Transition To Ph2_L\\Third\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_air_down_L", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 2\\Air Down_L\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_air_down_R", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 2\\Air Down_R\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_air_up_L", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 2\\Air Up_L\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_air_up_R", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 2\\Air Up_R\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_jump_L", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 2\\Jump_L\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_jump_R", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 2\\Jump_R\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_punch_back_L", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 2\\Punch_L\\back\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_punch_back_R", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 2\\Punch_R\\back\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_punch_stretch_L", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 2\\Punch_L\\stretch\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_punch_stretch_R", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 2\\Punch_R\\stretch\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_punch_end_L", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 2\\Punch_L\\end\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_punch_end_R", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 2\\Punch_R\\end\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_death", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 2\\Death\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_tomb_move_L", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 3\\Left\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_tomb_move_R", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 3\\Right\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_tomb_smash", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 3\\Smash\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_tomb_death", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 3\\Death\\"));

		mPh3IntroAnimator = AddComponent<Animator>(L"ph3Intro");
		mPh3IntroAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_tomb_intro", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 3\\Intro\\"));

		mPh2DustAnimator = AddComponent<Animator>(L"dustAnimator");
		mPh2DustAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_ph2_dust", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 2\\Dust\\A\\"));
		mPh2DustAnimator->GetAnim(L"Goopy Le Grande_ph2_dust")->SetDuration(0.05f);
		mPh2DustAnimator->GetAnim(L"Goopy Le Grande_ph2_dust")->SetLoop(false);
		mPh2DustAnimator->SetOffset(math::Vector2(0, 100));

		mMainAnimator->GetAnim(L"Goopy Le Grande_intro")->SetOffset(math::Vector2(-90, -90));

		mMainAnimator->GetAnim(L"Goopy Le Grande_small_punch_back_L")->SetOffset(math::Vector2(-10, 0));
		mMainAnimator->GetAnim(L"Goopy Le Grande_small_punch_back_R")->SetOffset(math::Vector2(10, 0));
		mMainAnimator->GetAnim(L"Goopy Le Grande_small_punch_stretch_L")->SetOffset(math::Vector2(-10, 0));
		mMainAnimator->GetAnim(L"Goopy Le Grande_small_punch_stretch_R")->SetOffset(math::Vector2(10, 0));
		mMainAnimator->GetAnim(L"Goopy Le Grande_small_punch_end_L")->SetOffset(math::Vector2(-10, 0));
		mMainAnimator->GetAnim(L"Goopy Le Grande_small_punch_end_R")->SetOffset(math::Vector2(10, 0));
		mMainAnimator->GetAnim(L"Goopy Le Grande_small_punch_back_L")->SetLoop(false);
		mMainAnimator->GetAnim(L"Goopy Le Grande_small_punch_back_R")->SetLoop(false);
		mMainAnimator->GetAnim(L"Goopy Le Grande_small_punch_stretch_L")->SetLoop(false);
		mMainAnimator->GetAnim(L"Goopy Le Grande_small_punch_stretch_R")->SetLoop(false);
		mMainAnimator->GetAnim(L"Goopy Le Grande_small_punch_end_L")->SetLoop(false);
		mMainAnimator->GetAnim(L"Goopy Le Grande_small_punch_end_R")->SetLoop(false);

		mMainAnimator->GetAnim(L"Goopy Le Grande_big_air_down_L")->SetOffset(math::Vector2(0, -30));
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_air_down_R")->SetOffset(math::Vector2(0, -30));
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_air_up_L")->SetOffset(math::Vector2(0, -30));
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_air_up_R")->SetOffset(math::Vector2(0, -30));
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_jump_L")->SetOffset(math::Vector2(0, -30));
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_jump_R")->SetOffset(math::Vector2(0, -30));

		mMainAnimator->GetAnim(L"Goopy Le Grande_big_punch_back_L")->SetOffset(math::Vector2(-130, -20));
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_punch_back_R")->SetOffset(math::Vector2(130, -20));
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_punch_stretch_L")->SetOffset(math::Vector2(-130, -20));
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_punch_stretch_R")->SetOffset(math::Vector2(130, -20));
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_punch_end_L")->SetOffset(math::Vector2(-130, -20));
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_punch_end_R")->SetOffset(math::Vector2(130, -20));
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_punch_back_L")->SetLoop(false);
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_punch_back_R")->SetLoop(false);
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_punch_stretch_L")->SetLoop(false);
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_punch_stretch_R")->SetLoop(false);
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_punch_end_L")->SetLoop(false);
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_punch_end_R")->SetLoop(false);
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_punch_back_L")->SetDuration(0.05f);
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_punch_back_R")->SetDuration(0.05f);
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_punch_stretch_L")->SetDuration(0.05f);
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_punch_stretch_R")->SetDuration(0.05f);
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_punch_end_L")->SetDuration(0.05f);
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_punch_end_R")->SetDuration(0.05f);

		mMainAnimator->GetAnim(L"Goopy Le Grande_big_jump_L")->SetOffset(math::Vector2(0, -20));
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_jump_R")->SetOffset(math::Vector2(0, -20));
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_air_up_L")->SetOffset(math::Vector2(0, -20));
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_air_up_R")->SetOffset(math::Vector2(0, -20));
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_air_down_R")->SetOffset(math::Vector2(0, -20));
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_air_down_R")->SetOffset(math::Vector2(0, -20));

		mMainAnimator->GetAnim(L"Goopy Le Grande_intro")->SetLoop(false);

		mMainAnimator->GetAnim(L"Goopy Le Grande_transition_to_ph2_first")->SetLoop(false);
		mMainAnimator->GetAnim(L"Goopy Le Grande_transition_to_ph2_third")->SetLoop(false);

		mMainAnimator->GetAnim(L"Goopy Le Grande_small_jump_L")->SetLoop(false);
		mMainAnimator->GetAnim(L"Goopy Le Grande_small_jump_R")->SetLoop(false);

		mMainAnimator->GetAnim(L"Goopy Le Grande_big_jump_L")->SetLoop(false);
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_jump_R")->SetLoop(false);

		mMainAnimator->GetAnim(L"Goopy Le Grande_big_death")->SetOffset(math::Vector2(0, -50));

		mMainAnimator->GetAnim(L"Goopy Le Grande_tomb_smash")->SetLoop(false);

		mPh3IntroAnimator->GetAnim(L"Goopy Le Grande_tomb_intro")->SetLoop(false);
		mPh3IntroAnimator->GetAnim(L"Goopy Le Grande_tomb_intro")->SetDuration(0.1f);
		mPh3IntroAnimator->GetAnim(L"Goopy Le Grande_tomb_intro")->SetOffset(math::Vector2(0, -900));

		smallJumpSound = ResourceManager::Load<Sound>(L"slime_small_jump", L"..\\content\\Sound\\AudioClip\\BossFightScene\\Goopy Le Grande\\sfx_slime_small_jump_02.wav");
		smallLandSound = ResourceManager::Load<Sound>(L"slime_small_land", L"..\\content\\Sound\\AudioClip\\BossFightScene\\Goopy Le Grande\\sfx_slime_small_land_01.wav");
		bigJumpSound = ResourceManager::Load<Sound>(L"slime_big_jump", L"..\\content\\Sound\\AudioClip\\BossFightScene\\Goopy Le Grande\\sfx_slime_big_jump_03.wav");
		bigLandSound = ResourceManager::Load<Sound>(L"slime_big_jump", L"..\\content\\Sound\\AudioClip\\BossFightScene\\Goopy Le Grande\\sfx_slime_big_land_03.wav");
	}
	void Goopy_Le_Grande_Boss::Update()
	{
		Boss::Update();

		if (mPunchCollider->Sensed())
		{
			dynamic_cast<Player_stage*>(mPunchCollider->GetSensedObj())->GetHit();
		}

		if (GetIsHIt())
		{
			SetIsHit(false);
			mMainAnimator->FlashingStart();
		}

		/*if (dynamic_cast<BossFightScene*>(SceneManager::GetCurScene())->gameover)
		{
			mPunchCollider->SetTargetType(enums::eGameObjType::none);
			mPunchCollider->SetActive(false);

			mPlayerSensor->SetTargetType(enums::eGameObjType::none);
			mPlayerSensor->SetActive(false);

			mSmashCollider->SetTargetType(enums::eGameObjType::none);
			mSmashCollider->SetActive(false);
		}*/
	}
	void Goopy_Le_Grande_Boss::Render(HDC hdc)
	{
		Boss::Render(hdc);
	}

	void Goopy_Le_Grande_Boss::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetTag() == enums::eGameObjType::wall)
		{
			if (mFlip)
				mFlip = false;
			else
				mFlip = true;

			if (GetState() != BossPhase_state::phase3)
			{
				if (mFlip)
					mPlayerSensor->SetOffset(math::Vector2(-180, 0));
				else
					mPlayerSensor->SetOffset(math::Vector2(180, 0));
			}

			mRigidbody->SetVelocity(math::Vector2(-mRigidbody->GetVelocity().x, mRigidbody->GetVelocity().y));
		}

		if (other->GetOwner()->GetTag() == enums::eGameObjType::floor)
		{
			mRigidbody->SetGround(true);
			mRigidbody->SetVelocity(math::Vector2::Zero);
			mIsJumping = false;

			if (GetState() == BossPhase_state::phase1)
				smallLandSound->Play(false);
			else if (GetState() == BossPhase_state::phase2)
			{
				bigLandSound->Play(false);
				mPh2DustAnimator->SetActivate(true);
				mPh2DustAnimator->ForcePlayAnim(L"Goopy Le Grande_ph2_dust");
			}
		}

		if(other->GetOwner()->GetTag() == enums::eGameObjType::player && GetState() != BossPhase_state::phase3)
			dynamic_cast<Player_stage*>(other->GetOwner())->GetHit();
	}

	void Goopy_Le_Grande_Boss::OnCollisionStay(Collider* other)
	{
		if (other->GetOwner()->GetTag() == enums::eGameObjType::player)
			dynamic_cast<Player_stage*>(other->GetOwner())->GetHit();
	}

	void Goopy_Le_Grande_Boss::OnCollisionExit(Collider* other)
	{
		if (other->GetOwner()->GetTag() == enums::eGameObjType::floor)
			mRigidbody->SetGround(false);
	}

	void Goopy_Le_Grande_Boss::Intro()
	{
		mMainAnimator->PlayAnim(L"Goopy Le Grande_intro");
		if (mMainAnimator->GetCurAnim()->IsComplete())
			SetState(me::BossPhase_state::phase1);
	}

	void Goopy_Le_Grande_Boss::Phase1()
	{
		if (GetHP() <= 1064 && mRigidbody->GetIsGround())
		{
			mPunchCollider->SetActive(false);
			TransitionToPh2();
			return;
		}

		if (mPlayerSensor->Sensed() && mRigidbody->GetIsGround() && !mIsPunching)
		{
			if (fabs(attackTime - Time::GetTime()) > attackCooldown)
			{
				mIsPunching = true;
				back = true;
				stretch = false;
			}
		}

		if (mIsPunching)
		{
			Punch();
		}
		else
		{
			Jump();
		}
	}
	void Goopy_Le_Grande_Boss::Phase2()
	{
		if (GetHP() <= 504 && mRigidbody->GetIsGround())
		{
			TransitionToPh3();
			return;
		}

		if (mPlayerSensor->Sensed() && mRigidbody->GetIsGround() && !mIsPunching)
		{
			if (fabs(attackTime - Time::GetTime()) > attackCooldown)
			{
				mIsPunching = true;
				back = true;
				stretch = false;
			}
		}

		if (mIsPunching)
		{
			Punch();
		}
		else
		{
			Jump();
		}
	}
	void Goopy_Le_Grande_Boss::Phase3()
	{
		if (GetHP() <= 0)
		{
			SetState(BossPhase_state::death);
			return;
		}

		if (mPlayerSensor->Sensed())
		{
			if (fabs(attackTime - Time::GetTime()) > attackCooldown)
			{
				mIsSmashing = true;
				attackTime = Time::GetTime();
			}
		}

		if (mIsSmashing)
		{
			Smash();
		}
		else
		{
			mSmashCollider->SetActive(false);
			TombMove();
		}
	}
	void Goopy_Le_Grande_Boss::Death()
	{
		mMainAnimator->PlayAnim(L"Goopy Le Grande_tomb_death");
	}

	void Goopy_Le_Grande_Boss::TransitionToPh2()
	{		
		if (!phCheckOne)
		{
			mMainAnimator->PlayAnim(L"Goopy Le Grande_transition_to_ph2_first");
			if (mMainAnimator->GetCurAnim()->IsComplete())
			{
				phCheckOne = true;
				SceneManager::Instantiate<QuestionMark>(enums::eLayer::Sensor, mTransform->GetPos() + math::Vector2(150, -100), L"questionMarkOne");
				SceneManager::Instantiate<QuestionMark>(enums::eLayer::Sensor, mTransform->GetPos() + math::Vector2(0, -200), L"questionMarkTwo");
				SceneManager::Instantiate<QuestionMark>(enums::eLayer::Sensor, mTransform->GetPos() + math::Vector2(-150, -100), L"questionMarkThree");
			}
			else
				return;
		}

		if (!phCheckTwo)
		{
			if(startTimePh == -1)
				startTimePh = Time::GetTime();
			mMainAnimator->PlayAnim(L"Goopy Le Grande_transition_to_ph2_second");
			if (fabs(startTimePh - (int)Time::GetTime()) > 2.5f)
				phCheckTwo = true;
			else
				return;
		}

		if (!phCheckThree)
		{
			mMainAnimator->PlayAnim(L"Goopy Le Grande_transition_to_ph2_third");
			if (mMainAnimator->GetCurAnim()->IsComplete())
				phCheckThree = true;
			else
				return;
		}

		SetState(BossPhase_state::phase2);
		mMainCollider->SetRadius(170);
		mMainCollider->SetOffset(mMainCollider->GetOffset() + math::Vector2(0, -25));

		mPlayerSensor->SetColliderSize(math::Vector2(500, 250));
		mPunchCollider->SetOffset(mPunchCollider->GetOffset() + math::Vector2(0, 60));
		mPunchCollider->SetColliderSize(math::Vector2(200, 200));

		phCheckOne = false;
		phCheckTwo = false;
		phCheckThree = false;

		startTimePh = -1;
	}

	void Goopy_Le_Grande_Boss::TransitionToPh3()
	{
		mPh2DustAnimator->SetActivate(false);
		mPlayerSensor->SetActive(false);

		if (!phCheckOne)
		{
			if (startTimePh == -1)
				startTimePh = Time::GetTime();

			mMainAnimator->PlayAnim(L"Goopy Le Grande_big_death");
			if (fabs(startTimePh - Time::GetTime()) > 3.5f)
			{
				phCheckOne = true;
				startTimePh = -1;
			}
			else
				return;
		}

		if (!phCheckTwo)
		{
			if (startTimePh == -1)
				startTimePh = Time::GetTime();

			Ph3Intro();
			return;
		}

		SetState(BossPhase_state::phase3);

		mRigidbody->SetActivate(false);

		mMainCollider->SetRadius(120.f);

		mPlayerSensor->SetOffset(math::Vector2(0, 100));
		mPlayerSensor->SetColliderSize(math::Vector2(400, 200));
		mPlayerSensor->SetActive(true);

		mTransform->SetPos(mTransform->GetPos() + math::Vector2(0, -150));

		phCheckOne = false;
		phCheckTwo = false;

		ColliderManager::CollisionLayerCheck(enums::eLayer::Player, enums::eLayer::Enemy, false);
	}

	void Goopy_Le_Grande_Boss::Ph3Intro()
	{
		mPh3IntroAnimator->PlayAnim(L"Goopy Le Grande_tomb_intro");

		if (mPh3IntroAnimator->GetCurAnim()->GetOffset() >= math::Vector2(0, -50))
		{
			mMainAnimator->SetActivate(false);
			if (fabs(startTimePh - Time::GetTime()) > 0.8f)
			{
				mMainAnimator->SetActivate(true);
				phCheckTwo = true;
				mPh3IntroAnimator->SetActivate(false);
				startTimePh = -1;
			}
		}
		else
		{
			mPh3IntroAnimator->GetCurAnim()->SetOffset(mPh3IntroAnimator->GetCurAnim()->GetOffset() + math::Vector2(0, 1200 * Time::GetDeltaTime()));
		}
	}

	void Goopy_Le_Grande_Boss::Jump()
	{
		mPunchCollider->SetActive(false);

		if (!mIsJumping)
		{
			if (GetState() == BossPhase_state::phase1)
				mMainAnimator->PlayAnim(L"Goopy Le Grande_small_jump", mFlip);
			else if (GetState() == BossPhase_state::phase2)
			{
				mMainAnimator->PlayAnim(L"Goopy Le Grande_big_jump", mFlip);
			}
			if (mMainAnimator->GetCurAnim()->IsComplete())
			{
				mIsJumping = true;
				mRigidbody->SetGround(false);
				smallJumpSound->Play(false);

				if (mFlip)
				{
					Player_stage* player = dynamic_cast<BossFightScene*>(SceneManager::GetCurScene())->GetPlayer();

					if (fabs(player->GetComponent<Transform>()->GetPos().x - mTransform->GetPos().x) > 150)
					{
						mRigidbody->AddForce(math::Vector2(-100000, -100000));
					}
					else
					{
						mRigidbody->AddForce(math::Vector2(-70000, -80000));
					}
				}
				else
				{
					Player_stage* player = dynamic_cast<BossFightScene*>(SceneManager::GetCurScene())->GetPlayer();

					if (fabs(player->GetComponent<Transform>()->GetPos().x - mTransform->GetPos().x) > 150)
					{
						mRigidbody->AddForce(math::Vector2(100000, -100000));
					}
					else
					{
						mRigidbody->AddForce(math::Vector2(70000, -80000));
					}
				}

				if (GetState() == BossPhase_state::phase2)
					mPh2DustAnimator->SetActivate(false);
			}
		}
		else
			JumpEffect();
	}

	void Goopy_Le_Grande_Boss::JumpEffect()
	{
		if (mRigidbody->GetIsGround())
			mIsJumping = false;

		if (mTransform->GetPos().y > mJumpMaxHeight || prevVelocity > mRigidbody->GetVelocity().y)
		{
			jumpUp = false;
			jumpDown = true;
		}

		if (GetState() == BossPhase_state::phase1)
		{
			if (jumpUp)
			{
				mMainAnimator->PlayAnim(L"Goopy Le Grande_small_air_up", mFlip);
			}
			else if (jumpDown)
			{
				mMainAnimator->PlayAnim(L"Goopy Le Grande_small_air_down", mFlip);
			}
		}
		else if (GetState() == BossPhase_state::phase2)
		{
			if (jumpUp)
			{
				mMainAnimator->PlayAnim(L"Goopy Le Grande_big_air_up", mFlip);
			}
			else if (jumpDown)
			{
				mMainAnimator->PlayAnim(L"Goopy Le Grande_big_air_down", mFlip);
			}
		}
	}

	void Goopy_Le_Grande_Boss::Punch()
	{
		if (GetState() == BossPhase_state::phase1)
		{
			if (punchStartTime == -1)
				punchStartTime = Time::GetTime();

			mPunchCollider->SetActive(true);

			if (back)
			{
				mMainAnimator->PlayAnim(L"Goopy Le Grande_small_punch_back", mFlip);

				if (1.2f < fabs(punchStartTime - Time::GetTime()))
				{
					stretch = true;
					back = false;
					punchStartTime = Time::GetTime();
					return;
				}

				mPunchCollider->SetOffset(math::Vector2(0, mPunchCollider->GetOffset().y));
			}
			else if (stretch)
			{
				if (1.2f < fabs(punchStartTime - Time::GetTime()))
				{
					stretch = false;
					return;
				}

				mMainAnimator->PlayAnim(L"Goopy Le Grande_small_punch_stretch", mFlip);
				if (fabs(mPunchCollider->GetOffset().x) < PunchMaxDist)
				{
					if (mFlip)
						mPunchCollider->SetOffset(mPunchCollider->GetOffset() + math::Vector2(-1000.f * Time::GetDeltaTime(), 0));
					else
						mPunchCollider->SetOffset(mPunchCollider->GetOffset() + math::Vector2(1000.f * Time::GetDeltaTime(), 0));
				}
			}

			if (!stretch && !back)
			{
				mMainAnimator->PlayAnim(L"Goopy Le Grande_small_punch_end", mFlip);

				if (mMainAnimator->GetCurAnim()->IsComplete())
				{
					mIsPunching = false;
					mPunchCollider->SetOffset(math::Vector2(0, mPunchCollider->GetOffset().y));
					mPunchCollider->SetActive(false);
					punchStartTime = -1;
					attackTime = Time::GetTime();
					return;
				}

				if (fabs(mPunchCollider->GetOffset().x) > 100)
				{
					if (mFlip)
						mPunchCollider->SetOffset(mPunchCollider->GetOffset() + math::Vector2(1000.f * Time::GetDeltaTime(), 0));
					else
						mPunchCollider->SetOffset(mPunchCollider->GetOffset() + math::Vector2(-1000.f * Time::GetDeltaTime(), 0));
				}
			}
		}
		else if (GetState() == BossPhase_state::phase2)
		{
			if (punchStartTime == -1)
				punchStartTime = Time::GetTime();

			mPunchCollider->SetActive(true);

			if (back)
			{
				mMainAnimator->PlayAnim(L"Goopy Le Grande_big_punch_back", mFlip);

				if(0.7f < fabs(punchStartTime - Time::GetTime()))
				{
					stretch = true;
					back = false;
					punchStartTime = Time::GetTime();
					return;
				}

				mPunchCollider->SetOffset(math::Vector2(0, mPunchCollider->GetOffset().y));
			}
			else if (stretch)
			{
				if(1.2f < fabs(punchStartTime - Time::GetTime()))
				{
					stretch = false;
					return;
				}

				mMainAnimator->PlayAnim(L"Goopy Le Grande_big_punch_stretch", mFlip);
				if (fabs(mPunchCollider->GetOffset().x) < PunchMaxDist)
				{
					if (mFlip)
						mPunchCollider->SetOffset(mPunchCollider->GetOffset() + math::Vector2(-800.f * Time::GetDeltaTime(), 0));
					else
						mPunchCollider->SetOffset(mPunchCollider->GetOffset() + math::Vector2(800.f * Time::GetDeltaTime(), 0));
				}
			}

			if (!stretch && !back)
			{
				mMainAnimator->PlayAnim(L"Goopy Le Grande_big_punch_end", mFlip);

				if (mMainAnimator->GetCurAnim()->IsComplete())
				{
					mIsPunching = false; 
					mPunchCollider->SetOffset(math::Vector2(0, mPunchCollider->GetOffset().y));
					mPunchCollider->SetActive(false);
					punchStartTime = -1;
					attackTime = Time::GetTime();
					return;
				}

				if (fabs(mPunchCollider->GetOffset().x) > 100)
				{
					if (mFlip)
						mPunchCollider->SetOffset(mPunchCollider->GetOffset() + math::Vector2(800.f * Time::GetDeltaTime(), 0));
					else
						mPunchCollider->SetOffset(mPunchCollider->GetOffset() + math::Vector2(-800.f * Time::GetDeltaTime(), 0));
				}
			}
		}
	}
	void Goopy_Le_Grande_Boss::Smash()
	{
		mMainAnimator->PlayAnim(L"Goopy Le Grande_tomb_smash");

		if ((fabs(attackTime - Time::GetTime()) > 0.7f) && mPlayerSensor->Sensed())
		{
			dynamic_cast<Player_stage*>(mPlayerSensor->GetSensedObj())->GetHit();
		}

		if (mMainAnimator->GetCurAnim()->IsComplete())
			mIsSmashing = false;
	}
	void Goopy_Le_Grande_Boss::TombMove()
	{
		mMainAnimator->PlayAnim(L"Goopy Le Grande_tomb_move", mFlip);

		if(mFlip)
			mTransform->SetPos(mTransform->GetPos() + math::Vector2(-600 * Time::GetDeltaTime(), 0));
		else
			mTransform->SetPos(mTransform->GetPos() + math::Vector2(600 * Time::GetDeltaTime(), 0));
	}
}
