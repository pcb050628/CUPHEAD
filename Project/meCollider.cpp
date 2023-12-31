#include "meCollider.h"
#include "meColliderManager.h"
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
		, otherCollider(nullptr)
	{
		gobj->ColliderCountIncrease();
	}
	Collider::~Collider()
	{
		Component::SetActivate(false);

		otherCollider = nullptr;

		GetOwner()->ColliderCountDecrease();
	}
	void Collider::Init()
	{
		Component::Init();

		mPos = GetOwner()->GetComponent<Transform>()->GetPos() + mOffset;
	}
	void Collider::Update()
	{
		mPos = GetOwner()->GetComponent<Transform>()->GetPos() + mOffset;
		Camera::AffectCameraPos(mPos);
	}
	void Collider::Render(HDC hdc)
	{
	}
	void Collider::OnCollisionEnter(Collider* other)
	{
		GetOwner()->OnCollisionEnter(other);
		otherCollider = other;
		isCollision = true;
	}
	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}
	void Collider::OnCollisionExit(Collider* other)
	{
		GetOwner()->OnCollisionExit(other);
		otherCollider = nullptr;
		isCollision = false;
	}
	void Collider::SetActivate(bool value)
	{
		Component::SetActivate(value);

		/*if(otherCollider != nullptr && value == false)
			ColliderManager::ColliderCollision(this, otherCollider);*/
	}
}