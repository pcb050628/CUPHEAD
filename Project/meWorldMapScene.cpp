#include "meWorldMapScene.h"
#include "OBJECTS.h"
#include "COMPONENTS.h"
#include "meResourceManager.h"
#include "meSceneManager.h"

namespace me
{
	WorldMapScene::WorldMapScene(std::wstring name) : Scene(name)
	{
	}
	WorldMapScene::~WorldMapScene()
	{
	}

	void WorldMapScene::Init()
	{
		Scene::Init();

		GameObject* map_small = AddGameObj(enums::eLayer::Background, L"map_ocean");
		Texture* iamge_map_small_isle = ResourceManager::Load<Texture>(L"world_ocean", L"..\\\content\\overWorld\\Inkwell Isle I\\Ocean\\world1_ocean_03.bmp");
		SpriteRenderer* title_bg_sr = map_small->AddComponent<SpriteRenderer>();
		title_bg_sr->SetImage(iamge_map_small_isle);
		map_small->AddComponent<Controller>();



		/*GameObject* map_small = AddGameObj(enums::eLayer::Background, L"map_small_isle");
		Texture* iamge_map_small_isle = ResourceManager::Load<Texture>(L"world_small_island", L"..\\content\\overWorld\\Inkwell Isle I\\Small Island\\Main\\world1_small_island_main.png");
		SpriteRenderer* title_bg_sr = map_small->AddComponent<SpriteRenderer>();
		title_bg_sr->SetImage(iamge_map_small_isle);*/
	}
	void WorldMapScene::Update()
	{
		Scene::Update();
	}
	void WorldMapScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}