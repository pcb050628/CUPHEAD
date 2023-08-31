#include "mePauseUI.h"
#include "meResourceManager.h"

namespace me
{
	PauseUI::PauseUI(const std::wstring& name) : GameObject(name, enums::eGameObjType::ui)
		, mSpriteRenderer(nullptr)
		, selectContinue(nullptr)
		, selectRetry(nullptr)
		, selectToMap(nullptr)
	{
	}
	PauseUI::~PauseUI()
	{
		mSpriteRenderer = nullptr;
		selectContinue = nullptr;
		selectRetry = nullptr;
		selectToMap = nullptr;
	}

	void PauseUI::Init()
	{
		GameObject::Init();

		selectContinue = ResourceManager::Load<Texture>(L"pause_continue", L"..\\content\\Scene\\pause_1.bmp");
		selectRetry = ResourceManager::Load<Texture>(L"pause_continue", L"..\\content\\Scene\\pause_2.bmp");
		selectToMap = ResourceManager::Load<Texture>(L"pause_continue", L"..\\content\\Scene\\pause_3.bmp");

		mSpriteRenderer = AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
		mSpriteRenderer->SetImage(selectContinue);
	}
	void PauseUI::Update()
	{
		GameObject::Update();
	}
	void PauseUI::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void PauseUI::OnCollisionEnter(Collider* other)
	{
	}
	void PauseUI::OnCollisionStay(Collider* other)
	{
	}
	void PauseUI::OnCollisionExit(Collider* other)
	{
	}
}