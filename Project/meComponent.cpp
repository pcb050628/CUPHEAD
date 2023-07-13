#include "meComponent.h"

namespace me
{
	Component::Component(enums::eComponentType type, GameObject* gobj, const std::wstring& name) : Entity(name)
		, mType(type)
		, mOwner(gobj)
		, mActivate(true)
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