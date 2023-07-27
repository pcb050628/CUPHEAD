#include "meCircleCollider.h"

namespace me
{
	CircleCollider::CircleCollider(GameObject* gobj, const std::wstring& name)
		: Collider(gobj, name, enums::eColliderType::Circle)
		, mVerticalRadius(20.f)
		, mHorizontalRadius(20.f)
	{
	}
	CircleCollider::~CircleCollider()
	{
	}
	void CircleCollider::Init()
	{
		Collider::Init();
	}
	void CircleCollider::Update()
	{
		Collider::Update();
	}
	void CircleCollider::Render(HDC hdc)
	{
		HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HPEN pen;
		if (GetCollision())
			pen = CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
		else
			pen = CreatePen(PS_SOLID, 0, RGB(0, 255, 0));

		HBRUSH oldB = (HBRUSH)SelectObject(hdc, brush);
		HPEN oldP = (HPEN)SelectObject(hdc, pen);

		math::Vector2 pos = GetPos();

		Ellipse(hdc
			, pos.x - mVerticalRadius
			, pos.y - mHorizontalRadius
			, pos.x + mVerticalRadius
			, pos.y + mHorizontalRadius);

		SelectObject(hdc, oldB);
		SelectObject(hdc, oldP);

		DeleteObject(brush);
		DeleteObject(pen);
	}
	void CircleCollider::OnCollisionEnter(Collider* other)
	{
		Collider::OnCollisionEnter(other);
	}
	void CircleCollider::OnCollisionStay(Collider* other)
	{
		Collider::OnCollisionStay(other);
	}
	void CircleCollider::OnCollisionExit(Collider* other)
	{
		Collider::OnCollisionExit(other);
	}
}