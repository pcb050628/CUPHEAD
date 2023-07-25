#include "mePlayer_stage.h"
#include "COMPONENTS.h"
#include "meSceneManager.h"
#include "meResourceManager.h"
#include "meBullet.h"

namespace me
{
	Player_stage::Player_stage(const std::wstring& name) : GameObject(name, enums::eGameObjType::player)
		, HP(5)
		, shootDelay(0.2f)
		, shootPrevTime(0)
		, mAnimator(nullptr)
		, mState(Player_state::Idle)
		, mIsGround(false)
		, mIsJumping(false)
		, mJumpStartHeight(0)
		, mJumpMaxHeight(300.f)

	{

	}
	Player_stage::~Player_stage()
	{
	}
	void Player_stage::Init()
	{
		GameObject::Init();

		mTransform = GetComponent<Transform>();

		BoxCollider* collider = AddComponent<BoxCollider>(enums::eComponentType::BoxCollider);
		collider->SetSize(collider->GetSize() + math::Vector2(0, 30));
		collider->SetOffset(math::Vector2(0, 10.f));

		mAnimator = AddComponent<Animator>(L"CupHead_stage_anim");
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_intro", L"..\\content\\BossFight\\Cuphead\\Intros\\Regular\\"));
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
		mAnimator->AddAnim(ResourceManager::Load<Animation>(L"CupHead_stage_anim_duck_idle_L", L"..\\content\\BossFight\\Cuphead\\Duck\\Idle_L\\"));
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

		if (!mIsGround&& !mIsJumping)
		{
			Transform* tr = GetComponent<Transform>();
			tr->SetPos(math::Vector2(tr->GetPos().x, tr->GetPos().y + 500.f * Time::GetDeltaTime()));
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
		case me::Player_stage::Player_state::Jump:
			Jump();
			break;
		}
	}

	void Player_stage::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Player_stage::OnCollisionEnter(BoxCollider* other)
	{
		if (other->GetOwner()->GetTag() == enums::eGameObjType::floor)
			mIsGround = true;
	}

	void Player_stage::OnCollisionStay(BoxCollider* other)
	{
	}

	void Player_stage::OnCollisionExit(BoxCollider* other)
	{

	}

