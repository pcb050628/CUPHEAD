#include "mePlatform.h"
#include "meResourceManager.h"

namespace me
{
	Platform::Platform(const std::wstring& name) : GameObject(name, enums::eGameObjType::platform)
		, mTransform(nullptr)
		, mAnimator(nullptr)
	{
	}
	Platform::~Platform()
	{
		mTransform = nullptr;
		mAnimator = nullptr;
	}

	void Platform::Init()
	{
		GameObject::Init();

		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>(enums::eComponentType::Animator);

		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Platform_anim", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Platform\\Platform\\"));
		mAnimator->PlayAnim(L"Platform_anim");
	}
	void Platform::Update()
	{
		GameObject::Update();
	}
	void Platform::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Platform::OnCollisionEnter(Collider* other)
	{
	}
	void Platform::OnCollisionStay(Collider* other)
	{
	}
	void Platform::OnCollisionExit(Collider* other)
	{
	}
}