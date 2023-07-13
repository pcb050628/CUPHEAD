#include "meComponent.h"

namespace me
{
	Component::Component(enums::eComponentType type, GameObject* gobj)
		: mType(type)
		, mOwner(gobj)
	{
	}

	Component::~Component()
	{

	}

	void Component::Init()
	{
	}

	void Component::Update()
	{
	}

	void Component::Render(HDC hdc)
	{
	}
}