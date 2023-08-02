#include "meSensor.h"

me::Sensor::Sensor(const std::wstring& name) : GameObject(name, enums::eGameObjType::sensor)
	, mCollider(nullptr)
	, TargetType(enums::eGameObjType::none)
	, mSensed(false)
{
}

me::Sensor::~Sensor()
{
}

void me::Sensor::Init()
{
	GameObject::Init();

	mCollider = AddComponent<BoxCollider>(enums::eComponentType::Collider);
}

void me::Sensor::Update()
{
	GameObject::Update();

	if (mOwner != nullptr)
	{
		GetComponent<Transform>()->SetPos(mOwner->GetComponent<Transform>()->GetPos() + mOffset);
	}
}

void me::Sensor::Render(HDC hdc)
{
	GameObject::Render(hdc);
}

void me::Sensor::OnCollisionEnter(Collider* other)
{
	if (other->GetOwner()->GetTag() == TargetType)
	{
		mSensed = true;
		SensedObj = other->GetOwner();
	}
}

void me::Sensor::OnCollisionStay(Collider* other)
{
}

void me::Sensor::OnCollisionExit(Collider* other)
{
	if (other->GetOwner()->GetTag() == TargetType)
	{
		mSensed = false;
		SensedObj = nullptr;
	}
}
