#include "mePlayer_stage.h"
#include "COMPONENTS.h"
#include "meResourceManager.h"

namespace me
{
	Player_stage::Player_stage(const std::wstring& name) : GameObject(name)
		, mAnimator(nullptr)
		, mState(Player_state::Idle)
		, mIsAim(false)
		, mIsRun(false)
		, mIsDuck(false)
		, mIsShooting(false)
		, mIsJumping(false)
		, mIsLookUp(false)
		, mIsLookDiagonalUp(false)
		, mIsLookDown(false)
		, mIsLookDiagonalDown(false)
		, mJumpStartHeight(0)
		, mJumpMaxHeight(100.f)

	{

	}
	Player_stage::~Player_stage()
	{
	}
	void Player_stage::Init()
	{
		GameObject::Init();

		AddComponent<Controller>(enums::eComponentType::Controller)->SetType(enums::eControlType::stage);
		AddComponent<BoxCollider>(enums::eComponentType::BoxCollider);

		mAnimator = AddComponent<Animator>(L"CupHead_stage_anim");
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_idle", L"..\\content\\BossFight\\Cuphead\\Idle\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_run", L"..\\content\\BossFight\\Cuphead\\Run\\Normal\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_jump", L"..\\content\\BossFight\\Cuphead\\Jump\\Cuphead\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_hit_ground", L"..\\content\\BossFight\\Cuphead\\Hit\\Ground\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_hit_air", L"..\\content\\BossFight\\Cuphead\\Hit\\Air\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_straight", L"..\\content\\BossFight\\Cuphead\\Shoot\\Straight\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_straight_run", L"..\\content\\BossFight\\Cuphead\\Run\\Shooting\\Straight\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_down", L"..\\content\\BossFight\\Cuphead\\Shoot\\Down\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_up", L"..\\content\\BossFight\\Cuphead\\Shoot\\Up\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_diagonal_down", L"..\\content\\BossFight\\Cuphead\\Shoot\\Diagonal Down\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_diagonal_up", L"..\\content\\BossFight\\Cuphead\\Shoot\\Diagonal Up\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_diagonal_run", L"..\\content\\BossFight\\Cuphead\\Run\\Shooting\\Diagonal Up\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_straight", L"..\\content\\BossFight\\Cuphead\\Aim\\Straight\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_up", L"..\\content\\BossFight\\Cuphead\\Aim\\Up\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_diagonal_up", L"..\\content\\BossFight\\Cuphead\\Aim\\Diagonal Up\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_down", L"..\\content\\BossFight\\Cuphead\\Aim\\Down\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_diagonal_down", L"..\\content\\BossFight\\Cuphead\\Aim\\Diagonal Down\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_duck_down", L"..\\content\\BossFight\\Cuphead\\Duck\\Down\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_duck_idle", L"..\\content\\BossFight\\Cuphead\\Duck\\Idle\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_duck_shoot", L"..\\content\\BossFight\\Cuphead\\Duck\\Shoot\\"));
		mAnimator->GetAnim(L"CupHead_stage_anim_run")->SetDuration(0.05f);
		mAnimator->GetAnim(L"CupHead_stage_anim_jump")->SetDuration(0.05f);
		mAnimator->GetAnim(L"CupHead_stage_anim_shoot_straight_run")->SetDuration(0.05f);
		mAnimator->GetAnim(L"CupHead_stage_anim_shoot_diagonal_run")->SetDuration(0.05f);
		mAnimator->GetAnim(L"CupHead_stage_anim_duck_down")->SetDuration(0.05f);
		mAnimator->GetAnim(L"CupHead_stage_anim_duck_down")->SetLoop(false);
	}
	void Player_stage::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case me::Player_stage::Player_state::Idle:
			break;
		case me::Player_stage::Player_state::Aim:
			break;
		case me::Player_stage::Player_state::Run:
			break;
		case me::Player_stage::Player_state::Duck:
			break;
		case me::Player_stage::Player_state::Shooting:
			break;
		case me::Player_stage::Player_state::Jumping:
			break;
		}

		if (KeyInput::GetKey(KeyCode::LeftArrow) && KeyInput::GetKeyUp(KeyCode::RightArrow))
		{
			mAnimator->SetFlipX(true);
			mIsRun = true;
			if (KeyInput::GetKeyDown(KeyCode::UpArrow))
				mIsLookDiagonalUp = true;
			if (KeyInput::GetKeyDown(KeyCode::DownArrow))
				mIsLookDiagonalDown = true;
		}
		if (KeyInput::GetKey(KeyCode::RightArrow) && KeyInput::GetKeyUp(KeyCode::LeftArrow))
		{
			mAnimator->SetFlipX(false);
			mIsRun = true;
			if (KeyInput::GetKeyDown(KeyCode::UpArrow))
				mIsLookDiagonalUp = true;
			if (KeyInput::GetKeyDown(KeyCode::DownArrow))
				mIsLookDiagonalDown = true;
		}
		if (KeyInput::GetKeyDown(KeyCode::Z))
		{
			mIsJumping = true;
			mIsAim = false;
			mJumpStartHeight = GetComponent<Transform>()->GetPos().y;
		}
		if (KeyInput::GetKeyDown(KeyCode::X))
			mIsShooting = true;
		if (KeyInput::GetKeyPressed(KeyCode::DownArrow))
		{
			mIsDuck = true;
			mAnimator->PlayAnim(L"CupHead_stage_anim_duck_down");
		}
		if (KeyInput::GetKeyDown(KeyCode::C))
			mIsAim = true;
		if (KeyInput::GetKeyDown(KeyCode::UpArrow))
			mIsLookUp = true;
		if (mIsAim && KeyInput::GetKeyDown(KeyCode::DownArrow))
			mIsLookDown = true;

		if (KeyInput::GetKeyUp(KeyCode::X))
			mIsShooting = false;
		if (KeyInput::GetKeyUp(KeyCode::DownArrow))
		{
			mIsDuck = false;
			mIsLookDown = false;
			mIsLookDiagonalDown = false;
		}
		if (KeyInput::GetKeyUp(KeyCode::RightArrow) && KeyInput::GetKeyUp(KeyCode::LeftArrow))
		{
			mIsRun = false;
			mIsLookDiagonalUp = false;
			mIsLookDiagonalDown = false;
		}
		if (KeyInput::GetKeyUp(KeyCode::UpArrow))
		{
			mIsLookUp = false;
			mIsLookDiagonalUp = false;
		}
		if (KeyInput::GetKeyUp(KeyCode::C))
		{
			mIsAim = false;
			mIsLookDown = false;
			mIsLookDiagonalDown = false;
		}

		if (!mIsAim && !mIsDuck && !mIsJumping && !mIsRun && !mIsShooting && !mIsLookUp)
			mAnimator->PlayAnim(L"CupHead_stage_anim_idle");
		else if (mIsJumping)
		{
			mAnimator->PlayAnim(L"CupHead_stage_anim_jump");

			Transform* tr = GetComponent<Transform>();
			tr->SetPos(tr->GetPos() + math::Vector2(0, -200.f * Time::GetDeltaTime()));

			if (tr->GetPos().y <= mJumpStartHeight - 100.f)
				mIsJumping = false;
		}
		else if (mIsAim)
		{
			if (mIsShooting && mIsLookDiagonalUp)
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_diagonal_up");
			else if (mIsShooting && mIsLookDiagonalDown)
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_diagonal_down");
			else if (mIsShooting && mIsLookUp)
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_up");
			else if (mIsShooting && mIsLookDown)
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_down");
			else if (mIsShooting)
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_straight");
			else if (mIsLookDiagonalUp)
				mAnimator->PlayAnim(L"CupHead_stage_anim_aim_diagonal_up");
			else if (mIsLookDiagonalDown)
				mAnimator->PlayAnim(L"CupHead_stage_anim_aim_diagonal_down");
			else if (mIsLookUp)
				mAnimator->PlayAnim(L"CupHead_stage_anim_aim_up");
			else if (mIsLookDown)
				mAnimator->PlayAnim(L"CupHead_stage_anim_aim_down");
			else
				mAnimator->PlayAnim(L"CupHead_stage_anim_aim_straight");
		}
		else if (mIsDuck)
		{
			if (mIsShooting)
				mAnimator->PlayAnim(L"CupHead_stage_anim_duck_shoot");
			else
				mAnimator->PlayAnim(L"CupHead_stage_anim_duck_idle");
		}
		else if (mIsRun)
		{
			if (mIsRun && mIsShooting && mIsLookDiagonalUp)
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_diagonal_run");
			else if (mIsRun && mIsShooting)
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_straight_run");
			else
				mAnimator->PlayAnim(L"CupHead_stage_anim_run");
		}
		else if (mIsLookUp)
		{
			if (mIsShooting)
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_up");
			else if (!mIsRun && !mIsDuck)
				mAnimator->PlayAnim(L"CupHead_stage_anim_aim_up");
		}
		else if (mIsShooting)
		{
			if(mIsDuck)
				mAnimator->PlayAnim(L"CupHead_stage_anim_duck_shoot");
			else if (mIsRun && mIsShooting)
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_straight_run");
			else if (mIsRun && mIsShooting && mIsLookDiagonalUp)
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_diagonal_up");
			else if (mIsRun && mIsShooting && mIsLookUp)
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_up");
			else if (mIsRun && mIsShooting && mIsLookDown)
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_down");
			else if (mIsRun && mIsShooting && mIsLookDiagonalDown)
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_diagonal_down");
			else if (mIsAim && mIsShooting && mIsLookDiagonalUp)
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_diagonal_up");
			else if (mIsAim && mIsShooting && mIsLookUp)
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_up");
			else if (mIsAim && mIsShooting && mIsLookDown)
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_down");
			else if (mIsAim && mIsShooting && mIsLookDiagonalDown)
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_diagonal_down");
			else			
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_straight");
		}
	}
	void Player_stage::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Player_stage::Idle()
	{
	}
	void Player_stage::Aim()
	{
	}
	void Player_stage::Run()
	{
		
	}
	void Player_stage::Duck()
	{
	}
	void Player_stage::Shooting()
	{
	}
	void Player_stage::Jumping()
	{
	}
}