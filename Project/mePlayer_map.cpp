#include "mePlayer_map.h"
#include "COMPONENTS.h"
#include "meResourceManager.h"

namespace me
{
	Player_map::Player_map(const std::wstring& name) : GameObject(name, enums::eGameObjType::player)
		, mAnimator(nullptr)
	{
	}
	Player_map::~Player_map()
	{
	}
	void Player_map::Init()
	{
		GameObject::Init();

		AddComponent<BoxCollider>(enums::eComponentType::Collider);

		mAnimator = AddComponent<Animator>(L"CupHead_map_anim");
		mAnimator->AddAnim(*ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_front_idle", L"..\\content\\Scene\\overWorld\\Cuphead Overworld.png", math::Vector2(0, 0), 16, 4));
		mAnimator->AddAnim(*ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_back_idle", L"..\\content\\Scene\\overWorld\\Cuphead Overworld.png", math::Vector2(0, 565.625f), 16, 2));
		mAnimator->AddAnim(*ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_horizontal_idle", L"..\\content\\Scene\\overWorld\\Cuphead Overworld.png", math::Vector2(0, 339.375f), 16, 2));
		mAnimator->AddAnim(*ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_front_walk", L"..\\content\\Scene\\overWorld\\Cuphead Overworld.png", math::Vector2(412.25f, 0), 16, 12));
		mAnimator->AddAnim(*ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_diagonal_front_walk", L"..\\content\\Scene\\overWorld\\Cuphead Overworld.png", math::Vector2(309.1875f, 113.125f), 16, 12));
		mAnimator->AddAnim(*ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_horizontal_walk", L"..\\content\\Scene\\overWorld\\Cuphead Overworld.png", math::Vector2(309.1875f, 339.375f), 16, 11));
		mAnimator->AddAnim(*ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_diagonal_back_walk", L"..\\content\\Scene\\overWorld\\Cuphead Overworld.png", math::Vector2(412.25f, 452.5f), 16, 12));
		mAnimator->AddAnim(*ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_back_walk", L"..\\content\\Scene\\overWorld\\Cuphead Overworld.png", math::Vector2(0, 678.75f), 16, 13));
		mAnimator->PlayAnim(L"CupHead_map_anim_back_idle");
	}
	void Player_map::Update()
	{
		GameObject::Update();

		if (KeyInput::GetKeyDown(KeyCode::LeftArrow) && KeyInput::GetKeyUp(KeyCode::RightArrow))
			mAnimator->SetFlipX(true);
		if (KeyInput::GetKeyDown(KeyCode::RightArrow) && KeyInput::GetKeyUp(KeyCode::LeftArrow))
			mAnimator->SetFlipX(false);

		Transform* tr = GetComponent<Transform>();

		if (KeyInput::GetKey(KeyCode::UpArrow))
			tr->SetPos(math::Vector2(tr->GetPos().x, tr->GetPos().y - (100.f * Time::GetDeltaTime())));
		if (KeyInput::GetKey(KeyCode::DownArrow))					   
			tr->SetPos(math::Vector2(tr->GetPos().x, tr->GetPos().y + (100.f * Time::GetDeltaTime())));
		if (KeyInput::GetKey(KeyCode::RightArrow))
			tr->SetPos(math::Vector2(tr->GetPos().x + (100.f * Time::GetDeltaTime()), tr->GetPos().y));
		if (KeyInput::GetKey(KeyCode::LeftArrow))	   
			tr->SetPos(math::Vector2(tr->GetPos().x - (100.f * Time::GetDeltaTime()), tr->GetPos().y));

		if (KeyInput::GetKey(KeyCode::UpArrow))
		{
			if(KeyInput::GetKey(KeyCode::RightArrow) || KeyInput::GetKey(KeyCode::LeftArrow))
				mAnimator->PlayAnim(L"CupHead_map_anim_diagonal_front_walk");
			else
				mAnimator->PlayAnim(L"CupHead_map_anim_front_walk");
		}
		else if (KeyInput::GetKeyReleased(KeyCode::UpArrow))
				mAnimator->PlayAnim(L"CupHead_map_anim_front_idle");

		if (KeyInput::GetKey(KeyCode::DownArrow))
		{
			if (KeyInput::GetKey(KeyCode::RightArrow) || KeyInput::GetKey(KeyCode::LeftArrow))
				mAnimator->PlayAnim(L"CupHead_map_anim_diagonal_back_walk");
			else
				mAnimator->PlayAnim(L"CupHead_map_anim_back_walk");
		}
		else if (KeyInput::GetKeyReleased(KeyCode::DownArrow))
			mAnimator->PlayAnim(L"CupHead_map_anim_back_idle");

		if (KeyInput::GetKey(KeyCode::LeftArrow) || KeyInput::GetKey(KeyCode::RightArrow))
		{
			if (KeyInput::GetKey(KeyCode::DownArrow))
				mAnimator->PlayAnim(L"CupHead_map_anim_diagonal_back_walk");
			else if (KeyInput::GetKey(KeyCode::UpArrow))
				mAnimator->PlayAnim(L"CupHead_map_anim_diagonal_front_walk");
			else
				mAnimator->PlayAnim(L"CupHead_map_anim_horizontal_walk");
		}

		if(KeyInput::GetKeyReleased(KeyCode::RightArrow) || KeyInput::GetKeyReleased(KeyCode::LeftArrow))
			mAnimator->PlayAnim(L"CupHead_map_anim_horizontal_idle");
	}
	void Player_map::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Player_map::OnCollisionEnter(Collider* other)
	{
	}
	void Player_map::OnCollisionStay(Collider* other)
	{

	}
	void Player_map::OnCollisionExit(Collider* other)
	{
	}
}