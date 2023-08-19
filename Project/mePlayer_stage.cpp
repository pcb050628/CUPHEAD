#include "mePlayer_stage.h"
#include "COMPONENTS.h"
#include "meSceneManager.h"
#include "meResourceManager.h"
#include "meBullet.h"

#define COLLIDER_DEFAULT_SIZE_X 85.f
#define COLLIDER_DEFAULT_SIZE_Y 130.f
#define COLLIDER_DEFAULT_OFFSET_X 0
#define COLLIDER_DEFAULT_OFFSET_Y 10.f
#define COLLIDER_DUCK_SIZE_X 100.f
#define COLLIDER_DUCK_SIZE_Y 60.f
#define COLLIDER_DUCK_OFFSET_X 0
#define COLLIDER_DUCK_OFFSET_Y 30.f

namespace me
{
	Player_stage::Player_stage(const std::wstring& name) : GameObject(name, enums::eGameObjType::player)
		, HP(3)
		, shootDelay(0.1f), shootPrevTime(0), mShootAnim_L(nullptr), mShootAnim_R(nullptr), shootSound(nullptr)
		, mAnimator(nullptr), mTransform(nullptr), mCollider(nullptr)
		, mCurState(Player_state::Idle), mPrevState(Player_state::none)
		, mIsGround(true)
		, mIsHit(false), mHitStartTime(0), mHitHoldingTime(0.1f), mInvincibleTime(2.f), hitSound(nullptr)
		, mIsJumping(false), mJumpStartHeight(0), mJumpMinHeight(250.f), mJumpMaxHeight(300.f), jumpSound(nullptr)
		, canParry(true), mIsParrying(false), parrySuccess(false), mParryStartTime(-1.f), mParryHoldingTime(0.3f)
		, mIsDash(false), mDashMaxDist(300.f), dashSound(nullptr)

