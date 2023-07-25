#include "meCollider.h"
#include "meGameObject.h"
#include "meCamera.h"

namespace me
{
	Collider::Collider(GameObject* gobj, const std::wstring& name, enums::eColliderType type)
		: Component(enums::eComponentType::Collider, gobj, name)
		, mType(type)
		, mPos(gobj->GetComponent<Transform>()->GetPos())
		, mOffset(math::Vector2::Zero)
		, isCollision(false)
	{
		gobj->ColliderCountIncrease();
	}
	Collider::~Collider()
	{
	}
	void Collider::Init()
	{
		Component::Init();
	}
	void Collider::Update()
	{
		mPos = GetOwner()->GetComponent<Transform>()->GetPos() + mOffset;
		mPos = Camera::AffectCameraPos(mPos);
	}
	void Collider::Render(HDC hdc)
	{
	}
	void Collider::OnCollisionEnter(Collider* other)
	{
		GetOwner()->OnCollisionEnter(other);
		isCollision = true;
	}
	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}
	void Collider::OnCollisionExit(Collider* other)
	{
		GetOwner()->OnCollisionExit(other);
		isCollision = false;
	}
}