#include "meWorldMapScene.h"
#include "OBJECTS.h"
#include "COMPONENTS.h"
#include "meResourceManager.h"
#include "meSceneManager.h"
#include "meCamera.h"
#include "mePlayer.h"

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

		GameObject* map = AddGameObj(enums::eLayer::Background, L"map_ocean");
		Texture* image_map = ResourceManager::Load<Texture>(L"world_ocean", L"..\\\content\\overWorld\\Inkwell Isle I\\world1_map_.bmp");
		SpriteRenderer* map_sr = map->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
		map_sr->SetImage(image_map);
		map->GetComponent<Transform>()->SetPos(math::Vector2(1060, 420));

		Camera::SetTarget(AddPlayer(L"CupHead_map"));
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