	{

	}
	Player_stage::~Player_stage()
	{
	}
	void Player_stage::Init()
	{
		GameObject::Init();

		mTransform = GetComponent<Transform>();

		mCollider = AddComponent<BoxCollider>(enums::eComponentType::Collider);
		mCollider->SetSize(math::Vector2(COLLIDER_DEFAULT_SIZE_X, COLLIDER_DEFAULT_SIZE_Y));
		mCollider->SetOffset(math::Vector2(COLLIDER_DEFAULT_OFFSET_X, COLLIDER_DEFAULT_OFFSET_Y));

		mShootAnim_R = AddComponent<Animator>(L"bullet_spawn_R");
		mShootAnim_L = AddComponent<Animator>(L"bullet_spawn_L");
		mShootAnim_R->AddAnim(*ResourceManager::Load(L"bullet_anim_spawn_R", L"..\\content\\Scene\\BossFight\\CupHead\\Bullet\\Spawn\\Right\\", eTextureType::png));
		mShootAnim_L->AddAnim(*ResourceManager::Load(L"bullet_anim_spawn_L", L"..\\content\\Scene\\BossFight\\CupHead\\Bullet\\Spawn\\Left\\", eTextureType::png));
		mShootAnim_R->GetAnim(L"bullet_anim_spawn_R")->SetDuration(0.05f);
		mShootAnim_L->GetAnim(L"bullet_anim_spawn_L")->SetDuration(0.05f);
		mShootAnim_R->SetOffset(mShootAnim_R->GetOffset() + math::Vector2(60, 0));
		mShootAnim_L->SetOffset(mShootAnim_L->GetOffset() + math::Vector2(-60 , 0));

		mAnimator = AddComponent<Animator>(L"CupHead_stage_anim");
		mAnimator->SetFlashingLoop(true);

		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_intro", L"..\\content\\Scene\\BossFight\\Cuphead\\Intros\\Regular\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_idle_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Idle_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_idle_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Idle_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_run_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Run\\Normal_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_run_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Run\\Normal_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_jump_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Jump\\Right\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_jump_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Jump\\Left\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_hit_ground_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Hit\\Ground\\Right\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_hit_ground_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Hit\\Ground\\Left\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_hit_air_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Hit\\Air\\Right\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_hit_air_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Hit\\Air\\Left\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_straight_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Shoot\\Straight_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_straight_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Shoot\\Straight_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_straight_run_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Run\\Shooting\\Straight_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_straight_run_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Run\\Shooting\\Straight_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_down_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Shoot\\Down_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_down_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Shoot\\Down_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_up_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Shoot\\Up_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_up_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Shoot\\Up_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_diagonal_down_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Shoot\\Diagonal Down_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_diagonal_down_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Shoot\\Diagonal Down_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_diagonal_up_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Shoot\\Diagonal Up_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_diagonal_up_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Shoot\\Diagonal Up_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_diagonal_up_run_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Run\\Shooting\\Diagonal Up_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_diagonal_up_run_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Run\\Shooting\\Diagonal Up_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_straight_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Aim\\Straight_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_straight_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Aim\\Straight_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_up_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Aim\\Up_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_up_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Aim\\Up_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_diagonal_up_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Aim\\Diagonal Up_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_diagonal_up_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Aim\\Diagonal Up_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_down_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Aim\\Down_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_down_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Aim\\Down_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_diagonal_down_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Aim\\Diagonal Down_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_diagonal_down_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Aim\\Diagonal Down_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_duck_idle_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Duck\\Idle_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_duck_idle_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Duck\\Idle_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_duck_shoot_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Duck\\Shoot_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_duck_shoot_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Duck\\Shoot_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_dash_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Dash\\Ground\\Right\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_dash_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Dash\\Ground\\Left\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_parry_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Parry\\Hand\\Left\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_parry_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Parry\\Hand\\Right\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_ghost", L"..\\content\\Scene\\BossFight\\Cuphead\\Ghost\\"));

		mAnimator->GetAnim(L"CupHead_stage_anim_intro")->SetDuration(0.05f);
		mAnimator->GetAnim(L"CupHead_stage_anim_run_R")->SetDuration(0.04f);
		mAnimator->GetAnim(L"CupHead_stage_anim_run_L")->SetDuration(0.04f);
		mAnimator->GetAnim(L"CupHead_stage_anim_shoot_straight_run_R")->SetDuration(0.04f);
		mAnimator->GetAnim(L"CupHead_stage_anim_shoot_straight_run_L")->SetDuration(0.04f);
		mAnimator->GetAnim(L"CupHead_stage_anim_shoot_diagonal_up_run_R")->SetDuration(0.04f);
		mAnimator->GetAnim(L"CupHead_stage_anim_shoot_diagonal_up_run_L")->SetDuration(0.04f);

		mAnimator->GetAnim(L"CupHead_stage_anim_intro")->SetLoop(false);
		mAnimator->GetAnim(L"CupHead_stage_anim_hit_air_R")->SetLoop(false);
		mAnimator->GetAnim(L"CupHead_stage_anim_hit_air_L")->SetLoop(false);
		mAnimator->GetAnim(L"CupHead_stage_anim_hit_ground_R")->SetLoop(false);
		mAnimator->GetAnim(L"CupHead_stage_anim_hit_ground_L")->SetLoop(false);
		mAnimator->GetAnim(L"CupHead_stage_anim_parry_R")->SetLoop(false);
		mAnimator->GetAnim(L"CupHead_stage_anim_parry_L")->SetLoop(false);

		jumpSound = ResourceManager::Load<Sound>(L"CupHead_stage_sound_jump", L"..\\content\\Sound\\AudioClip\\BossFightScene\\Player_stage\\sfx_player_jump_01.wav");
		shootSound = ResourceManager::Load<Sound>(L"CupHead_stage_sound_shoot", L"..\\content\\Sound\\AudioClip\\BossFightScene\\Player_stage\\sfx_player_spreadshot_fire_loop_002.wav");
		hitSound = ResourceManager::Load<Sound>(L"CupHead_stage_sound_hit", L"..\\content\\Sound\\AudioClip\\BossFightScene\\Player_stage\\sfx_player_hit_03.wav");
		dashSound = ResourceManager::Load<Sound>(L"CupHead_stage_sound_dash", L"..\\content\\Sound\\AudioClip\\BossFightScene\\Player_stage\\sfx_player_dash_03.wav");
		parrySound = ResourceManager::Load<Sound>(L"CupHead_stage_sound_parry_slap", L"..\\content\\Sound\\AudioClip\\BossFightScene\\Player_stage\\sfx_player_parry_slap_02.wav");
	}
	void Player_stage::Update()
	{
		GameObject::Update();

		if (!mIsDash)
		{
			if (KeyInput::GetKeyDown(KeyCode::RightArrow) && KeyInput::GetKeyUp(KeyCode::LeftArrow))
				mAnimator->SetFlipX(false);
			else if (KeyInput::GetKeyDown(KeyCode::LeftArrow) && KeyInput::GetKeyUp(KeyCode::RightArrow))
				mAnimator->SetFlipX(true);
		}

		if(KeyInput::GetKeyPressed(KeyCode::Z) && mIsGround && !mIsJumping && !mIsHit)
		{
			mIsJumping = true;
			mIsGround = false;
			mJumpStartHeight = GetComponent<Transform>()->GetPos().y;
			jumpSound->Play(false);
		}

		if (KeyInput::GetKeyPressed(KeyCode::LSHIFT) && !mIsDash && !mIsHit)
		{
			mIsDash = true;
			mDashFlip = mAnimator->GetFlipX();
			mDashStartPoint = mTransform->GetPos().x;
			dashSound->Play(false);

			mCollider->SetSize(math::Vector2(COLLIDER_DUCK_SIZE_X, COLLIDER_DUCK_SIZE_Y));
			mCollider->SetOffset(math::Vector2(COLLIDER_DUCK_OFFSET_X, COLLIDER_DUCK_OFFSET_Y));
		}

		if (mCurState != Player_state::Aim && mCurState != Player_state::Duck && mCurState != Player_state::Dead && !mIsHit && !mIsDash)
		{
			if (KeyInput::GetKey(KeyCode::RightArrow))
				mTransform->SetPos(math::Vector2(mTransform->GetPos().x + 350.f * Time::GetDeltaTime(), mTransform->GetPos().y));

			if (KeyInput::GetKey(KeyCode::LeftArrow))
				mTransform->SetPos(math::Vector2(mTransform->GetPos().x - 350.f * Time::GetDeltaTime(), mTransform->GetPos().y));
		}

		if (mCurState != Player_state::Dead && KeyInput::GetKeyUp(KeyCode::X) || mIsHit)
		{
			mShootAnim_R->StopPlay();
			mShootAnim_L->StopPlay();

			shootSound->Stop(true);
		}
		else 
		{
			if (mAnimator->GetFlipX())
				mShootAnim_R->StopPlay();
			else
				mShootAnim_L->StopPlay();
		}

		if (mCurState != Player_state::Dead && !mIsGround && !mIsJumping && !mIsDash)
		{
			Transform* tr = GetComponent<Transform>();
			tr->SetPos(math::Vector2(tr->GetPos().x, tr->GetPos().y + 700.f * Time::GetDeltaTime()));
			mPrevState = mCurState;
			mCurState = Player_state::Jump;
		}

		if (mAnimator->IsFlashing() && (mHitStartTime + mInvincibleTime) < Time::GetTime())
		{
			mAnimator->FlashingStop();
		}

		switch (mCurState)
		{
		case me::Player_stage::Player_state::Intro:
			Intro();
			break;
		case me::Player_stage::Player_state::Idle:
			Idle();
			break;
		case me::Player_stage::Player_state::Aim:
			Aim();
			break;
		case me::Player_stage::Player_state::Run:
			Run();
			break;
		case me::Player_stage::Player_state::Duck:
			Duck();
			break;
		case me::Player_stage::Player_state::Shooting:
			Shooting();
			break;
		case me::Player_stage::Player_state::Jump:
			Jump();
			break;
		case me::Player_stage::Player_state::Hit:
			Hit();
			break;
		case me::Player_stage::Player_state::Dash:
			Dash();
			break;
		case me::Player_stage::Player_state::Dead:
			Dead();
			break;
		}
	}

