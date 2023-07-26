#include "meSceneManager.h"
#include "meCamera.h"
#include "COMPONENTS.h"
#include "meResourceManager.h"
#include "meTItleScene.h"
#include "meMainScene.h"
#include "meWorldMapScene.h"
#include "meGoopy_Le_Grande_Stage.h"
#include "meTexture.h"

namespace me
{
	Scene* SceneManager::mCurScene = NULL;
	std::map<std::wstring ,Scene*> SceneManager::mScenes = {};

	void SceneManager::Init()
	{
		CreateScene<TitleScene>(L"title");
		CreateScene<MainScene>(L"main");
		CreateScene<WorldMapScene>(L"overWorld");
		mCurScene = CreateScene<Goopy_Le_Grande_Stage>(L"test");
	}

	void SceneManager::Update()
	{
		mCurScene->Update();
	}

	void SceneManager::Render(HDC hdc)
	{
		mCurScene->Render(hdc);
	}

	template <typename T>
	T* SceneManager::CreateScene(std::wstring name)
	{
		Scene* tmp = new T(name);
		tmp->Init();

		mScenes.insert(std::make_pair(tmp->GetName(), tmp));

		if (mCurScene == nullptr)
			mCurScene = tmp;

		return dynamic_cast<T*>(tmp);
	}

	Scene* SceneManager::LoadScene(std::wstring name)
	{
		std::map<std::wstring, Scene*>::iterator iter =  mScenes.find(name);

		if (iter == mScenes.end())
			return nullptr;

		mCurScene->Clear();
		mCurScene = iter->second;
		mCurScene->Init();
		return iter->second;
	}
}