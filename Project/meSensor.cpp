#include "meSensor.h"

me::Sensor::Sensor(const std::wstring& name) : GameObject(name, enums::eGameObjType::sensor)
	, mCollider(nullptr)
	, mOwner(nullptr)
{
	TargetTypes = {};
	isSensed = {};
	SensedObjs = {};
}

me::Sensor::~Sensor()
{
	mOwner = nullptr;
	mCollider = nullptr;
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
	for (enums::eGameObjType type : TargetTypes)
	{
		if (other->GetOwner()->GetTag() == type)
		{
			isSensed.find(type)->second = enums::SenseType::Enter;
			SensedObjs.find(type)->second = other->GetOwner();
		}
	}
}

void me::Sensor::OnCollisionStay(Collider* other)
{
	for (enums::eGameObjType type : TargetTypes)
	{
		if (other->GetOwner()->GetTag() == type)
		{
			isSensed.find(type)->second = enums::SenseType::Stay;
			SensedObjs.find(type)->second = other->GetOwner();
		}
	}
}

void me::Sensor::OnCollisionExit(Collider* other)
{
	for (enums::eGameObjType type : TargetTypes)
	{
		if (other->GetOwner()->GetTag() == type)
		{
			isSensed.find(type)->second = enums::SenseType::none;
			SensedObjs.find(type)->second = nullptr;
		}
	}
}
