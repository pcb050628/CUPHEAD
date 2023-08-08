#include "meGoopy_Le_Grande_Boss.h"
#include "meSceneManager.h"
#include "meResourceManager.h"
#include "meQuestionMark.h"

namespace me
{
#define PunchMaxDist 400

	Goopy_Le_Grande_Boss::Goopy_Le_Grande_Boss(const std::wstring& name) : Boss(name)
		, mMainAnimator(nullptr)
		, mFlip(true)
		, mMainCollider(nullptr)
		, mPunchCollider(nullptr)
		, attackStartTime(0)
		, smallPunchHoldingTime(0.45f)
		, bigPunchHoldingTime(0.9f)
		, attackCooldown(5)
		, mSmashCollider(nullptr)
		, mIsGround(true)
		, mIsJumping(false)
		, mJumpMaxHeight(450)
		, startTimePh(-1)
	{
	}
	Goopy_Le_Grande_Boss::~Goopy_Le_Grande_Boss()
	{
	}
	void Goopy_Le_Grande_Boss::Init()
	{
		Boss::Init();

		SetHP(1400);

		mTransform = GetComponent<Transform>();

		mMainCollider = AddComponent<CircleCollider>(L"Main");
		mMainCollider->SetRadius(100);

		mPunchCollider = SceneManager::Instantiate<Sensor>(L"test", enums::eLayer::Sensor, mTransform->GetPos(), L"Punch");
		mPunchCollider->SetOwner(this);
		mPunchCollider->SetTargetType(enums::eGameObjType::player);
		mPunchCollider->SetColliderSize(math::Vector2(250, 250));
		mPunchCollider->SetOffset(math::Vector2(0, -130));
		
		mPlayerSensor = SceneManager::Instantiate<Sensor>(L"test", enums::eLayer::Sensor, mTransform->GetPos(), L"enemySensor");
		mPlayerSensor->SetOwner(this);
		mPlayerSensor->SetTargetType(enums::eGameObjType::player);
		mPlayerSensor->SetOffset(math::Vector2(-180, 0));
		mPlayerSensor->SetColliderSize(math::Vector2(400, 100));

		mSmashCollider = SceneManager::Instantiate<Sensor>(L"test", enums::eLayer::Sensor, mTransform->GetPos(), L"Smash");

		mPunchCollider->SetActive(false);
		mSmashCollider->SetActive(false);

		mMainAnimator = AddComponent<Animator>(enums::eComponentType::Animator);

		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_intro", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Intro\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_air_down_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Air Down_L\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_air_down_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Air Down_R\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_air_up_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Air Up_L\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_air_up_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Air Up_R\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_jump_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Jump_L\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_jump_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Jump_R\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_punch_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Punch_L\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_punch_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Punch_R\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_transition_to_ph2_first", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Transition To Ph2_L\\First\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_transition_to_ph2_second", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Transition To Ph2_L\\Second\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_transition_to_ph2_third", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Transition To Ph2_L\\Third\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_air_down_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 2\\Air Down_L\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_air_down_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 2\\Air Down_R\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_air_up_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 2\\Air Up_L\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_air_up_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 2\\Air Up_R\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_jump_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 2\\Jump_L\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_jump_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 2\\Jump_R\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_punch_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 2\\Punch_L\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_punch_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 2\\Punch_R\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_death", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 2\\Death\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_tomb_move_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 3\\Left\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_tomb_move_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 3\\Right\\"));
		mMainAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_tomb_smash", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 3\\Right\\"));

		mPh3IntroAnimator = AddComponent<Animator>(L"ph3Intro");
		mPh3IntroAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_tomb_intro", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 3\\Intro\\"));

		mPh2DustAnimator = AddComponent<Animator>(L"dustAnimator");
		mPh2DustAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_ph2_dust", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 2\\Dust\\A\\"));
		mPh2DustAnimator->GetAnim(L"Goopy Le Grande_ph2_dust")->SetDuration(0.05f);

		mMainAnimator->GetAnim(L"Goopy Le Grande_intro")->SetOffset(math::Vector2(-90, -90));
		mMainAnimator->GetAnim(L"Goopy Le Grande_small_punch_L")->SetOffset(math::Vector2(0, -10));
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_punch_L")->SetOffset(math::Vector2(0, -10));
		mMainAnimator->GetAnim(L"Goopy Le Grande_intro")->SetLoop(false);
		mMainAnimator->GetAnim(L"Goopy Le Grande_transition_to_ph2_first")->SetLoop(false);
		mMainAnimator->GetAnim(L"Goopy Le Grande_transition_to_ph2_third")->SetLoop(false);
		mMainAnimator->GetAnim(L"Goopy Le Grande_small_jump_L")->SetLoop(false);
		mMainAnimator->GetAnim(L"Goopy Le Grande_small_jump_R")->SetLoop(false);
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_jump_L")->SetLoop(false);
		mMainAnimator->GetAnim(L"Goopy Le Grande_big_jump_R")->SetLoop(false);
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
			{
				mFlip = false;
				mPlayerSensor->SetOffset(math::Vector2(180, 0));
			}
			else
			{
				mFlip = true;
				mPlayerSensor->SetOffset(math::Vector2(-180, 0));
			}
		}

		if (other->GetOwner()->GetTag() == enums::eGameObjType::floor)
		{
			mIsGround = true;
			if (GetState() == BossPhase_state::phase1)
				smallLandSound->Play(false);
			else if (GetState() == BossPhase_state::phase2)
				bigLandSound->Play(false);
		}
	}

	void Goopy_Le_Grande_Boss::OnCollisionStay(Collider* other)
	{
	}

	void Goopy_Le_Grande_Boss::OnCollisionExit(Collider* other)
	{
	}

	void Goopy_Le_Grande_Boss::Intro()
	{
		mMainAnimator->PlayAnim(L"Goopy Le Grande_intro");
		if (mMainAnimator->GetCurAnim()->IsComplete())
			SetState(me::BossPhase_state::phase1);
	}

	void Goopy_Le_Grande_Boss::Phase1()
	{
		if (GetHP() <= 1064 && mIsGround)
		{
			mPunchCollider->SetActive(false);
			TransitionToPh2();
			return;
		}

		if (mPlayerSensor->Sensed() && mIsGround && !mIsPunching)
		{
			if (fabs(attackStartTime - Time::GetTime()) > attackCooldown)
			{
				mIsPunching = true;
				stretch = true;
				attackStartTime = Time::GetTime();
			}
		}

		if (mIsPunching)
		{
			Punch();
		}
		else
		{
			mPunchCollider->SetActive(false);
			if (!mIsJumping && mIsGround)
			{	
				mJumpStartPoint = mTransform->GetPos().y;
				mIsJumping = true;
			}

			if (mIsGround)
			{
				mMainAnimator->PlayAnim(L"Goopy Le Grande_small_jump", mFlip);
				if (mMainAnimator->GetCurAnim()->IsComplete())
				{
					Jump();
					mIsGround = false;
					smallJumpSound->Play(false);
				}
			}
			else
				Jump();
		}
	}
	void Goopy_Le_Grande_Boss::Phase2()
	{
		if (GetHP() <= 504 && mIsGround)
		{
			TransitionToPh3();
			return;
		}

		if (mPlayerSensor->Sensed() && mIsGround && !mIsPunching)
		{
			if (fabs(attackStartTime - Time::GetTime()) > attackCooldown)
			{
				mIsPunching = true;
				stretch = true;
				attackStartTime = Time::GetTime();
			}
		}

		if (mIsPunching)
		{
			Punch();
		}
		else
		{
			mPunchCollider->SetActive(false);
			if (!mIsJumping && mIsGround)
			{
				mJumpStartPoint = mTransform->GetPos().y;
				mIsJumping = true;
			}

			if (mIsGround)
			{
				mMainAnimator->PlayAnim(L"Goopy Le Grande_big_jump", mFlip);
				if (mMainAnimator->GetCurAnim()->IsComplete())
				{
					Jump();
					mIsGround = false;
				}
			}
			else
				Jump();
		}
	}
	void Goopy_Le_Grande_Boss::Phase3()
	{
		/*if (GetHP() <= 0)
		{
			SetState(BossPhase_state::death);
			return;
		}*/

		if (mPlayerSensor->Sensed())
		{
			if (fabs(attackStartTime - Time::GetTime()) > attackCooldown)
			{
				mIsSmashing = true;
				attackStartTime = Time::GetTime();
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
			if (fabs(startTimePh - (int)Time::GetTime()) > 3.5f)
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

		mPlayerSensor->SetColliderSize(math::Vector2(500, 150));
		mPunchCollider->SetOffset(mPunchCollider->GetOffset() + math::Vector2(0, 50));

		phCheckOne = false;
		phCheckTwo = false;
		phCheckThree = false;

		startTimePh = -1;
	}

	void Goopy_Le_Grande_Boss::TransitionToPh3()
	{
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

		mPlayerSensor->SetOffset(math::Vector2(0, 100));
		mPlayerSensor->SetColliderSize(math::Vector2(100, 100));

		mTransform->SetPos(mTransform->GetPos() + math::Vector2(0, -200));

		phCheckOne = false;
		phCheckTwo = false;
	}

	void Goopy_Le_Grande_Boss::Ph3Intro()
	{
		mPh3IntroAnimator->PlayAnim(L"Goopy Le Grande_tomb_intro");

		if (mPh3IntroAnimator->GetCurAnim()->GetOffset() >= math::Vector2(0, -100))
		{
			mMainAnimator->SetActivate(false);
			if (fabs(startTimePh - Time::GetTime()) > 2.f)
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
		if (fabs(mJumpStartPoint - mTransform->GetPos().y) > mJumpMaxHeight)
			mIsJumping = false;

		if (mIsJumping)
		{
			MoveUp();
		}
		else
		{
			MoveDown();
		}
	}
	void Goopy_Le_Grande_Boss::MoveUp()
	{
		float ypos = mTransform->GetPos().y;
		float xpos = mTransform->GetPos().x;

		if (GetState() == BossPhase_state::phase1)
		{
			ypos -= 300.f * Time::GetDeltaTime();

			if (mFlip)
				xpos -= 300.f * Time::GetDeltaTime();
			else
				xpos += 300.f * Time::GetDeltaTime();
			
			mTransform->SetPos(math::Vector2(xpos, ypos));
			mMainAnimator->PlayAnim(L"Goopy Le Grande_small_air_up", mFlip);
		}
		else if (GetState() == BossPhase_state::phase2)
		{
			ypos -= 250.f * Time::GetDeltaTime();

			if (mFlip)
				xpos -= 300.f * Time::GetDeltaTime();
			else
				xpos += 300.f * Time::GetDeltaTime();

			mTransform->SetPos(math::Vector2(xpos, ypos));
			mMainAnimator->PlayAnim(L"Goopy Le Grande_big_air_up", mFlip);
		}
	}
	void Goopy_Le_Grande_Boss::MoveDown()
	{
		float ypos = mTransform->GetPos().y;
		float xpos = mTransform->GetPos().x;
		if (GetState() == BossPhase_state::phase1)
		{
			ypos += 300.f * Time::GetDeltaTime();

			if (mFlip)
				xpos -= 300.f * Time::GetDeltaTime();
			else
				xpos += 300.f * Time::GetDeltaTime();

			mTransform->SetPos(math::Vector2(xpos, ypos));
			mMainAnimator->PlayAnim(L"Goopy Le Grande_small_air_down", mFlip);
		}
		else if (GetState() == BossPhase_state::phase2)
		{
			ypos += 400.f * Time::GetDeltaTime();

			if (mFlip)
				xpos -= 300.f * Time::GetDeltaTime();
			else
				xpos += 300.f * Time::GetDeltaTime();

			mTransform->SetPos(math::Vector2(xpos, ypos));
			mMainAnimator->PlayAnim(L"Goopy Le Grande_big_air_down", mFlip);
		}
	}
	void Goopy_Le_Grande_Boss::Punch()
	{
		if (GetState() == BossPhase_state::phase1)
		{
			mPunchCollider->SetActive(true);
			mMainAnimator->PlayAnim(L"Goopy Le Grande_small_punch", mFlip);
			if (stretch && fabs(mPunchCollider->GetOffset().x) > PunchMaxDist)
			{
				stretch = false;
				back = true;
				attackStartTime = Time::GetTime();
			}
			else if (back && (fabs(mPunchCollider->GetOffset().x) < 10 || fabs(mPunchCollider->GetOffset().x) > 1000))
			{
				back = false;
			}

			if (!stretch && !back)
			{
				mIsPunching = false;
				mPunchCollider->SetActive(false);
				mPunchCollider->SetOffset(math::Vector2(0, -130));
				return;
			}

			if (stretch && fabs(attackStartTime - Time::GetTime()) >= smallPunchHoldingTime)
			{
				if(mFlip)
					mPunchCollider->SetOffset(mPunchCollider->GetOffset() + math::Vector2(-1200.f * Time::GetDeltaTime(), 0));
				else
					mPunchCollider->SetOffset(mPunchCollider->GetOffset() + math::Vector2(1200.f * Time::GetDeltaTime(), 0));
			}
			else if(back && fabs(attackStartTime - Time::GetTime()) >= smallPunchHoldingTime - 1)
			{
				if(mFlip)
					mPunchCollider->SetOffset(mPunchCollider->GetOffset() + math::Vector2(1400.f * Time::GetDeltaTime(), 0));
				else
					mPunchCollider->SetOffset(mPunchCollider->GetOffset() + math::Vector2(-1400.f * Time::GetDeltaTime(), 0));
			}
		}
		else if (GetState() == BossPhase_state::phase2)
		{
			mPunchCollider->SetActive(true);
			mMainAnimator->PlayAnim(L"Goopy Le Grande_big_punch", mFlip);
			if (stretch && fabs(mPunchCollider->GetOffset().x) > PunchMaxDist)
			{
				stretch = false;
				back = true;
				attackStartTime = Time::GetTime();
			}
			else if (back && (fabs(mPunchCollider->GetOffset().x) < 10 || fabs(mPunchCollider->GetOffset().x) > 1000))
			{
				back = false;
			}

			if (!stretch && !back)
			{
				mIsPunching = false;
				mPunchCollider->SetActive(false);
				mPunchCollider->SetOffset(math::Vector2(0, -130));
				return;
			}

			if (stretch && fabs(attackStartTime - Time::GetTime()) >= bigPunchHoldingTime)
			{
				if (mFlip)
					mPunchCollider->SetOffset(mPunchCollider->GetOffset() + math::Vector2(-1000.f * Time::GetDeltaTime(), 0));
				else
					mPunchCollider->SetOffset(mPunchCollider->GetOffset() + math::Vector2(1000.f * Time::GetDeltaTime(), 0));
			}
			else if (back)
			{
				if (mFlip)
					mPunchCollider->SetOffset(mPunchCollider->GetOffset() + math::Vector2(900.f * Time::GetDeltaTime(), 0));
				else
					mPunchCollider->SetOffset(mPunchCollider->GetOffset() + math::Vector2(-900.f * Time::GetDeltaTime(), 0));
			}
		}
	}
	void Goopy_Le_Grande_Boss::Smash()
	{
	}
	void Goopy_Le_Grande_Boss::TombMove()
	{
		mMainAnimator->PlayAnim(L"Goopy Le Grande_tomb_move", mFlip);

		if(mFlip)
			mTransform->SetPos(mTransform->GetPos() + math::Vector2(-800 * Time::GetDeltaTime(), 0));
		else
			mTransform->SetPos(mTransform->GetPos() + math::Vector2(800 * Time::GetDeltaTime(), 0));
	}
}
