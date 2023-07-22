#include "meBoss.h"
#include "COMPONENTS.h"
#include "meResourceManager.h"

namespace me
{
	Boss::Boss(const std::wstring& name) : GameObject(name, enums::eGameObjType::enemy)
	{
	}
	Boss::~Boss()
	{
	}
	void Boss::Init()
	{
		GameObject::Init();
	}
	void Boss::Update()
	{
		GameObject::Update();
	}
	void Boss::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}