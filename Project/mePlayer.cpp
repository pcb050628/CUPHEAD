#include "mePlayer.h"
#include "COMPONENTS.h"
#include "meResourceManager.h"

namespace me
{
	Player::Player(const std::wstring& name) : GameObject(name)
		, mFront_sr(nullptr)
		, mBack_sr(nullptr)
		, mHorizontal_sr(nullptr)
		, mFront_anim(nullptr)
		, mBack_anim(nullptr)
		, mHorizontal_anim(nullptr)
	{
	}
	Player::~Player()
	{
	}
	void Player::Init()
	{
		GameObject::Init();
		mFront_sr = AddComponent<SpriteRenderer>(L"CupHead_map_front_sr");
		mBack_sr = AddComponent<SpriteRenderer>(L"CupHead_map_back_sr");
		mHorizontal_sr = AddComponent<SpriteRenderer>(L"CupHead_map_horizontal_sr");

		mFront_anim = AddComponent<Animator>(L"CupHead_map_front_anim");
		mBack_anim = AddComponent<Animator>(L"CupHead_map_back_anim");
		mHorizontal_anim = AddComponent<Animator>(L"CupHead_map_horizontal_anim");

		AddComponent<Controller>(enums::eComponentType::Controller);

		mFront_sr->SetActivate(false);
		mBack_sr->SetActivate(false);

		mFront_anim->SetActivate(false);
		mBack_anim->SetActivate(false);
		mHorizontal_anim->SetActivate(false);

		Texture* image = ResourceManager::Load<Texture>(L"CupHead_Map", L"..\\content\\overWorld\\Cuphead Overworld.png");
		mFront_sr->SetImage(image);
		mBack_sr->SetImage(image);
		mHorizontal_sr->SetImage(image);

		mFront_sr->SetWidth(103.0625f);
		mFront_sr->SetHeight(113.125f);

		mBack_sr->SetWidth(103.0625f);
		mBack_sr->SetHeight(113.125f);
		mBack_sr->SetStartPointY(565.625f);

		mHorizontal_sr->SetWidth(103.0625f);
		mHorizontal_sr->SetHeight(113.125f);
		mHorizontal_sr->SetStartPointY(226.25f);
	}
	void Player::Update()
	{
		GameObject::Update();

		if (KeyInput::GetKey(KeyCode::LeftArrow))
		{
			mHorizontal_anim->SetActivate(true);

			if(!mHorizontal_sr->IsFlipX())
				mHorizontal_sr->SetFlipX(true);
		}
		
		if (KeyInput::GetKey(KeyCode::RightArrow))
		{
			mHorizontal_anim->SetActivate(true);

			if(mHorizontal_sr->IsFlipX())
				mHorizontal_sr->SetFlipX(false);
		}
		
		if (KeyInput::GetKeyUp(KeyCode::RightArrow) || KeyInput::GetKeyUp(KeyCode::LeftArrow))
		{
			mHorizontal_anim->SetActivate(false);
		}
	}
	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}