#pragma once
#include "DEFAULT.h"
#include "meScene.h"

namespace me
{
	class SceneManager
	{
	public:
		static void Init();
		static void Update();
		static void Render(HDC hdc);
		static void Release();

		static Scene* GetCurScene() { return mCurScene; }

		template <typename T>
		static T* CreateScene(std::wstring name);
		static Scene* LoadScene(std::wstring name);
		static void ReLoadCurScene();
		static void Fadeout();

		template <typename T>
		static T* Instantiate(enums::eLayer layerType, math::Vector2 pos = math::Vector2::Zero, const std::wstring& name = L"object")
		{
			GameObject* gobj = mCurScene->AddGameObj<T>(layerType, name);
			gobj->GetComponent<Transform>()->SetPos(pos);
			return dynamic_cast<T*>(gobj);
		}

		template <typename T>
		static T* Instantiate(const std::wstring& sceneName, enums::eLayer layerType, math::Vector2 pos = math::Vector2::Zero, const std::wstring& name = L"object")
		{
			std::map<std::wstring, Scene*>::iterator iter = mScenes.find(sceneName);

			if (iter == mScenes.end())
				return nullptr;

			GameObject* gobj = iter->second->AddGameObj<T>(layerType, name);
			gobj->GetComponent<Transform>()->SetPos(pos);
			return dynamic_cast<T*>(gobj);
		}

		static void Destroy(GameObject* gobj)
		{
			gobj->SetState(GameObject::ObjState::Dead);
		}

	private:
		static Scene* mCurScene;
		static std::map<std::wstring, Scene*> mScenes;

		static bool loading;
		static float loadingStartTime;
		static Scene* LoadedScene;
	}; 
}

