#include "mePlayer_stage.h"
#include "COMPONENTS.h"
#include "meSceneManager.h"
#include "meResourceManager.h"
#include "meBullet.h"

#define COLLIDER_DEFAULT_SIZE_X 100.f
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
		, HP(5)
		, shootDelay(0.1f)
		, shootPrevTime(0)
		, mAnimator(nullptr)
		, mShootAnim(nullptr)
		, mTransform(nullptr)
		, mCollider(nullptr)
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

		mCollider = AddComponent<BoxCollider>(enums::eComponentType::Collider);
		mCollider->SetSize(math::Vector2(COLLIDER_DEFAULT_SIZE_X, COLLIDER_DEFAULT_SIZE_Y));
		mCollider->SetOffset(math::Vector2(COLLIDER_DEFAULT_OFFSET_X, COLLIDER_DEFAULT_OFFSET_Y));

		mShootAnim = AddComponent<Animator>(L"bullet_spawn");
		mShootAnim->AddAnim(*ResourceManager::Load(L"bullet_anim_spawn_R", L"..\\content\\BossFight\\CupHead\\Bullet\\Spawn\\Right\\", eTextureType::png));
		mShootAnim->AddAnim(*ResourceManager::Load(L"bullet_anim_spawn_L", L"..\\content\\BossFight\\CupHead\\Bullet\\Spawn\\Left\\", eTextureType::png));

		mAnimator = AddComponent<Animator>(L"CupHead_stage_anim");
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_intro", L"..\\content\\BossFight\\Cuphead\\Intros\\Regular\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_idle_R", L"..\\content\\BossFight\\Cuphead\\Idle_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_idle_L", L"..\\content\\BossFight\\Cuphead\\Idle_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_run_R", L"..\\content\\BossFight\\Cuphead\\Run\\Normal_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_run_L", L"..\\content\\BossFight\\Cuphead\\Run\\Normal_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_jump_R", L"..\\content\\BossFight\\Cuphead\\Jump\\Right\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_jump_L", L"..\\content\\BossFight\\Cuphead\\Jump\\Left\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_hit_ground_R", L"..\\content\\BossFight\\Cuphead\\Hit\\Ground\\Right\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_hit_ground_L", L"..\\content\\BossFight\\Cuphead\\Hit\\Ground\\Left\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_hit_air_R", L"..\\content\\BossFight\\Cuphead\\Hit\\Air\\Right\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_hit_air_L", L"..\\content\\BossFight\\Cuphead\\Hit\\Air\\Left\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_straight_R", L"..\\content\\BossFight\\Cuphead\\Shoot\\Straight_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_straight_L", L"..\\content\\BossFight\\Cuphead\\Shoot\\Straight_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_straight_run_R", L"..\\content\\BossFight\\Cuphead\\Run\\Shooting\\Straight_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_straight_run_L", L"..\\content\\BossFight\\Cuphead\\Run\\Shooting\\Straight_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_down_R", L"..\\content\\BossFight\\Cuphead\\Shoot\\Down_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_down_L", L"..\\content\\BossFight\\Cuphead\\Shoot\\Down_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_up_R", L"..\\content\\BossFight\\Cuphead\\Shoot\\Up_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_up_L", L"..\\content\\BossFight\\Cuphead\\Shoot\\Up_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_diagonal_down_R", L"..\\content\\BossFight\\Cuphead\\Shoot\\Diagonal Down_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_diagonal_down_L", L"..\\content\\BossFight\\Cuphead\\Shoot\\Diagonal Down_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_diagonal_up_R", L"..\\content\\BossFight\\Cuphead\\Shoot\\Diagonal Up_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_diagonal_up_L", L"..\\content\\BossFight\\Cuphead\\Shoot\\Diagonal Up_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_diagonal_up_run_R", L"..\\content\\BossFight\\Cuphead\\Run\\Shooting\\Diagonal Up_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_shoot_diagonal_up_run_L", L"..\\content\\BossFight\\Cuphead\\Run\\Shooting\\Diagonal Up_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_straight_R", L"..\\content\\BossFight\\Cuphead\\Aim\\Straight_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_straight_L", L"..\\content\\BossFight\\Cuphead\\Aim\\Straight_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_up_R", L"..\\content\\BossFight\\Cuphead\\Aim\\Up_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_up_L", L"..\\content\\BossFight\\Cuphead\\Aim\\Up_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_diagonal_up_R", L"..\\content\\BossFight\\Cuphead\\Aim\\Diagonal Up_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_diagonal_up_L", L"..\\content\\BossFight\\Cuphead\\Aim\\Diagonal Up_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_down_R", L"..\\content\\BossFight\\Cuphead\\Aim\\Down_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_down_L", L"..\\content\\BossFight\\Cuphead\\Aim\\Down_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_diagonal_down_R", L"..\\content\\BossFight\\Cuphead\\Aim\\Diagonal Down_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_aim_diagonal_down_L", L"..\\content\\BossFight\\Cuphead\\Aim\\Diagonal Down_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_duck_idle_R", L"..\\content\\BossFight\\Cuphead\\Duck\\Idle_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_duck_idle_L", L"..\\content\\BossFight\\Cuphead\\Duck\\Idle_L\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_duck_shoot_R", L"..\\content\\BossFight\\Cuphead\\Duck\\Shoot_R\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"CupHead_stage_anim_duck_shoot_L", L"..\\content\\BossFight\\Cuphead\\Duck\\Shoot_L\\"));
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
				tr->SetPos(math::Vector2(tr->GetPos().x + 350.f * Time::GetDeltaTime(), tr->GetPos().y));

			if (KeyInput::GetKey(KeyCode::LeftArrow))
				tr->SetPos(math::Vector2(tr->GetPos().x - 350.f * Time::GetDeltaTime(), tr->GetPos().y));
		}

		if (!mIsGround&& !mIsJumping)
		{
			Transform* tr = GetComponent<Transform>();
			tr->SetPos(math::Vector2(tr->GetPos().x, tr->GetPos().y + 700.f * Time::GetDeltaTime()));
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
		case me::Player_stage::Player_state::Hit:
			Hit();
			break;
		}
	}

	void Player_stage::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Player_stage::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetTag() == enums::eGameObjType::floor)
			mIsGround = true;
	}

	void Player_stage::OnCollisionStay(Collider* other)
	{
	}

	void Player_stage::OnCollisionExit(Collider* other)
	{

	}

	void Player_stage::Idle()
	{
		mAnimator->PlayAnim(L"CupHead_stage_anim_idle", mAnimator->GetFlipX());

		if (mIsHit)
			mState = Player_state::Hit;
		else if (KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow))
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
		if (mIsHit)
			mState = Player_state::Hit;
		else if (KeyInput::GetKeyUp(KeyCode::C) && (KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow)))
			mState = Player_state::Run;
		else if (KeyInput::GetKeyUp(KeyCode::C))
			mState = Player_state::Idle;
		else if (KeyInput::GetKeyDown(KeyCode::X))
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
				SpawnBullet(math::Vector2(1, -1));
			}
			else if (KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow))
			{
				mAnimator->PlayAnim(L"CupHead_stage_anim_shoot_straight_run", mAnimator->GetFlipX());
				SpawnBullet();
			}
			else
				mState = Player_state::Shooting;
		}
		else
			mAnimator->PlayAnim(L"CupHead_stage_anim_run", mAnimator->GetFlipX());

		if (mIsHit)
			mState = Player_state::Hit;
		else if (KeyInput::GetKeyDown(KeyCode::Z))
		{
			mIsGround = false;
			mJumpStartHeight = GetComponent<Transform>()->GetPos().y;
			mState = Player_state::Jump;
			mIsJumping = true;
		}
		else if (KeyInput::GetKeyDown(KeyCode::DownArrow))
			mState = Player_state::Duck;
		else if (KeyInput::GetKeyDown(KeyCode::C))
			mState = Player_state::Aim;
		else if (KeyInput::GetKeyUp(KeyCode::RightArrow) && KeyInput::GetKeyUp(KeyCode::LeftArrow))
			mState = Player_state::Idle;
	}

	void Player_stage::Duck()
	{
		mCollider->SetSize(math::Vector2(COLLIDER_DUCK_SIZE_X, COLLIDER_DUCK_SIZE_Y));
		mCollider->SetOffset(math::Vector2(COLLIDER_DUCK_OFFSET_X, COLLIDER_DUCK_OFFSET_Y));

		if (mIsHit)
			mState = Player_state::Hit;
		else if (KeyInput::GetKeyUp(KeyCode::DownArrow))
		{
			mState = Player_state::Idle;

			mCollider->SetSize(math::Vector2(COLLIDER_DEFAULT_SIZE_X, COLLIDER_DEFAULT_SIZE_Y));
			mCollider->SetOffset(math::Vector2(COLLIDER_DEFAULT_OFFSET_X, COLLIDER_DEFAULT_OFFSET_Y));
		}
		else if (KeyInput::GetKeyDown(KeyCode::Z))
		{
			mIsGround = false;
			mJumpStartHeight = GetComponent<Transform>()->GetPos().y;
			mState = Player_state::Jump;
			mIsJumping = true;

			mCollider->SetSize(math::Vector2(COLLIDER_DEFAULT_SIZE_X, COLLIDER_DEFAULT_SIZE_Y));
			mCollider->SetOffset(math::Vector2(COLLIDER_DEFAULT_OFFSET_X, COLLIDER_DEFAULT_OFFSET_Y));
		}
		else if (KeyInput::GetKeyDown(KeyCode::C))
		{
			mState = Player_state::Aim;

			mCollider->SetSize(math::Vector2(COLLIDER_DEFAULT_SIZE_X, COLLIDER_DEFAULT_SIZE_Y));
			mCollider->SetOffset(math::Vector2(COLLIDER_DEFAULT_OFFSET_X, COLLIDER_DEFAULT_OFFSET_Y));
		}
		else if (KeyInput::GetKeyDown(KeyCode::X))
		{
			mAnimator->PlayAnim(L"CupHead_stage_anim_duck_shoot", mAnimator->GetFlipX());
			SpawnBullet();
		}
		else if (KeyInput::GetKeyUp(KeyCode::DownArrow) && (KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow)))
		{
			mState = Player_state::Run;

			mCollider->SetSize(math::Vector2(COLLIDER_DEFAULT_SIZE_X, COLLIDER_DEFAULT_SIZE_Y));
			mCollider->SetOffset(math::Vector2(COLLIDER_DEFAULT_OFFSET_X, COLLIDER_DEFAULT_OFFSET_Y));
		}
		else
			mAnimator->PlayAnim(L"CupHead_stage_anim_duck_idle", mAnimator->GetFlipX());
	}

	void Player_stage::Shooting()
	{
		if (mIsHit)
			mState = Player_state::Hit;
		else if(KeyInput::GetKeyDown(KeyCode::Z))
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
	}

	void Player_stage::Jump()
	{
		Transform* tr = GetComponent<Transform>();
		mAnimator->PlayAnim(L"CupHead_stage_anim_jump", mAnimator->GetFlipX());

		if(mIsJumping)
		{
			tr->SetPos(math::Vector2(tr->GetPos().x, tr->GetPos().y - 700.f * Time::GetDeltaTime()));
		}

		if (mJumpMaxHeight <= abs(mJumpStartHeight - tr->GetPos().y) || mIsGround)
		{
			mIsJumping = false;
		}

		if (KeyInput::GetKeyDown(KeyCode::X))
		{
			SpawnBullet();
		}

		if (mIsHit)
		{
			mAnimator->PlayAnim(L"CupHead_stage_anim_hit_air", mAnimator->GetFlipX());
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
	void Player_stage::Hit()
	{
		if(mIsGround)
			mAnimator->PlayAnim(L"CupHead_stage_anim_hit_ground", mAnimator->GetFlipX());

		if (mAnimator->GetCurAnim()->IsComplete())
		{
			if (KeyInput::GetKeyDown(KeyCode::Z))
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
			else if (KeyInput::GetKeyDown(KeyCode::RightArrow) || KeyInput::GetKeyDown(KeyCode::LeftArrow))
				mState = Player_state::Run;
			else if (KeyInput::GetKeyDown(KeyCode::X))
				mState = Player_state::Shooting;
			else
				mState = Player_state::Idle;
		}
	}

	void Player_stage::SpawnBullet(math::Vector2 dir)
	{
		if (shootPrevTime + shootDelay < Time::GetTime())
		{
			math::Vector2 comPos = mTransform->GetPos();

			if (dir.y == 1)
			{
				comPos.y += 30.f;
			}
			else if (dir.y == -1)
			{
				comPos.y -= 30.f;
			}

			if (dir.x == 0)
			{
				if (mAnimator->GetFlipX())
					comPos.x += mTransform->GetScale().x / 2;
				else
					comPos.x -= mTransform->GetScale().x / 2;
			}

			if (mAnimator->GetFlipX())
				comPos = math::Vector2(comPos.x - mTransform->GetScale().x / 4, comPos.y);
			else
				comPos = math::Vector2(comPos.x + mTransform->GetScale().x / 4, comPos.y);

			Bullet* b = SceneManager::Instantiate<Bullet>(enums::eLayer::Bullet, comPos);
			b->SetDirection(dir, mAnimator->GetFlipX());
			shootPrevTime = Time::GetTime();
		}
	}
}