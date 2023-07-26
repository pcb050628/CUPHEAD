#include "meWorldMapScene.h"
#include "OBJECTS.h"
#include "COMPONENTS.h"
#include "meResourceManager.h"
#include "meSceneManager.h"
#include "meCamera.h"
#include "mePlayer_map.h"

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

		GameObject* map = AddGameObj(enums::eLayer::Background, L"map_ocean", enums::eGameObjType::background);
		Texture* image_map = ResourceManager::Load<Texture>(L"world_ocean", L"..\\\content\\overWorld\\Inkwell Isle I\\world1_map_.bmp");
		SpriteRenderer* map_sr = map->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
		map_sr->SetImage(image_map);
		map->GetComponent<Transform>()->SetPos(math::Vector2(1060, 420));

		Camera::SetTarget(AddPlayer_map(L"CupHead_map"));
	}
	void WorldMapScene::Update()
	{
		Scene::Update();

		if (KeyInput::GetKeyDown(KeyCode::H))
			SceneManager::LoadScene(L"test");
	}
	void WorldMapScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void WorldMapScene::Clear()
	{
	}
}