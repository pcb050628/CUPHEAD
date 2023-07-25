#include "meGameObject.h"
#include "COMPONENTS.h"

namespace me
{
	GameObject::GameObject(const std::wstring& name, enums::eGameObjType type) : Entity(name)
		, type(type)
		, mColliderCount(0)
		, Activate(true)
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

	void GameObject::OnCollisionEnter(Collider* other)
	{
	}
	void GameObject::OnCollisionStay(Collider* other)
	{
	}
	void GameObject::OnCollisionExit(Collider* other)
	{
	}
}