#include "meTransform.h"
#include "meGameObject.h"

namespace me
{
	Transform::Transform(GameObject* gobj, const std::wstring& name) : Component(enums::eComponentType::Transform, gobj, name)
	{
		mScale = math::Vector2(100, 100);
	}
	Transform::~Transform()
	{
	}

	void Transform::Init()
	{
	}

	void Transform::Update()
	{
	}

	void Transform::Render(HDC hdc)
	{
	}
}