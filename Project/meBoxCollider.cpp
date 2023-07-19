#include "meBoxCollider.h"
#include "meGameObject.h"

namespace me
{
	BoxCollider::BoxCollider(GameObject* gobj, const std::wstring& name) 
		: Component(enums::eComponentType::BoxCollider, gobj, name)
		, mPos(gobj->GetComponent<Transform>()->GetPos())
		, mScale(gobj->GetComponent<Transform>()->GetScale())
	{
	}
	BoxCollider::~BoxCollider()
	{
	}
	void BoxCollider::Init()
	{
	}
	void BoxCollider::Update()
	{
	}
	void BoxCollider::Render(HDC hdc)
	{
		HBRUSH brush = CreateSolidBrush(NULL_BRUSH);
		HPEN pen = CreatePen(PS_SOLID, 0, RGB(0, 255, 0));

		HBRUSH oldB = (HBRUSH)SelectObject(hdc, brush);
		HPEN oldP = (HPEN)SelectObject(hdc, pen);

		Rectangle(hdc
			, mPos.x - mScale.x / 2
			, mPos.y - mScale.y / 2
			, mPos.x + mScale.x / 2
			, mPos.y + mScale.y / 2);

		SelectObject(hdc, oldB);
		SelectObject(hdc, oldP);

		DeleteObject(brush);
		DeleteObject(pen);
	}
}