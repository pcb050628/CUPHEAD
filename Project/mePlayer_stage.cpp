#include "mePlayer_stage.h"
#include "COMPONENTS.h"
#include "meResourceManager.h"

namespace me
{
	Player_stage::Player_stage(const std::wstring& name) : GameObject(name)
	{
	}
	Player_stage::~Player_stage()
	{
	}
	void Player_stage::Init()
	{
		GameObject::Init();
	}
	void Player_stage::Update()
	{
		GameObject::Update();
	}
	void Player_stage::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}