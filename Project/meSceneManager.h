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

		static Scene* GetCurScene() { return mCurScene; }

		template <typename T>
		static T* CreateScene(std::wstring name);
		static Scene* LoadScene(std::wstring name);

	private:
		static Scene* mCurScene;
		static std::map<std::wstring, Scene*> mScenes;
	}; 
}

