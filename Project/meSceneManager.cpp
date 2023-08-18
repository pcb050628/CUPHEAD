#include "meSceneManager.h"
#include "meCamera.h"
#include "COMPONENTS.h"
#include "meResourceManager.h"
#include "meTItleScene.h"
#include "meMainScene.h"
#include "meClearScene.h"
#include "meWorldMapScene.h"
#include "meGoopy_Le_Grande_Stage.h"
#include "meRootPack_Stage.h"
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
		CreateScene<ClearScene>(L"clear");
		CreateScene<Goopy_Le_Grande_Stage>(L"slime_stage");
		CreateScene<RootPack_Stage>(L"rootpack_stage");
		CreateScene<Scene>(L"test");

<<<<<<< Updated upstream
		LoadScene(L"slime_stage");
=======
<<<<<<< HEAD
		LoadScene(L"test");
=======
		LoadScene(L"slime_stage");
>>>>>>> d47d6e14adf9a35388ac1168b84ab563491c9f4c
>>>>>>> Stashed changes
	}

	void SceneManager::Update()
	{
		mCurScene->Update();
	}

	void SceneManager::Render(HDC hdc)
	{
		mCurScene->Render(hdc);
	}

	void SceneManager::Release()
	{
		for (auto iter : mScenes)
		{
			delete iter.second;
		}

		mScenes.clear();
	}

	template <typename T>
	T* SceneManager::CreateScene(std::wstring name)
	{
		Scene* tmp = new T(name);
		mScenes.insert(std::make_pair(tmp->GetName(), tmp));
		tmp->Init();

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
		Camera::Reset();
		mCurScene = iter->second;
		return iter->second;
	}
	void SceneManager::ReLoadCurScene()
	{
		Camera::Reset();
		mCurScene->Clear();
	}
}