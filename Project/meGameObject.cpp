#include "meGameObject.h"
#include "COMPONENTS.h"

namespace me
{
	GameObject::GameObject(const std::wstring& name) : Entity(name)
		,tag()
		, mColliderCount(0)
	{
		AddComponent<Transform>(L"defaultTransform");
	}
	GameObject::~GameObject()
	{
		if (mComponents.size() > 0)
		{
			for (auto comp : mComponents)
			{
				delete comp;
			}
		}
		mComponents.clear();
	}

	void GameObject::Init()
	{
		for (auto comp : mComponents)
		{
			comp->Init();
		}
	}

	void GameObject::Update()
	{
		for (auto comp : mComponents)
		{
			if (comp->GetActivate())
				comp->Update();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (auto comp : mComponents)
		{
			if (comp->GetActivate())
				comp->Render(hdc);
		}
	}

	void GameObject::OnCollisionEnter(BoxCollider* other)
	{
	}
	void GameObject::OnCollisionStay(BoxCollider* other)
	{
	}
	void GameObject::OnCollisionExit(BoxCollider* other)
	{
	}
}