	void Player_stage::Idle()
	{
		mAnimator->PlayAnim(L"CupHead_stage_anim_idle", mAnimator->GetFlipX());

		if (KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow))
			mState = Player_state::Run;
		else if (KeyInput::GetKeyDown(KeyCode::Z))
		{
			mIsGround = false;
			mJumpStartHeight = GetComponent<Transform>()->GetPos().y;
			mState = Player_state::Jump;
			mIsJumping = true;
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
			{
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_diagonal_up", mAnimator->GetFlipX());
				SpawnBullet(mTransform->GetPos(), math::Vector2(1, -1));
			}
			else if ((KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow)) && KeyInput::GetKeyDown(KeyCode::DownArrow))
			{
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_diagonal_down", mAnimator->GetFlipX());
				SpawnBullet(mTransform->GetPos(), math::Vector2(1, 1));
			}
			else if (KeyInput::GetKeyDown(KeyCode::UpArrow))
			{
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_up", mAnimator->GetFlipX());
				SpawnBullet(mTransform->GetPos(), math::Vector2(0, -1));
			}
			else if (KeyInput::GetKeyDown(KeyCode::DownArrow))
			{
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_down", mAnimator->GetFlipX());
				SpawnBullet(mTransform->GetPos(), math::Vector2(0, 1));
			}
			else
			{
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_straight", mAnimator->GetFlipX());
				SpawnBullet(mTransform->GetPos());
			}
		}
		else if (KeyInput::GetKeyDown(KeyCode::Z))
		{
			mIsGround = false;
			mJumpStartHeight = GetComponent<Transform>()->GetPos().y;
			mState = Player_state::Jump;
			mIsJumping = true;
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
			{
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_diagonal_up_run", mAnimator->GetFlipX());
				SpawnBullet(mTransform->GetPos(), math::Vector2(1, -1));
			}
			else if (KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow))
			{
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_straight_run", mAnimator->GetFlipX());
				SpawnBullet(mTransform->GetPos());
			}
			else
				mState = Player_state::Shooting;
		}
		else
			mAnimator->PlayAnim(L"CupHead_stage_anim_run", mAnimator->GetFlipX());

		if (KeyInput::GetKeyDown(KeyCode::Z))
		{
			mIsGround = false;
			mJumpStartHeight = GetComponent<Transform>()->GetPos().y;
			mState = Player_state::Jump;
			mIsJumping = true;
		}
		else if (KeyInput::GetKeyDown(KeyCode::DownArrow))
			mState = Player_state::Duck;
		else if (KeyInput::GetKeyUp(KeyCode::RightArrow) && KeyInput::GetKeyUp(KeyCode::LeftArrow))
			mState = Player_state::Idle;
	}

	void Player_stage::Duck()
	{
		if (KeyInput::GetKeyUp(KeyCode::DownArrow))
			mState = Player_state::Idle;
		else if (KeyInput::GetKeyDown(KeyCode::C))
			mState = Player_state::Aim;
		else if (KeyInput::GetKeyDown(KeyCode::X))
		{
			mAnimator->PlayAnim(L"CupHead_stage_anim_duck_shoot", mAnimator->GetFlipX());
			SpawnBullet(mTransform->GetPos() + math::Vector2(0, 20.f));
		}
		else if (KeyInput::GetKeyDown(KeyCode::Z))
		{
			mIsGround = false;
			mJumpStartHeight = GetComponent<Transform>()->GetPos().y;
			mState = Player_state::Jump;
			mIsJumping = true;
		}
		else if (KeyInput::GetKeyUp(KeyCode::DownArrow) && (KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow)))
			mState = Player_state::Run;
		else
			mAnimator->PlayAnim(L"CupHead_stage_anim_duck_idle", mAnimator->GetFlipX());
	}

	void Player_stage::Shooting()
	{
		if (KeyInput::GetKeyDown(KeyCode::UpArrow))
		{
			mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_up", mAnimator->GetFlipX());
			SpawnBullet(mTransform->GetPos(), math::Vector2(0, -1));
		}
		else
		{
			mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_straight", mAnimator->GetFlipX());
			SpawnBullet(mTransform->GetPos());
		}

		if(KeyInput::GetKeyDown(KeyCode::Z))
		{
			mIsGround = false;
			mJumpStartHeight = GetComponent<Transform>()->GetPos().y;
			mState = Player_state::Jump;
			mIsJumping = true;
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

	void Player_stage::Jump()
	{
		Transform* tr = GetComponent<Transform>();
		mAnimator->PlayAnim(L"CupHead_stage_anim_jump", mAnimator->GetFlipX());

		if(mIsJumping)
		{
			tr->SetPos(math::Vector2(tr->GetPos().x, tr->GetPos().y - 500.f * Time::GetDeltaTime()));
		}

		if (mJumpMaxHeight <= abs(mJumpStartHeight - tr->GetPos().y) || mIsGround)
		{
			mIsJumping = false;
		}

		if (KeyInput::GetKeyDown(KeyCode::X))
		{
			SpawnBullet(mTransform->GetPos());
		}

		if (mIsGround)
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
	void Player_stage::SpawnBullet(math::Vector2 pos, math::Vector2 dir)
	{
		if (shootPrevTime + shootDelay < Time::GetTime())
		{
			Bullet* b = SceneManager::Instantiate<Bullet>(enums::eLayer::Bullet, pos);
			b->SetDirection(dir);
			b->SetFlip(GetComponent<Animator>()->GetFlipX());
			shootPrevTime = Time::GetTime();
		}
	}
}