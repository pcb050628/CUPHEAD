#include "meGoopy_Le_Grande_Boss.h"
#include "meSceneManager.h"
#include "meResourceManager.h"

namespace me
{
#define PunchMaxDist 400

	Goopy_Le_Grande_Boss::Goopy_Le_Grande_Boss(const std::wstring& name) : Boss(name)
		, mAnimator(nullptr)
		, mFlip(true)
		, mMainCollider(nullptr)
		, mPunchCollider(nullptr)
		, startTime(0)
		, PunchHoldingTime(0.45f)
		, punchCooldown(5)
		, mSmashCollider(nullptr)
		, mIsGround(true)
		, mIsJumping(false)
		, mJumpMaxHeight(450)
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
		mMainCollider->SetVerticalRadius(100);
		mMainCollider->SetHorizontalRadius(100);

		mPunchCollider = SceneManager::Instantiate<Sensor>(L"test", enums::eLayer::Sensor, mTransform->GetPos(), L"Punch");
		mPunchCollider->SetOwner(this);
		mPunchCollider->SetTargetType(enums::eGameObjType::player);
		mPunchCollider->SetColliderSize(math::Vector2(250, 250));
		mPunchCollider->SetOffset(math::Vector2(0, -100));
		
		mPunchSensor = SceneManager::Instantiate<Sensor>(L"test", enums::eLayer::Sensor, mTransform->GetPos(), L"enemySensor");
		mPunchSensor->SetOwner(this);
		mPunchSensor->SetTargetType(enums::eGameObjType::player);
		mPunchSensor->SetOffset(math::Vector2(-180, 0));
		mPunchSensor->SetColliderSize(math::Vector2(400, 100));

		mSmashCollider = AddComponent<BoxCollider>(L"Smash");

		//mMainCollider->SetActivate(false);
		mPunchCollider->SetActive(false);
		mSmashCollider->SetActivate(false);