	void Player_stage::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		//wchar_t xBuffer[50] = {};
		//wchar_t yBuffer[50] = {};
		//float pox = mTransform->GetPos().x;
		//float poy = mTransform->GetPos().y;
		//
		//swprintf_s(xBuffer, L"fps : %f", pox);
		//swprintf_s(yBuffer, L"fps : %f", poy);
		//int xLen = wcsnlen_s(xBuffer, 50);
		//int yLen = wcsnlen_s(yBuffer, 50);
		//
		//TextOut(hdc, 10, 10, xBuffer, xLen);
		//TextOut(hdc, 10, 50, yBuffer, yLen);
	}

	void Player_stage::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetTag() == enums::eGameObjType::floor)
			mIsGround = true;
		if (other->GetOwner()->GetTag() == enums::eGameObjType::wall)
			mIsDash = false;

		if (mIsParrying && other->GetOwner()->GetIsParryable())
		{
			mIsParrying = false;
			parrySuccess = true;
			mJumpStartHeight = mTransform->GetPos().y;
			mIsJumping = true;
			canParry = true;
			parrySound->Play(false);
			return;
		}
	}

	void Player_stage::OnCollisionStay(Collider* other)
	{
		if (mIsParrying && other->GetOwner()->GetIsParryable())
		{
			mIsParrying = false;
			parrySuccess = true;
			mIsJumping = true;
			mJumpStartHeight = mTransform->GetPos().y;
			canParry = true;
			parrySound->Play(false);
		}

		if (other->GetOwner()->GetTag() == enums::eGameObjType::floor)
		{
			mIsGround = true;
		}
	}

	void Player_stage::OnCollisionExit(Collider* other)
	{

	}

	void Player_stage::Intro()
	{
		mAnimator->PlayAnim(L"CupHead_stage_anim_intro");
		mTransform->SetPos(math::Vector2(-420, 200));
		if (mAnimator->GetCurAnim()->IsComplete())
		{
			mPrevState = Player_state::Intro;
			mCurState = Player_state::Idle;
		}
	}

	void Player_stage::Idle()
	{
		if (HP <= 0)
		{
			mCurState = Player_state::Dead;
		}
		else if (mIsHit)
		{
			mCurState = Player_state::Hit;
			mAnimator->PlayAnim(L"CupHead_stage_anim_hit_ground", mAnimator->GetFlipX());
			return;
		}
		else if (mIsDash)
		{
			mCurState = Player_state::Dash;
		}
		else if (KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow))
		{
			mCurState = Player_state::Run;
		}
		else if (mIsJumping)
		{
			mCurState = Player_state::Jump;
		}
		else if (KeyInput::GetKeyDown(KeyCode::C))
		{
			mCurState = Player_state::Aim;
		}
		else if (KeyInput::GetKeyDown(KeyCode::DownArrow))
		{
			mCurState = Player_state::Duck;
		}
		else if (KeyInput::GetKeyDown(KeyCode::X))
		{
			mCurState = Player_state::Shooting;
		}

		if (mPrevState == Player_state::Hit)
		{
			mAnimator->NextPlayAnim(L"CupHead_stage_anim_idle", mAnimator->GetFlipX());
		}
		else if(mCurState == Player_state::Idle && mPrevState != Player_state::Hit)
		{
			mAnimator->PlayAnim(L"CupHead_stage_anim_idle", mAnimator->GetFlipX());
		}

		mPrevState = Player_state::Idle;
	}

	void Player_stage::Aim()
	{
		if (HP <= 0)
		{
			mCurState = Player_state::Dead;
		}
		else if (mIsHit)
		{
			mCurState = Player_state::Hit;
			mAnimator->PlayAnim(L"CupHead_stage_anim_hit_ground", mAnimator->GetFlipX());
			return;
		}
		else if (mIsDash)
		{
			mCurState = Player_state::Dash;
		}
		else if (KeyInput::GetKeyUp(KeyCode::C) && (KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow)))
		{
			mCurState = Player_state::Run;
		}
		else if (KeyInput::GetKeyUp(KeyCode::C))
		{
			mCurState = Player_state::Idle;
		}
		else if (KeyInput::GetKeyDown(KeyCode::X))
		{
			if (mPrevState == Player_state::Hit && !mAnimator->GetCurAnim()->IsComplete())
			{
				if ((KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow)) && KeyInput::GetKeyDown(KeyCode::UpArrow))
				{
					mAnimator->NextPlayAnim(L"CupHead_stage_anim_shoot_diagonal_up", mAnimator->GetFlipX());
					SpawnBullet(math::Vector2(1, -1));
				}
				else if ((KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow)) && KeyInput::GetKeyDown(KeyCode::DownArrow))
				{
					mAnimator->NextPlayAnim(L"CupHead_stage_anim_shoot_diagonal_down", mAnimator->GetFlipX());
					SpawnBullet(math::Vector2(1, 1));
				}
				else if (KeyInput::GetKeyDown(KeyCode::UpArrow))
				{
					mAnimator->NextPlayAnim(L"CupHead_stage_anim_shoot_up", mAnimator->GetFlipX());
					SpawnBullet(math::Vector2(0, -1));
				}
				else if (KeyInput::GetKeyDown(KeyCode::DownArrow))
				{
					mAnimator->NextPlayAnim(L"CupHead_stage_anim_shoot_down", mAnimator->GetFlipX());
					SpawnBullet(math::Vector2(0, 1));
				}
				else
				{
					mAnimator->NextPlayAnim(L"CupHead_stage_anim_shoot_straight", mAnimator->GetFlipX());
					SpawnBullet();
				}
			}
			else
			{
				if ((KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow)) && KeyInput::GetKeyDown(KeyCode::UpArrow))
				{
					mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_diagonal_up", mAnimator->GetFlipX());
					SpawnBullet(math::Vector2(1, -1));
				}
				else if ((KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow)) && KeyInput::GetKeyDown(KeyCode::DownArrow))
				{
					mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_diagonal_down", mAnimator->GetFlipX());
					SpawnBullet(math::Vector2(1, 1));
				}
				else if (KeyInput::GetKeyDown(KeyCode::UpArrow))
				{
					mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_up", mAnimator->GetFlipX());
					SpawnBullet(math::Vector2(0, -1));
				}
				else if (KeyInput::GetKeyDown(KeyCode::DownArrow))
				{
					mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_down", mAnimator->GetFlipX());
					SpawnBullet(math::Vector2(0, 1));
				}
				else
				{
					mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_straight", mAnimator->GetFlipX());
					SpawnBullet();
				}
			}

			if(!shootSound->GetIsPlaying())
				shootSound->Play(false);
		}
		else if (mIsJumping)
		{
			mCurState = Player_state::Jump;
		}
		else
		{
			if (mPrevState == Player_state::Hit && !mAnimator->GetCurAnim()->IsComplete())
			{
				if ((KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow)) && KeyInput::GetKeyDown(KeyCode::UpArrow))
					mAnimator->NextPlayAnim(L"CupHead_stage_anim_aim_diagonal_up", mAnimator->GetFlipX());
				else if ((KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow)) && KeyInput::GetKeyDown(KeyCode::DownArrow))
					mAnimator->NextPlayAnim(L"CupHead_stage_anim_aim_diagonal_down", mAnimator->GetFlipX());
				else if (KeyInput::GetKeyDown(KeyCode::UpArrow))
					mAnimator->NextPlayAnim(L"CupHead_stage_anim_aim_up", mAnimator->GetFlipX());
				else if (KeyInput::GetKeyDown(KeyCode::DownArrow))
					mAnimator->NextPlayAnim(L"CupHead_stage_anim_aim_down", mAnimator->GetFlipX());
				else
					mAnimator->PlayAnim(L"CupHead_stage_anim_aim_straight", mAnimator->GetFlipX());
			}
			else
			{
				if ((KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow)) && KeyInput::GetKeyDown(KeyCode::UpArrow))
					mAnimator->PlayAnim(L"CupHead_stage_anim_aim_diagonal_up", mAnimator->GetFlipX());
				else if ((KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow)) && KeyInput::GetKeyDown(KeyCode::DownArrow))
					mAnimator->PlayAnim(L"CupHead_stage_anim_aim_diagonal_down", mAnimator->GetFlipX());
				else if (KeyInput::GetKeyDown(KeyCode::UpArrow))
					mAnimator->PlayAnim(L"CupHead_stage_anim_aim_up", mAnimator->GetFlipX());
				else if (KeyInput::GetKeyDown(KeyCode::DownArrow))
					mAnimator->PlayAnim(L"CupHead_stage_anim_aim_down", mAnimator->GetFlipX());
				else
					mAnimator->PlayAnim(L"CupHead_stage_anim_aim_straight", mAnimator->GetFlipX());
			}
		}

		mPrevState = Player_state::Aim;
	}

	void Player_stage::Run()
	{
		if (HP <= 0)
		{
			mCurState = Player_state::Dead;
		}
		else if (mIsHit)
		{
			mCurState = Player_state::Hit;
			mAnimator->PlayAnim(L"CupHead_stage_anim_hit_ground", mAnimator->GetFlipX());
			return;
		}
		else if (mIsDash)
		{
			mCurState = Player_state::Dash;
		}
		else if (mIsJumping)
		{
			mCurState = Player_state::Jump;
		}
		else if (KeyInput::GetKeyDown(KeyCode::DownArrow))
		{
			mCurState = Player_state::Duck;
		}
		else if (KeyInput::GetKeyDown(KeyCode::C))
		{
			mCurState = Player_state::Aim;
		}
		else if (KeyInput::GetKeyUp(KeyCode::RightArrow) && KeyInput::GetKeyUp(KeyCode::LeftArrow))
		{
			mCurState = Player_state::Idle;
		}

		if (mPrevState == Player_state::Hit && !mAnimator->GetCurAnim()->IsComplete())
		{
			if (KeyInput::GetKeyDown(KeyCode::X))
			{
				if ((KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow)) && KeyInput::GetKeyDown(KeyCode::UpArrow))
				{
					mAnimator->NextPlayAnim(L"CupHead_stage_anim_shoot_diagonal_up_run", mAnimator->GetFlipX());
					SpawnBullet(math::Vector2(1, -1));
				}
				else if (KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow))
				{
					mAnimator->NextPlayAnim(L"CupHead_stage_anim_shoot_straight_run", mAnimator->GetFlipX());
					SpawnBullet();
				}
				else
				{
					mCurState = Player_state::Shooting;
				}

				if (!shootSound->GetIsPlaying())
					shootSound->Play(false);
			}
			else
			{
				mAnimator->NextPlayAnim(L"CupHead_stage_anim_run", mAnimator->GetFlipX());
			}
			
		}
		else
		{
			if (KeyInput::GetKeyDown(KeyCode::X))
			{
				if ((KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow)) && KeyInput::GetKeyDown(KeyCode::UpArrow))
				{
					mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_diagonal_up_run", mAnimator->GetFlipX());
					SpawnBullet(math::Vector2(1, -1));
				}
				else if (KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow))
				{
					mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_straight_run", mAnimator->GetFlipX());
					SpawnBullet();
				}
				else
				{
					mCurState = Player_state::Shooting;
				}

				if (!shootSound->GetIsPlaying())
					shootSound->Play(false);
			}
			else
			{
				mAnimator->PlayAnim(L"CupHead_stage_anim_run", mAnimator->GetFlipX());
			}
		}

		mPrevState = Player_state::Run;
	}

	void Player_stage::Duck()
	{
		mCollider->SetSize(math::Vector2(COLLIDER_DUCK_SIZE_X, COLLIDER_DUCK_SIZE_Y));
		mCollider->SetOffset(math::Vector2(COLLIDER_DUCK_OFFSET_X, COLLIDER_DUCK_OFFSET_Y));

		if (HP <= 0)
		{
			mCurState = Player_state::Dead;

			mCollider->SetSize(math::Vector2(COLLIDER_DEFAULT_SIZE_X, COLLIDER_DEFAULT_SIZE_Y));
			mCollider->SetOffset(math::Vector2(COLLIDER_DEFAULT_OFFSET_X, COLLIDER_DEFAULT_OFFSET_Y));
		}
		else if (mIsHit)
		{
			mCurState = Player_state::Hit;
			mAnimator->PlayAnim(L"CupHead_stage_anim_hit_ground", mAnimator->GetFlipX());

			mCollider->SetSize(math::Vector2(COLLIDER_DEFAULT_SIZE_X, COLLIDER_DEFAULT_SIZE_Y));
			mCollider->SetOffset(math::Vector2(COLLIDER_DEFAULT_OFFSET_X, COLLIDER_DEFAULT_OFFSET_Y));
			return;
		}
		else if (mIsDash)
		{
			mCurState = Player_state::Dash;
		}
		else if (mIsJumping)
		{
			mCurState = Player_state::Jump;
		}
		else if (KeyInput::GetKeyUp(KeyCode::DownArrow))
		{
			mCurState = Player_state::Idle;

			mCollider->SetSize(math::Vector2(COLLIDER_DEFAULT_SIZE_X, COLLIDER_DEFAULT_SIZE_Y));
			mCollider->SetOffset(math::Vector2(COLLIDER_DEFAULT_OFFSET_X, COLLIDER_DEFAULT_OFFSET_Y));
		}
		else if (KeyInput::GetKeyDown(KeyCode::C))
		{
			mCurState = Player_state::Aim;

			mCollider->SetSize(math::Vector2(COLLIDER_DEFAULT_SIZE_X, COLLIDER_DEFAULT_SIZE_Y));
			mCollider->SetOffset(math::Vector2(COLLIDER_DEFAULT_OFFSET_X, COLLIDER_DEFAULT_OFFSET_Y));
		}
		else if (KeyInput::GetKeyDown(KeyCode::X))
		{
			if (mPrevState == Player_state::Hit && !mAnimator->GetCurAnim()->IsComplete())
			{
				mAnimator->NextPlayAnim(L"CupHead_stage_anim_duck_shoot", mAnimator->GetFlipX());
				SpawnBullet();
			}
			else
			{
				mAnimator->PlayAnim(L"CupHead_stage_anim_duck_shoot", mAnimator->GetFlipX());
				SpawnBullet();
			}

			if (!shootSound->GetIsPlaying())
				shootSound->Play(false);
		}
		else if (KeyInput::GetKeyUp(KeyCode::DownArrow) && (KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow)))
		{
			mCurState = Player_state::Run;

			mCollider->SetSize(math::Vector2(COLLIDER_DEFAULT_SIZE_X, COLLIDER_DEFAULT_SIZE_Y));
			mCollider->SetOffset(math::Vector2(COLLIDER_DEFAULT_OFFSET_X, COLLIDER_DEFAULT_OFFSET_Y));
		}
		else
		{
			if (mPrevState == Player_state::Hit && !mAnimator->GetCurAnim()->IsComplete())
			{
				mAnimator->NextPlayAnim(L"CupHead_stage_anim_duck_idle", mAnimator->GetFlipX());
				mPrevState = Player_state::Duck;
				return;
			}
			else
				mAnimator->PlayAnim(L"CupHead_stage_anim_duck_idle", mAnimator->GetFlipX());
		}

		mPrevState = Player_state::Duck;
	}

	void Player_stage::Shooting()
	{
		if (HP <= 0)
		{
			mCurState = Player_state::Dead;
		}
		else if (mIsHit)
		{
			mCurState = Player_state::Hit;
			mAnimator->PlayAnim(L"CupHead_stage_anim_hit_ground", mAnimator->GetFlipX());
			return;
		}
		else if (mIsDash)
		{
			mCurState = Player_state::Dash;
		}
		else if (mIsJumping)
		{
			mCurState = Player_state::Jump;
		}
		else if (KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow))
		{
			mCurState = Player_state::Run;
		}
		else if (KeyInput::GetKeyDown(KeyCode::C))
		{
			mCurState = Player_state::Aim;
		}
		else if (KeyInput::GetKeyDown(KeyCode::DownArrow))
		{
			mCurState = Player_state::Duck;
		}
		else if (KeyInput::GetKeyUp(KeyCode::X))
		{
			mCurState = Player_state::Idle;
		}

		if (mPrevState == Player_state::Hit && !mAnimator->GetCurAnim()->IsComplete())
		{
			if (KeyInput::GetKeyDown(KeyCode::UpArrow))
			{
				mAnimator->NextPlayAnim(L"CupHead_stage_anim_shoot_up", mAnimator->GetFlipX());
				SpawnBullet(math::Vector2(0, -1));
			}
			else
			{
				mAnimator->NextPlayAnim(L"CupHead_stage_anim_shoot_straight", mAnimator->GetFlipX());
				SpawnBullet();
			}

			if (!shootSound->GetIsPlaying())
				shootSound->Play(false);

			mPrevState = Player_state::Shooting;
			return;
		}
		else
		{
			if (KeyInput::GetKeyDown(KeyCode::UpArrow))
			{
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_up", mAnimator->GetFlipX());
				SpawnBullet(math::Vector2(0, -1));
			}
			else
			{
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_straight", mAnimator->GetFlipX());
				SpawnBullet();
			}

			if (!shootSound->GetIsPlaying())
				shootSound->Play(false);
		}

		mPrevState = Player_state::Shooting;
	}

	void Player_stage::Jump()
	{
		if (HP <= 0)
		{
			mCurState = Player_state::Dead;
		}
		else if (mIsHit)
		{
			mCurState = Player_state::Hit;
			mPrevState = Player_state::Jump;
			mAnimator->PlayAnim(L"CupHead_stage_anim_hit_air", mAnimator->GetFlipX());
			return;
		}
		else
		{
			if (mIsParrying)
				Parry();
			else
			{
				mAnimator->PlayAnim(L"CupHead_stage_anim_jump", mAnimator->GetFlipX());

				if (KeyInput::GetKeyDown(KeyCode::X))
				{
					SpawnBullet();
					
					if(!shootSound->GetIsPlaying())
						shootSound->Play(false);
				}
			}
		}

		if (KeyInput::GetKeyPressed(KeyCode::Z) && canParry)
		{
			canParry = false;
			mIsParrying = true;
			mParryStartTime = Time::GetTime();
		}
		else if ((KeyInput::GetKeyDown(KeyCode::Z) || mJumpMinHeight > fabs(mJumpStartHeight - mTransform->GetPos().y)) && mIsJumping)
		{
			mTransform->SetPos(math::Vector2(mTransform->GetPos().x, mTransform->GetPos().y - 700.f * Time::GetDeltaTime()));
		}
		else
			mIsJumping = false;
		
		if (mIsDash)
		{
			mCurState = Player_state::Dash;
			mIsJumping = false;
			return;
		}

		if (parrySuccess)
		{
			if ((mJumpMaxHeight - 50) <= fabs(mJumpStartHeight - mTransform->GetPos().y) || mIsGround || mPrevState == Player_state::Hit)
			{
				mIsJumping = false;
				parrySuccess = false;
			}
		}
		else
		{
			if (mJumpMaxHeight <= fabs(mJumpStartHeight - mTransform->GetPos().y) || mIsGround || mPrevState == Player_state::Hit)
			{
				mIsJumping = false;
			}

		}

		if (mIsGround || !mIsJumping)
		{
			canParry = true;

			if (KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow))
				mCurState = Player_state::Run;
			else if (KeyInput::GetKeyDown(KeyCode::C))
				mCurState = Player_state::Aim;
			else if (KeyInput::GetKeyDown(KeyCode::DownArrow))
				mCurState = Player_state::Duck;
			else if (KeyInput::GetKeyDown(KeyCode::X))
				mCurState = Player_state::Shooting;
			else
				mCurState = Player_state::Idle;
		}

		mPrevState = Player_state::Jump;
	}

	void Player_stage::Parry()
	{
		if (HP <= 0)
		{
			mCurState = Player_state::Dead;
		}
		else if (mIsHit)
		{
			mCurState = Player_state::Hit;
			mIsParrying = false;
			mAnimator->PlayAnim(L"CupHead_stage_anim_hit_air", mAnimator->GetFlipX());
			return;
		}
		else
		{
			mAnimator->PlayAnim(L"CupHead_stage_anim_parry", mAnimator->GetFlipX());
		}

		if (mIsGround || (fabs(mParryStartTime - Time::GetTime()) > mParryHoldingTime))
			mIsParrying = false;
	}

	void Player_stage::Hit()
	{
		if (mPrevState == Player_state::Duck || mPrevState == Player_state::Dash)
		{
			mCollider->SetSize(math::Vector2(COLLIDER_DEFAULT_SIZE_X, COLLIDER_DEFAULT_SIZE_Y));
			mCollider->SetOffset(math::Vector2(COLLIDER_DEFAULT_OFFSET_X, COLLIDER_DEFAULT_OFFSET_Y));
		}

		if (HP <= 0)
		{
			mCurState = Player_state::Dead;
		}

		if (mHitStartTime + mHitHoldingTime < Time::GetTime())
		{
			mIsHit = false;
		}

		if (mAnimator->GetCurAnim()->IsComplete())
		{
			if (mIsJumping)
				mCurState = Player_state::Jump;
			else if (KeyInput::GetKeyDown(KeyCode::C))
				mCurState = Player_state::Aim;
			else if (KeyInput::GetKeyDown(KeyCode::DownArrow))
				mCurState = Player_state::Duck;
			else if (KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow))
				mCurState = Player_state::Run;
			else if (KeyInput::GetKeyDown(KeyCode::X))
				mCurState = Player_state::Shooting;
			else
				mCurState = Player_state::Idle;
		}

		mPrevState = Player_state::Hit;
	}

	void Player_stage::Dash()
	{
		if (HP <= 0)
		{
			mCurState = Player_state::Dead;
		}

		if (mIsHit)
		{
			mIsDash = false;
			mCurState = Player_state::Hit;
			mPrevState = Player_state::Dash;

			if(mIsGround)
				mAnimator->PlayAnim(L"CupHead_stage_anim_hit_ground", mAnimator->GetFlipX());
			else
				mAnimator->PlayAnim(L"CupHead_stage_anim_hit_air", mAnimator->GetFlipX());

			return;
		}

		if ((fabs(mDashStartPoint - mTransform->GetPos().x) > mDashMaxDist) || !mIsDash)
		{
			mIsDash = false;

			if(mIsHit)
				mCurState = Player_state::Hit;
			else if (mIsJumping)
				mCurState = Player_state::Jump;
			else if (KeyInput::GetKeyDown(KeyCode::C))
				mCurState = Player_state::Aim;
			else if (KeyInput::GetKeyDown(KeyCode::DownArrow))
				mCurState = Player_state::Duck;
			else if (KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow))
				mCurState = Player_state::Run;
			else if (KeyInput::GetKeyDown(KeyCode::X))
				mCurState = Player_state::Shooting;
			else
				mCurState = Player_state::Idle;

			mPrevState = Player_state::Dash;

			mCollider->SetSize(math::Vector2(COLLIDER_DEFAULT_SIZE_X, COLLIDER_DEFAULT_SIZE_Y));
			mCollider->SetOffset(math::Vector2(COLLIDER_DEFAULT_OFFSET_X, COLLIDER_DEFAULT_OFFSET_Y));
		}
		else if(mIsDash)
		{
			mAnimator->PlayAnim(L"CupHead_stage_anim_dash", mDashFlip);

			math::Vector2 nPos;

			if (mDashFlip)
				nPos = math::Vector2(mTransform->GetPos().x - 700.f * Time::GetDeltaTime(), mTransform->GetPos().y);
			else
				nPos = math::Vector2(mTransform->GetPos().x + 700.f * Time::GetDeltaTime(), mTransform->GetPos().y);

			mTransform->SetPos(nPos);
		}
	}

	void Player_stage::Dead()
	{
		mAnimator->PlayAnim(L"CupHead_stage_anim_ghost");
	}

	void Player_stage::SpawnBullet(math::Vector2 dir)
	{
		if (shootPrevTime + shootDelay < Time::GetTime())
		{
			math::Vector2 comPos = mTransform->GetPos();

			if (dir.y == 1)
			{
				comPos.y += 90.f;
			}
			else if (dir.y == -1)
			{
				comPos.y -= 70.f;
			}

			if (dir.x == 0)
			{
				if (mAnimator->GetFlipX())
					comPos.x += mTransform->GetScale().x / 2;
				else
					comPos.x -= mTransform->GetScale().x / 2;
			}

			if (mCurState == Player_state::Duck)
				comPos.y += 30.f;

			if (mAnimator->GetFlipX())
			{
				comPos = math::Vector2(comPos.x - mTransform->GetScale().x / 4, comPos.y);
				//mShootAnim_L->PlayAnim(L"bullet_anim_spawn_L");
			}
			else
			{
				comPos = math::Vector2(comPos.x + mTransform->GetScale().x / 4, comPos.y);
				//mShootAnim_R->PlayAnim(L"bullet_anim_spawn_R");
			}

			Bullet* b = SceneManager::Instantiate<Bullet>(enums::eLayer::Bullet, comPos);
			b->SetDirection(dir, mAnimator->GetFlipX());
			shootPrevTime = Time::GetTime();
		}
	}
	void Player_stage::GetHit()
	{
		if (!mIsHit && (mHitStartTime + mInvincibleTime < Time::GetTime()))
		{
			mIsHit = true;
			mHitStartTime = Time::GetTime();
			HP -= 1;
			hitSound->Play(false);
			mAnimator->FlashingStart();
		}
	}
}