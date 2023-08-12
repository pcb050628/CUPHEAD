#include "meMainScene.h"
#include "COMPONENTS.h"
#include "meResourceManager.h"
#include "meSceneManager.h"

namespace me
{
	MainScene::MainScene(std::wstring name) : Scene(name)
		, smileAnim(nullptr)
		, smileSprite(nullptr)
		, loadMap(false)
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

		GameObject* select_main_bg = AddGameObj(enums::eLayer::Background, L"select_main", enums::eGameObjType::background);
		Texture* image_select_main_bg = ResourceManager::Load<Texture>(L"select_main", L"..\\content\\main screen\\selectPageBG.bmp");
		select_main_bg->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer)->SetImage(image_select_main_bg);

		GameObject* select_red_bg = AddGameObj(enums::eLayer::Background, L"select_red", enums::eGameObjType::background);
		Texture* image_select_red_bg = ResourceManager::Load<Texture>(L"select_red", L"..\\content\\main screen\\selectPageBG_2.bmp");
		select_red_bg->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer)->SetImage(image_select_red_bg);

		GameObject* select_smile = AddGameObj(enums::eLayer::Background, L"select_red", enums::eGameObjType::background);

		smileSprite = select_smile->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
		smileSprite->SetImage(ResourceManager::Load<Texture>(L"mainscreen_smile_static", L"..\\content\\main screen\\smile anim\\smile_1.bmp"));

		smileAnim = select_smile->AddComponent<Animator>(enums::eComponentType::Animator);
		smileAnim->AddAnim(*ResourceManager::Load<Animation>(L"mainscreen_smile", L"..\\content\\main screen\\smile anim\\"));
		smileAnim->GetAnim(L"mainscreen_smile")->SetDuration(0.12f);
		smileAnim->GetAnim(L"mainscreen_smile")->SetLoop(false);
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

		if (KeyInput::GetKeyPressed(KeyCode::Enter))
		{
			smileSprite->SetActivate(false);
			smileAnim->PlayAnim(L"mainscreen_smile");
			loadMap = true;
		}

		if (loadMap && smileAnim->GetAnim(L"mainscreen_smile")->IsComplete())
		{
			loadMap = false;
			SceneManager::LoadScene(L"overWorld");
		}
	}
	void MainScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void MainScene::Clear()
	{
		loadMap = false;
	}
}