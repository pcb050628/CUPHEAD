#include "meGameObject.h"
#include "COMPONENTS.h"

namespace me
{
	GameObject::GameObject(const std::wstring& name) : Entity(name)
		,tag()
	{
		AddComponent<Transform>(L"defaultTransform");
	}
	GameObject::~GameObject()
	{
		if (mComponents.size() > 0)
		{
			auto iter = mComponents.begin();

			for (int i = 0; i < mComponents.size(); i++, iter++)
			{
				delete iter->second;
			}
		}
		mComponents.clear();
	}

	void GameObject::Init()
	{
		auto iter = mComponents.begin();

		for (int i = 0; i < mComponents.size(); i++, iter++)
		{
			iter->second->Init();
		}
	}

	void GameObject::Update()
	{
		auto iter = mComponents.begin();

		for (int i = 0; i < mComponents.size(); i++, iter++)
		{
			if (iter->second->GetActivate())
				iter->second->Update();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		auto iter = mComponents.begin();

		for (int i = 0; i < mComponents.size(); i++, iter++)
		{
			if (iter->second->GetActivate())
				iter->second->Render(hdc);
		}
	}
}