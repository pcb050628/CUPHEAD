#include "meBoxCollider.h"
#include "meGameObject.h"
#include "meCamera.h"

namespace me
{
	BoxCollider::BoxCollider(GameObject* gobj, const std::wstring& name) 
		: Component(enums::eComponentType::BoxCollider, gobj, name)
		, mPos(gobj->GetComponent<Transform>()->GetPos())
		, mOffset(math::Vector2::Zero)
		, mSize(gobj->GetComponent<Transform>()->GetScale())
	{
		gobj->ColliderCountIncrease();
	}
	BoxCollider::~BoxCollider()
	{
	}
	void BoxCollider::Init()
	{
	}
	void BoxCollider::Update()
	{
		mPos = GetOwner()->GetComponent<Transform>()->GetPos() + mOffset;
		mPos = Camera::AffectCameraPos(mPos);
	}
	void BoxCollider::Render(HDC hdc)
	{
		HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HPEN pen;
		if(isCollision)
			pen = CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
		else
			pen = CreatePen(PS_SOLID, 0, RGB(0, 255, 0));

		HBRUSH oldB = (HBRUSH)SelectObject(hdc, brush);
		HPEN oldP = (HPEN)SelectObject(hdc, pen);

		Rectangle(hdc
			, mPos.x - mSize.x / 2
			, mPos.y - mSize.y / 2
			, mPos.x + mSize.x / 2
			, mPos.y + mSize.y / 2);

		SelectObject(hdc, oldB);
		SelectObject(hdc, oldP);

		DeleteObject(brush);
		DeleteObject(pen);
	}
	void BoxCollider::OnCollisionEnter(BoxCollider* other)
	{
		GetOwner()->OnCollisionEnter(other);
		isCollision = true;
	}
	void BoxCollider::OnCollisionStay(BoxCollider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}
	void BoxCollider::OnCollisionExit(BoxCollider* other)
	{
		GetOwner()->OnCollisionExit(other);
		isCollision = false;
	}
}