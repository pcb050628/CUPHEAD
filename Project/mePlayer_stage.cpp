#include "mePlayer_stage.h"
#include "COMPONENTS.h"
#include "meResourceManager.h"

namespace me
{
	Player_stage::Player_stage(const std::wstring& name) : GameObject(name)
		, mAnimator(nullptr)
		, mIsAim(false)
		, mIsJumping(false)
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

		if (KeyInput::GetKey(KeyCode::LeftArrow) && KeyInput::GetKeyUp(KeyCode::RightArrow))
			mAnimator->SetFlipX(true);
		if (KeyInput::GetKey(KeyCode::RightArrow) && KeyInput::GetKeyUp(KeyCode::LeftArrow))
			mAnimator->SetFlipX(false);


		if (KeyInput::GetKeyDown(KeyCode::Z))
		{
			mIsJumping = true;
			mIsAim = false;
			mJumpStartHeight = GetComponent<Transform>()->GetPos().y;
			mAnimator->PlayAnim(L"CupHead_stage_anim_jump");
		}

		if (KeyInput::GetKey(KeyCode::X) && KeyInput::GetKey(KeyCode::UpArrow))
			mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_up");
		else if(KeyInput::GetKey(KeyCode::X) && mIsDuck)
			mAnimator->PlayAnim(L"CupHead_stage_anim_duck_shoot");
		else if(KeyInput::GetKey(KeyCode::X))
			mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_straight");

		if (!mIsJumping)
		{
			if (KeyInput::GetKeyDown(KeyCode::C))
				mIsAim = true;

			if (KeyInput::GetKeyDown(KeyCode::DownArrow))
			{
				mAnimator->PlayAnim(L"CupHead_stage_anim_duck_down");
				mAnimator->NextPlayAnim(L"CupHead_stage_anim_duck_idle");
				mIsDuck = true;
			}
			else if (KeyInput::GetKeyUp(KeyCode::DownArrow))
				mIsDuck = false;

			if(!mIsDuck && !mIsAim)
			{
				if (KeyInput::GetKey(KeyCode::LeftArrow) || KeyInput::GetKey(KeyCode::RightArrow))
				{
					if(KeyInput::GetKey(KeyCode::UpArrow) && KeyInput::GetKey(KeyCode::X))
						mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_diagonal_run");
					else if (KeyInput::GetKey(KeyCode::X))
						mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_straight_run");
					else
						mAnimator->PlayAnim(L"CupHead_stage_anim_run");
				}
			}

			if(KeyInput::IsAllKeyUp())
				mAnimator->PlayAnim(L"CupHead_stage_anim_idle");
		}
		else if (mIsAim)
		{
			if (KeyInput::GetKeyUp(KeyCode::C))
				mIsAim = false;
		}
		else if(mIsJumping)
		{
			Transform* tr = GetComponent<Transform>();

			if (tr->GetPos().y <= mJumpStartHeight + -mJumpMaxHeight)
			{
				mIsJumping = false;
			}
			else
			{
				tr->SetPos(tr->GetPos() + math::Vector2(0.f, -100.f * Time::GetDeltaTime()));
			}
		}
	}
	void Player_stage::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}