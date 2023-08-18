#include "meWorldMapScene.h"
#include "OBJECTS.h"
#include "COMPONENTS.h"
#include "meResourceManager.h"
#include "meSceneManager.h"
#include "meColliderManager.h"
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
		Texture* image_map = ResourceManager::Load<Texture>(L"world_ocean", L"..\\content\\Scene\\overWorld\\Inkwell Isle I\\world1_map_.bmp");
		SpriteRenderer* map_sr = map->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
		map_sr->SetImage(image_map);
		map->GetComponent<Transform>()->SetPos(math::Vector2(1060, 420));

		bgm = ResourceManager::Load<Sound>(L"worldmap_bgm", L"..\\content\\Sound\\AudioClip\\OverWorld\\bgm_map_gdc.wav");

		mPlayer = AddPlayer_map(L"CupHead_map");
		mPlayer->GetComponent<Transform>()->SetPos(mPlayer->GetComponent<Transform>()->GetPos() + math::Vector2(450, 60));

		GoopyLeGrandeStage = AddGameObj<Sensor>(enums::eLayer::Sensor, L"glgStageSensor");
		GoopyLeGrandeStage->SetTargetType(enums::eGameObjType::player);
		GoopyLeGrandeStage->GetComponent<Transform>()->SetPos(math::Vector2(1240, -220));

		RootPackStage = AddGameObj<Sensor>(enums::eLayer::Sensor, L"trpStageSensor");
		RootPackStage->SetTargetType(enums::eGameObjType::player);
		RootPackStage->GetComponent<Transform>()->SetPos(math::Vector2(960, 570));
	}
	void WorldMapScene::Setting()
	{
		Camera::SetTarget(mPlayer);

		bgm->Play(true);

		ColliderManager::CollisionLayerCheck(enums::eLayer::Sensor, enums::eLayer::Player, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Background, enums::eLayer::Player, true);
	}
	void WorldMapScene::Update()
	{
		Scene::Update();

		if (KeyInput::GetKeyPressed(KeyCode::Z) && GoopyLeGrandeStage->Sensed())
			SceneManager::LoadScene(L"slime_stage");

		if (KeyInput::GetKeyPressed(KeyCode::Z) && RootPackStage->Sensed())
			SceneManager::LoadScene(L"rootpack_stage");
	}
	void WorldMapScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void WorldMapScene::Clear()
	{
		Scene::Clear();

		bgm->Stop(true);
	}
}