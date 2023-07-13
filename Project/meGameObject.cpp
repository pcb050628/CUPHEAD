#include "meGameObject.h"
#include "COMPONENTS.h"

namespace me
{
	GameObject::GameObject(const std::wstring& name) : Entity(name)
		,tag()
	{
		AddComponent<Transform>();
	}
	GameObject::~GameObject()
	{
		if (mComponents.size() > 0)
		{
			int idx = 0;
			while (idx < mComponents.size())
			{
				delete mComponents[idx];
				idx++;
			}
		}
		mComponents.clear();
	}

	void GameObject::Init()
	{

	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			comp->Update();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (Component* comp : mComponents)
		{
			comp->Render(hdc);
		}
	}
}