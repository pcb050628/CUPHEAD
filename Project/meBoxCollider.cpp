#include "meBoxCollider.h"
#include "meColliderManager.h"
#include "meGameObject.h"
#include "meCamera.h"

namespace me
{
	BoxCollider::BoxCollider(GameObject* gobj, const std::wstring& name) 
		: Collider(gobj, name, enums::eColliderType::Box)
		, mSize(gobj->GetComponent<Transform>()->GetScale())
	{
	}
	BoxCollider::~BoxCollider()
	{
	}
	void BoxCollider::Init()
	{
		Collider::Init();
	}
	void BoxCollider::Update()
	{
		Collider::Update();
	}
	void BoxCollider::Render(HDC hdc)
	{
		if (ColliderManager::GetRender())
		{
			HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
			HPEN pen;
			if(GetCollision())
				pen = CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
			else
				pen = CreatePen(PS_SOLID, 0, RGB(0, 255, 0));

			HBRUSH oldB = (HBRUSH)SelectObject(hdc, brush);
			HPEN oldP = (HPEN)SelectObject(hdc, pen);

			math::Vector2 pos = GetPos();

			Rectangle(hdc
				, pos.x - mSize.x / 2
				, pos.y - mSize.y / 2
				, pos.x + mSize.x / 2
				, pos.y + mSize.y / 2);

			SelectObject(hdc, oldB);
			SelectObject(hdc, oldP);

			DeleteObject(brush);
			DeleteObject(pen);
		}
	}
	void BoxCollider::OnCollisionEnter(Collider* other)
	{
		Collider::OnCollisionEnter(other);
	}
	void BoxCollider::OnCollisionStay(Collider* other)
	{
		Collider::OnCollisionStay(other);
	}
	void BoxCollider::OnCollisionExit(Collider* other)
	{
		Collider::OnCollisionExit(other);
	}
}