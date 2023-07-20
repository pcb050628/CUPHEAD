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

		AddComponent<BoxCollider>(enums::eComponentType::BoxCollider);

		mAnimator = AddComponent<Animator>(L"CupHead_stage_anim");
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_idle_R", L"..\\content\\BossFight\\Cuphead\\Idle_R\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_idle_L", L"..\\content\\BossFight\\Cuphead\\Idle_L\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_run_R", L"..\\content\\BossFight\\Cuphead\\Run\\Normal_R\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_run_L", L"..\\content\\BossFight\\Cuphead\\Run\\Normal_L\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_jump_R", L"..\\content\\BossFight\\Cuphead\\Jump\\Right\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_jump_L", L"..\\content\\BossFight\\Cuphead\\Jump\\Left\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_hit_ground", L"..\\content\\BossFight\\Cuphead\\Hit\\Ground\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_hit_air", L"..\\content\\BossFight\\Cuphead\\Hit\\Air\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_straight_R", L"..\\content\\BossFight\\Cuphead\\Shoot\\Straight_R\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_straight_L", L"..\\content\\BossFight\\Cuphead\\Shoot\\Straight_L\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_straight_run_R", L"..\\content\\BossFight\\Cuphead\\Run\\Shooting\\Straight_R\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_straight_run_L", L"..\\content\\BossFight\\Cuphead\\Run\\Shooting\\Straight_L\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_down_R", L"..\\content\\BossFight\\Cuphead\\Shoot\\Down_R\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_down_L", L"..\\content\\BossFight\\Cuphead\\Shoot\\Down_L\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_up_R", L"..\\content\\BossFight\\Cuphead\\Shoot\\Up_R\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_up_L", L"..\\content\\BossFight\\Cuphead\\Shoot\\Up_L\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_diagonal_down_R", L"..\\content\\BossFight\\Cuphead\\Shoot\\Diagonal Down_R\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_diagonal_down_L", L"..\\content\\BossFight\\Cuphead\\Shoot\\Diagonal Down_L\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_diagonal_up_R", L"..\\content\\BossFight\\Cuphead\\Shoot\\Diagonal Up_R\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_diagonal_up_L", L"..\\content\\BossFight\\Cuphead\\Shoot\\Diagonal Up_L\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_diagonal_up_run_R", L"..\\content\\BossFight\\Cuphead\\Run\\Shooting\\Diagonal Up_R\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_diagonal_up_run_L", L"..\\content\\BossFight\\Cuphead\\Run\\Shooting\\Diagonal Up_L\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_straight_R", L"..\\content\\BossFight\\Cuphead\\Aim\\Straight_R\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_straight_L", L"..\\content\\BossFight\\Cuphead\\Aim\\Straight_L\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_up_R", L"..\\content\\BossFight\\Cuphead\\Aim\\Up_R\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_up_L", L"..\\content\\BossFight\\Cuphead\\Aim\\Up_L\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_diagonal_up_R", L"..\\content\\BossFight\\Cuphead\\Aim\\Diagonal Up_R\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_diagonal_up_R", L"..\\content\\BossFight\\Cuphead\\Aim\\Diagonal Up_L\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_down_R", L"..\\content\\BossFight\\Cuphead\\Aim\\Down_R\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_down_L", L"..\\content\\BossFight\\Cuphead\\Aim\\Down_L\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_diagonal_down_R", L"..\\content\\BossFight\\Cuphead\\Aim\\Diagonal Down_R\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_diagonal_down_L", L"..\\content\\BossFight\\Cuphead\\Aim\\Diagonal Down_L\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_duck_idle_R", L"..\\content\\BossFight\\Cuphead\\Duck\\Idle_R\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_duck_idle_L", L"..\\content\\BossFight\\Cuphead\\Duck\\Idle_R\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_duck_shoot_R", L"..\\content\\BossFight\\Cuphead\\Duck\\Shoot_R\\"));
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_duck_shoot_L", L"..\\content\\BossFight\\Cuphead\\Duck\\Shoot_L\\"));
	}
	void Player_stage::Update()
	{
		GameObject::Update();

		if (KeyInput::GetKeyDown(KeyCode::RightArrow) && KeyInput::GetKeyUp(KeyCode::LeftArrow))
			mAnimator->SetFlipX(false);
		else if (KeyInput::GetKeyDown(KeyCode::LeftArrow) && KeyInput::GetKeyUp(KeyCode::RightArrow))
			mAnimator->SetFlipX(true);

		if (mState != Player_state::Aim && mState != Player_state::Duck)
		{
			Transform* tr = GetComponent<Transform>();

			if (KeyInput::GetKey(KeyCode::RightArrow))
				tr->SetPos(math::Vector2(tr->GetPos().x + 200.f * Time::GetDeltaTime(), tr->GetPos().y));

			if (KeyInput::GetKey(KeyCode::LeftArrow))
				tr->SetPos(math::Vector2(tr->GetPos().x - 200.f * Time::GetDeltaTime(), tr->GetPos().y));
		}

		switch (mState)
		{
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
		case me::Player_stage::Player_state::Jumping:
			Jumping();
			break;
		}
	}

	void Player_stage::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Player_stage::Idle()
	{
		mAnimator->PlayAnim(L"CupHead_stage_anim_idle", mAnimator->GetFlipX());

		if (KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow))
			mState = Player_state::Run;
		else if (KeyInput::GetKeyDown(KeyCode::Z))
		{
			mJumpStartHeight = GetComponent<Transform>()->GetPos().y;
			mState = Player_state::Jumping;
		}
		else if (KeyInput::GetKeyDown(KeyCode::C))
			mState = Player_state::Aim;
		else if (KeyInput::GetKeyDown(KeyCode::DownArrow))
			mState = Player_state::Duck;
		else if (KeyInput::GetKeyDown(KeyCode::X))
			mState = Player_state::Shooting;
	}

	void Player_stage::Aim()
	{
		if (KeyInput::GetKeyUp(KeyCode::C) && (KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow)))
			mState = Player_state::Run;
		else if (KeyInput::GetKeyUp(KeyCode::C))
			mState = Player_state::Idle;
		else if (KeyInput::GetKeyDown(KeyCode::X))
		{
			if ((KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow)) && KeyInput::GetKeyDown(KeyCode::UpArrow))
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_diagonal_up", mAnimator->GetFlipX());
			else if ((KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow)) && KeyInput::GetKeyDown(KeyCode::DownArrow))
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_diagonal_down", mAnimator->GetFlipX());
			else if (KeyInput::GetKeyDown(KeyCode::UpArrow))
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_up", mAnimator->GetFlipX());
			else if (KeyInput::GetKeyDown(KeyCode::DownArrow))
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_down", mAnimator->GetFlipX());
			else
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_straight", mAnimator->GetFlipX());
		}
		else if (KeyInput::GetKeyDown(KeyCode::Z))
		{
			mJumpStartHeight = GetComponent<Transform>()->GetPos().y;
			mState = Player_state::Jumping;
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

	void Player_stage::Run()
	{
		if (KeyInput::GetKeyDown(KeyCode::X))
		{
			if ((KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow)) && KeyInput::GetKeyDown(KeyCode::UpArrow))
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_diagonal_up_run", mAnimator->GetFlipX());
			else if (KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow))
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_straight_run", mAnimator->GetFlipX());
			else
				mState = Player_state::Shooting;
		}
		else
			mAnimator->PlayAnim(L"CupHead_stage_anim_run", mAnimator->GetFlipX());

		if (KeyInput::GetKeyDown(KeyCode::Z))
		{
			mJumpStartHeight = GetComponent<Transform>()->GetPos().y;
			mState = Player_state::Jumping;
		}
		else if (KeyInput::GetKeyUp(KeyCode::RightArrow) && KeyInput::GetKeyUp(KeyCode::LeftArrow))
			mState = Player_state::Idle;
	}

	void Player_stage::Duck()
	{
		if (KeyInput::GetKeyDown(KeyCode::X))
			mAnimator->PlayAnim(L"CupHead_stage_anim_duck_shoot", mAnimator->GetFlipX());
		else if (KeyInput::GetKeyDown(KeyCode::Z))
		{
			mJumpStartHeight = GetComponent<Transform>()->GetPos().y;
			mState = Player_state::Jumping;
		}
		else if (KeyInput::GetKeyDown(KeyCode::C))
			mState = Player_state::Aim;
		else if (KeyInput::GetKeyUp(KeyCode::DownArrow) && (KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow)))
			mState = Player_state::Run;
		else if (KeyInput::GetKeyUp(KeyCode::DownArrow))
			mState = Player_state::Idle;
		else
			mAnimator->PlayAnim(L"CupHead_stage_anim_duck_idle", mAnimator->GetFlipX());
	}

	void Player_stage::Shooting()
	{
		if (KeyInput::GetKeyDown(KeyCode::UpArrow))
			mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_up", mAnimator->GetFlipX());
		else
			mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_straight", mAnimator->GetFlipX());

		if(KeyInput::GetKeyDown(KeyCode::Z))
		{
			mJumpStartHeight = GetComponent<Transform>()->GetPos().y;
			mState = Player_state::Jumping;
		}
		else if (KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow))
			mState = Player_state::Run;
		else if (KeyInput::GetKeyDown(KeyCode::C))
			mState = Player_state::Aim;
		else if (KeyInput::GetKeyDown(KeyCode::DownArrow))
			mState = Player_state::Duck;
		else if (KeyInput::GetKeyUp(KeyCode::X))
			mState = Player_state::Idle;
	}

	void Player_stage::Jumping()
	{
		mAnimator->PlayAnim(L"CupHead_stage_anim_jump", mAnimator->GetFlipX());
		Transform* tr = GetComponent<Transform>();

		tr->SetPos(math::Vector2(tr->GetPos().x, tr->GetPos().y - 200.f * Time::GetDeltaTime()));

		if (KeyInput::GetKeyDown(KeyCode::X))
		{
			// shoot
		}

		if (mJumpMaxHeight <= abs(mJumpStartHeight - tr->GetPos().y))
		{
			if (KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow))
				mState = Player_state::Run;
			else if (KeyInput::GetKeyDown(KeyCode::C))
				mState = Player_state::Aim;
			else if (KeyInput::GetKeyDown(KeyCode::DownArrow))
				mState = Player_state::Duck;
			else if (KeyInput::GetKeyDown(KeyCode::X))
				mState = Player_state::Shooting;
			else
				mState = Player_state::Idle;
		}
	}
}