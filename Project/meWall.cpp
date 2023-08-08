#include "meWall.h"
#include "meSceneManager.h"

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
	float dist = 0;
	if (other->GetType() == enums::eColliderType::Box)
	{
		dist = (other->GetOwner()->GetComponent<BoxCollider>()->GetSize().x / 2) + (GetComponent<BoxCollider>()->GetSize().x / 2);
	}
	else
	{
		dist = (other->GetOwner()->GetComponent<CircleCollider>()->GetRadius()) + (GetComponent<BoxCollider>()->GetSize().x / 2);
	}

	if (other->GetOwner()->GetComponent<Transform>()->GetPos().x < GetComponent<Transform>()->GetPos().x)
	{
		other->GetOwner()->GetComponent<Transform>()->SetPos(math::Vector2(GetComponent<Transform>()->GetPos().x - dist, other->GetOwner()->GetComponent<Transform>()->GetPos().y));
	}
	else if (other->GetOwner()->GetComponent<Transform>()->GetPos().x > GetComponent<Transform>()->GetPos().x)
	{
		other->GetOwner()->GetComponent<Transform>()->SetPos(math::Vector2(GetComponent<Transform>()->GetPos().x + dist, other->GetOwner()->GetComponent<Transform>()->GetPos().y));
	}
}

void me::Wall::OnCollisionStay(Collider* other)
{
}

void me::Wall::OnCollisionExit(Collider* other)
{
}
