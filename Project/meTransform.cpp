#include "meTransform.h"
#include "meGameObject.h"

namespace me
{
	Transform::Transform(GameObject* gobj) : Component(enums::eComponentType::Transform, gobj)
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