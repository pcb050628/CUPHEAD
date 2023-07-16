#include "mePlayer_map.h"
#include "COMPONENTS.h"
#include "meResourceManager.h"

namespace me
{
	Player_map::Player_map(const std::wstring& name) : GameObject(name)
		, mAnimator(nullptr)
	{
	}
	Player_map::~Player_map()
	{
	}
	void Player_map::Init()
	{
		GameObject::Init();
		AddComponent<Controller>(enums::eComponentType::Controller)->SetType(enums::eControlType::map);

		mAnimator = AddComponent<Animator>(L"CupHead_map_anim");
		mAnimator->AddAnim(ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_front_idle", L"..\\content\\overWorld\\Cuphead Overworld.png", math::Vector2(0, 0), 16, 4));
		mAnimator->AddAnim(ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_back_idle", L"..\\content\\overWorld\\Cuphead Overworld.png", math::Vector2(0, 565.625f), 16, 2));
		mAnimator->AddAnim(ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_horizontal_idle", L"..\\content\\overWorld\\Cuphead Overworld.png", math::Vector2(0, 339.375f), 16, 2));
		mAnimator->AddAnim(ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_front_walk", L"..\\content\\overWorld\\Cuphead Overworld.png", math::Vector2(412.25f, 0), 16, 12));
		mAnimator->AddAnim(ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_diagonal_front_walk", L"..\\content\\overWorld\\Cuphead Overworld.png", math::Vector2(309.1875f, 113.125f), 16, 12));
		mAnimator->AddAnim(ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_horizontal_walk", L"..\\content\\overWorld\\Cuphead Overworld.png", math::Vector2(309.1875f, 339.375f), 16, 11));
		mAnimator->AddAnim(ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_diagonal_back_walk", L"..\\content\\overWorld\\Cuphead Overworld.png", math::Vector2(412.25f, 452.5f), 16, 12));
		mAnimator->AddAnim(ResourceManager::Load(L"CupHead_map_anim", L"CupHead_map_anim_back_walk", L"..\\content\\overWorld\\Cuphead Overworld.png", math::Vector2(0, 678.75f), 16, 13));
		mAnimator->PlayAnim(L"CupHead_map_anim_back_idle");
	}
	void Player_map::Update()
	{
		GameObject::Update();

		if (KeyInput::GetKeyDown(KeyCode::LeftArrow))
			mAnimator->SetFlipX(true);
		if (KeyInput::GetKeyDown(KeyCode::RightArrow))
			mAnimator->SetFlipX(false);

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
}