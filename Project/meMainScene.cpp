#include "meMainScene.h"
#include "COMPONENTS.h"
#include "meResourceManager.h"
#include "meSceneManager.h"

namespace me
{
	MainScene::MainScene(std::wstring name) : Scene(name)
	{
	}
	MainScene::~MainScene()
	{
	}
	void MainScene::Init()
	{
		Scene::Init();

		GameObject* main_bg = AddGameObj(enums::eLayer::Background, L"main_background", enums::eGameObjType::background);
		Texture* image_main_bg = ResourceManager::Load<Texture>(L"main_background", L"..\\content\\main screen\\Main_Menu_Background.bmp");
		main_bg->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer)->SetImage(image_main_bg);
	}
	void MainScene::Setting()
	{

	}
	void MainScene::Update()
	{
		Scene::Update();

		if (KeyInput::GetKeyDown(KeyCode::ESC))
		{
			SceneManager::LoadScene(L"title");
		}

		if (KeyInput::GetKeyDown(KeyCode::L))
		{
			SceneManager::LoadScene(L"overWorld");
		}
	}
	void MainScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void MainScene::Clear()
	{
	}
}