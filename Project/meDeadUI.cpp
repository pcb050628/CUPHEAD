#include "meDeadUI.h"
#include "meSceneManager.h"
#include "meResourceManager.h"

namespace me
{
	DeadUI::DeadUI(const std::wstring& name) : GameObject(name, enums::eGameObjType::ui)
		, mSpriteRenderer(nullptr), selectRetry(nullptr), selectToMap(nullptr)
	{
	}
	DeadUI::~DeadUI()
	{
	}

	void DeadUI::Init()
	{
		GameObject::Init();

		mSpriteRenderer = AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);

		selectRetry = ResourceManager::Load<Texture>(L"deadUI_retry", L"..\\content\\Scene\\deadSceneUI_retry.bmp");
		selectToMap = ResourceManager::Load<Texture>(L"deadUI_toMap", L"..\\content\\Scene\\deadSceneUI_toMap.bmp");

		SelectRetry();
	}
	void DeadUI::Update()
	{
		GameObject::Update();

		if (KeyInput::GetKeyPressed(KeyCode::Z))
		{
			if (mSpriteRenderer->CompareImage(selectRetry))
			{
				SceneManager::ReLoadCurScene();
			}
			else
			{
				SceneManager::LoadScene(L"overWorld");
			}
		}
	}
	void DeadUI::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void DeadUI::OnCollisionEnter(Collider* other)
	{
	}
	void DeadUI::OnCollisionStay(Collider* other)
	{
	}
	void DeadUI::OnCollisionExit(Collider* other)
	{
	}
	void DeadUI::Change()
	{
		if (mSpriteRenderer->CompareImage(selectRetry))
			SelectToMap();
		else
			SelectRetry();
	}
}