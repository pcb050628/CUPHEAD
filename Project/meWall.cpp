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
	mCollider->SetSize(math::Vector2(100, 1000));
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

	Transform* mTransform = this->GetComponent<Transform>();
	Transform* otherTransform = other->GetOwner()->GetComponent<Transform>();

	if (other->GetType() == enums::eColliderType::Box)
	{
		dist = (dynamic_cast<BoxCollider*>(other)->GetSize().x / 2) + (GetComponent<BoxCollider>()->GetSize().x / 2);
	}
	else
	{
		dist = (dynamic_cast<CircleCollider*>(other)->GetRadius()) + (GetComponent<BoxCollider>()->GetSize().x / 2);
	}

	if (otherTransform->GetPos().x < mTransform->GetPos().x)
	{
		otherTransform->SetPos(math::Vector2(mTransform->GetPos().x - dist, otherTransform->GetPos().y));
	}
	else if (otherTransform->GetPos().x > mTransform->GetPos().x)
	{
		otherTransform->SetPos(math::Vector2(mTransform->GetPos().x + dist, otherTransform->GetPos().y));
	}
}

void me::Wall::OnCollisionStay(Collider* other)
{
}

void me::Wall::OnCollisionExit(Collider* other)
{
}