		mAnimator = AddComponent<Animator>(enums::eComponentType::Animator);

		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_intro", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Intro\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_air_down_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Air Down_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_air_down_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Air Down_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_air_up_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Air Up_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_air_up_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Air Up_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_jump_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Jump_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_jump_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Jump_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_punch_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Punch_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_small_punch_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Punch_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_transition_to_ph2_first", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Transition To Ph2_L\\First\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_transition_to_ph2_second", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Transition To Ph2_L\\Second\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_transition_to_ph2_third", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 1\\Transition To Ph2_L\\Third\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_air_down_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 2\\Air Down_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_air_down_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 2\\Air Down_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_air_up_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 2\\Air Up_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_air_up_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 2\\Air Up_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_jump_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 2\\Jump_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_jump_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 2\\Jump_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_punch_L", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 2\\Punch_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Goopy Le Grande_big_punch_R", L"..\\content\\BossFight\\Goopy Le Grande\\Phase 2\\Punch_R\\"));

		mAnimator->GetAnim(L"Goopy Le Grande_intro")->SetOffset(math::Vector2(-90, -90));
		mAnimator->GetAnim(L"Goopy Le Grande_small_punch_L")->SetOffset(math::Vector2(0, -10));
		mAnimator->GetAnim(L"Goopy Le Grande_intro")->SetLoop(false);
		mAnimator->GetAnim(L"Goopy Le Grande_transition_to_ph2_first")->SetLoop(false);
		mAnimator->GetAnim(L"Goopy Le Grande_transition_to_ph2_third")->SetLoop(false);
		mAnimator->GetAnim(L"Goopy Le Grande_small_jump_L")->SetLoop(false);
		mAnimator->GetAnim(L"Goopy Le Grande_small_jump_R")->SetLoop(false);
		mAnimator->GetAnim(L"Goopy Le Grande_big_jump_L")->SetLoop(false);
		mAnimator->GetAnim(L"Goopy Le Grande_big_jump_R")->SetLoop(false);
		mAnimator->PlayAnim(L"Goopy Le Grande_intro");
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
				mPunchSensor->SetOffset(math::Vector2(180, 0));
			}
			else
			{
				mFlip = true;
				mPunchSensor->SetOffset(math::Vector2(-180, 0));
			}
		}

		if (other->GetOwner()->GetTag() == enums::eGameObjType::floor)
			mIsGround = true;
	}

	void Goopy_Le_Grande_Boss::OnCollisionStay(Collider* other)
	{
	}

	void Goopy_Le_Grande_Boss::OnCollisionExit(Collider* other)
	{
	}

	void Goopy_Le_Grande_Boss::Intro()
	{
		mAnimator->PlayAnim(L"Goopy Le Grande_intro");
		if (mAnimator->GetCurAnim()->IsComplete())
			SetState(me::BossPhase_state::phase1);
	}

	void Goopy_Le_Grande_Boss::Phase1()
	{
		if (GetHP() <= 1064 && mIsGround)
		{
			TransitionToPh2();
			return;
		}

		if (mPunchSensor->Sensed() && mIsGround && !mIsPunching)
		{
			if (fabs(startTime - Time::GetTime()) > punchCooldown)
			{
				mIsPunching = true;
				stretch = true;
				startTime = Time::GetTime();
			}
		}

		if (mIsPunching)
		{
			Punch();
		}
		else
		{
			if (!mIsJumping && mIsGround)
			{	
				mJumpStartPoint = mTransform->GetPos().y;
				mIsJumping = true;
			}

			if (mIsGround)
			{
				mAnimator->PlayAnim(L"Goopy Le Grande_small_jump", mFlip);
				if (mAnimator->GetCurAnim()->IsComplete())
				{
					Jump();
					mIsGround = false;
				}
			}
			else
				Jump();
		}
	}
	void Goopy_Le_Grande_Boss::Phase2()
	{
		if (GetHP() <= 504)
		{

		}

		if (mPunchSensor->Sensed() && mIsGround)
		{
			Punch();
		}
		else
		{
			if (!mIsJumping && mIsGround)
			{
				mJumpStartPoint = mTransform->GetPos().y;
				mIsJumping = true;
			}

			if (mIsGround)
			{
				mAnimator->PlayAnim(L"Goopy Le Grande_big_jump", mFlip);
				if (mAnimator->GetCurAnim()->IsComplete())
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

	}
	void Goopy_Le_Grande_Boss::Death()
	{
	}

	void Goopy_Le_Grande_Boss::TransitionToPh2()
	{
		static bool one = false;
		static bool two = false;
		static bool three = false;
		
		if (!one)
		{
			mAnimator->PlayAnim(L"Goopy Le Grande_transition_to_ph2_first");
			if (mAnimator->GetCurAnim()->IsComplete())
				one = true;
			else
				return;
		}

		if (!two)
		{
			static int startTime = Time::GetTime();
			mAnimator->PlayAnim(L"Goopy Le Grande_transition_to_ph2_second");
			if (fabs(startTime - (int)Time::GetTime()) > 1.5f)
				two = true;
			else
				return;
		}

		if (!three)
		{
			mAnimator->PlayAnim(L"Goopy Le Grande_transition_to_ph2_third");
			if (mAnimator->GetCurAnim()->IsComplete())
				three = true;
			else
				return;
		}

		SetState(BossPhase_state::phase2);
		mMainCollider->SetHorizontalRadius(170);
		mMainCollider->SetVerticalRadius(170);
		mMainCollider->SetOffset(mMainCollider->GetOffset() + math::Vector2(0, -25));

		mPunchSensor->SetColliderSize(math::Vector2());
	}

	void Goopy_Le_Grande_Boss::TransitionToPh3()
	{
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
			mAnimator->PlayAnim(L"Goopy Le Grande_small_air_up", mFlip);
		}
		else if (GetState() == BossPhase_state::phase2)
		{
			ypos -= 250.f * Time::GetDeltaTime();

			if (mFlip)
				xpos -= 300.f * Time::GetDeltaTime();
			else
				xpos += 300.f * Time::GetDeltaTime();

			mTransform->SetPos(math::Vector2(xpos, ypos));
			mAnimator->PlayAnim(L"Goopy Le Grande_big_air_up", mFlip);
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
			mAnimator->PlayAnim(L"Goopy Le Grande_small_air_down", mFlip);
		}
		else if (GetState() == BossPhase_state::phase2)
		{
			ypos += 400.f * Time::GetDeltaTime();

			if (mFlip)
				xpos -= 300.f * Time::GetDeltaTime();
			else
				xpos += 300.f * Time::GetDeltaTime();

			mTransform->SetPos(math::Vector2(xpos, ypos));
			mAnimator->PlayAnim(L"Goopy Le Grande_big_air_down", mFlip);
		}
	}
	void Goopy_Le_Grande_Boss::Punch()
	{
		if (GetState() == BossPhase_state::phase1)
		{
			mPunchCollider->SetActive(true);
			mAnimator->PlayAnim(L"Goopy Le Grande_small_punch", mFlip);
			if (stretch && fabs(mPunchCollider->GetOffset().x) > PunchMaxDist)
			{
				stretch = false;
				back = true;
				startTime = Time::GetTime();
			}
			else if (back && fabs(mPunchCollider->GetOffset().x) < 10)
			{
				back = false;
			}

			if (!stretch && !back)
			{
				mIsPunching = false;
				mPunchCollider->SetActive(false);
				return;
			}

			if (stretch && fabs(startTime - Time::GetTime()) >= PunchHoldingTime)
			{
				if(mFlip)
					mPunchCollider->SetOffset(mPunchCollider->GetOffset() + math::Vector2(-1200.f * Time::GetDeltaTime(), 0));
				else
					mPunchCollider->SetOffset(mPunchCollider->GetOffset() + math::Vector2(1200.f * Time::GetDeltaTime(), 0));
			}
			else if(back && fabs(startTime - Time::GetTime()) >= PunchHoldingTime - 1)
			{
				if(mFlip)
					mPunchCollider->SetOffset(mPunchCollider->GetOffset() + math::Vector2(1200.f * Time::GetDeltaTime(), 0));
				else
					mPunchCollider->SetOffset(mPunchCollider->GetOffset() + math::Vector2(-1200.f * Time::GetDeltaTime(), 0));
			}
		}
		else if (GetState() == BossPhase_state::phase2)
		{

		}
	}
	void Goopy_Le_Grande_Boss::Smash()
	{
	}
}
