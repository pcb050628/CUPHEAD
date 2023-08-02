#include "meWall.h"

me::Wall::Wall(const std::wstring& name) : GameObject(name, enums::eGameObjType::wall)
	, mCollider(nullptr)
{
}

me::Wall::~Wall()
{
}

void me::Wall::Init()
{
	GameObject::Init();

	mCollider = AddComponent<BoxCollider>(enums::eComponentType::Collider);
	mCollider->SetSize(math::Vector2(100, 3000));
}

void me::Wall::Update()
{
	GameObject::Update();
}

void me::Wall::Render(HDC hdc)
{
	GameObject::Render(hdc);
}

void me::Wall::OnCollisionEnter(Collider* other)
{
}

void me::Wall::OnCollisionStay(Collider* other)
{
}

void me::Wall::OnCollisionExit(Collider* other)
{
}
