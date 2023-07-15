#include "mePlayer_map.h"
#include "COMPONENTS.h"
#include "meResourceManager.h"

namespace me
{
	Player_map::Player_map(const std::wstring& name) : GameObject(name)
		, mFront_sr(nullptr)
		, mBack_sr(nullptr)
		, mHorizontal_sr(nullptr)
		, mAnimtor(nullptr)
	{
	}
	Player_map::~Player_map()
	{
	}
	void Player_map::Init()
	{
		GameObject::Init();

		mAnimtor = AddComponent<Animator>(L"CupHead_map_anim");
		mAnimtor->AddAnim(ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_front_idle", L"..\\content\\overWorld\\Cuphead Overworld.png", math::Vector2(0, 0), 16, 4, 5.f));
		mAnimtor->AddAnim(ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_back_idle", L"..\\content\\overWorld\\Cuphead Overworld.png", math::Vector2(0, 565.625f), 16, 2));
		mAnimtor->AddAnim(ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_horizontal_idle", L"..\\content\\overWorld\\Cuphead Overworld.png", math::Vector2(0, 339.375f), 16, 2));
		mAnimtor->AddAnim(ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_front_walk", L"..\\content\\overWorld\\Cuphead Overworld.png", math::Vector2(412.25f, 0), 16, 12, 2.f));
		mAnimtor->AddAnim(ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_diagonal_front_walk", L"..\\content\\overWorld\\Cuphead Overworld.png", math::Vector2(309.1875f, 113.125f), 16, 12));
		mAnimtor->AddAnim(ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_horizontal_walk", L"..\\content\\overWorld\\Cuphead Overworld.png", math::Vector2(309.1875f, 339.375f), 16, 11));
		mAnimtor->AddAnim(ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_diagonal_back_walk", L"..\\content\\overWorld\\Cuphead Overworld.png", math::Vector2(412.25f, 452.5f), 16, 12));
		mAnimtor->AddAnim(ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_back_walk", L"..\\content\\overWorld\\Cuphead Overworld.png", math::Vector2(0, 678.75f), 16, 13));
		mAnimtor->PlayAnim(L"CupHead_map_anim_back_idle");
		AddComponent<Controller>(enums::eComponentType::Controller);
	}
	void Player_map::Update()
	{
		GameObject::Update();

		if (KeyInput::GetKeyDown(KeyCode::LeftArrow))
			mAnimtor->SetFlipX(true);
		if (KeyInput::GetKeyDown(KeyCode::RightArrow))
			mAnimtor->SetFlipX(false);

		if (KeyInput::GetKey(KeyCode::UpArrow))
		{
			if(KeyInput::GetKey(KeyCode::RightArrow) || KeyInput::GetKey(KeyCode::LeftArrow))
				mAnimtor->PlayAnim(L"CupHead_map_anim_diagonal_front_walk");
			else
				mAnimtor->PlayAnim(L"CupHead_map_anim_front_walk");
		}
		else if (KeyInput::GetKeyReleased(KeyCode::UpArrow))
				mAnimtor->PlayAnim(L"CupHead_map_anim_front_idle");

		if (KeyInput::GetKey(KeyCode::DownArrow))
		{
			if (KeyInput::GetKey(KeyCode::RightArrow) || KeyInput::GetKey(KeyCode::LeftArrow))
				mAnimtor->PlayAnim(L"CupHead_map_anim_diagonal_back_walk");
			else
				mAnimtor->PlayAnim(L"CupHead_map_anim_back_walk");
		}
		else if (KeyInput::GetKeyReleased(KeyCode::DownArrow))
			mAnimtor->PlayAnim(L"CupHead_map_anim_back_idle");

		if (KeyInput::GetKey(KeyCode::LeftArrow) || KeyInput::GetKey(KeyCode::RightArrow))
		{
			if (KeyInput::GetKey(KeyCode::DownArrow))
				mAnimtor->PlayAnim(L"CupHead_map_anim_diagonal_back_walk");
			else if (KeyInput::GetKey(KeyCode::UpArrow))
				mAnimtor->PlayAnim(L"CupHead_map_anim_diagonal_front_walk");
			else
				mAnimtor->PlayAnim(L"CupHead_map_anim_horizontal_walk");
		}

		if(KeyInput::GetKeyReleased(KeyCode::RightArrow) || KeyInput::GetKeyReleased(KeyCode::LeftArrow))
			mAnimtor->PlayAnim(L"CupHead_map_anim_horizontal_idle");
	}
	void Player_map::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}