#include "meGoopy_Le_Grande_Stage.h"
#include "meGoopy_Le_Grande_Boss.h"
#include "meResourceManager.h"
#include "meColliderManager.h"
#include "meFloor.h"
#include "meQuestionMark.h"

namespace me
{
	Goopy_Le_Grande_Stage::Goopy_Le_Grande_Stage(std::wstring name) : BossFightScene(name)
	{
	}
	Goopy_Le_Grande_Stage::~Goopy_Le_Grande_Stage()
	{
	}
	void Goopy_Le_Grande_Stage::Init()
	{
		BossFightScene::Init();

		//GameObject* bg_evergreen = AddGameObj(enums::eLayer::Background, L"1_stage_backgroung_evergreen", enums::eGameObjType::background);
		//SpriteRenderer* evergreen_sr = bg_evergreen->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
		//evergreen_sr->SetImage(ResourceManager::Load<Texture>(L"Goopy_Le_background_evergreen", L"..\\content\\BossFight\\Goopy Le Grande\\Background\\slime_bg_bg_evergreens.bmp"));

		/*GameObject* bg_far_forest = AddGameObj(enums::eLayer::Background, L"0_stage_backgroung_far_forest", enums::eGameObjType::background);
		SpriteRenderer* far_forest_sr = bg_far_forest->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
		far_forest_sr->SetImage(ResourceManager::Load<Texture>(L"Goopy_Le_background_far_forest", L"..\\content\\BossFight\\Goopy Le Grande\\Background\\slime_bg_bg_far_forest.bmp"));
		far_forest_sr->SetScale(math::Vector2(1, 1.4f));*/

		//GameObject* bg_forest = AddGameObj(enums::eLayer::Background, L"2_stage_backgroung_bg_bg_forest", enums::eGameObjType::background);
		//SpriteRenderer* forest_sr = bg_forest->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
		//forest_sr->SetImage(ResourceManager::Load<Texture>(L"Goopy_Le_background_forest", L"..\\content\\BossFight\\Goopy Le Grande\\Background\\slime_bg_bg_forest.bmp"));
		////forest_sr->SetScale(math::Vector2(1, 1.4f));

		GameObject* bg_main_ground = AddGameObj(enums::eLayer::Background, L"3_stage_backgroung_bg_mg_main_ground", enums::eGameObjType::background);
		bg_main_ground->GetComponent<Transform>()->SetPos(bg_main_ground->GetComponent<Transform>()->GetPos() + math::Vector2(0, 80.f));
		SpriteRenderer* main_ground_sr = bg_main_ground->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
		main_ground_sr->SetImage(ResourceManager::Load<Texture>(L"Goopy_Le_background_main_ground", L"..\\content\\BossFight\\Goopy Le Grande\\Background\\slime_bg_mg_main_ground.bmp"));

		Floor* floor = AddGameObj<Floor>(enums::eLayer::floor, L"floor_");
	}
	void Goopy_Le_Grande_Stage::Setting()
	{
		BossFightScene::Setting();

		GetPlayer()->GetComponent<Transform>()->SetPos(math::Vector2(-420, 200));
		AddBoss<Goopy_Le_Grande_Boss>(L"Goopy Le Grande", math::Vector2(300, -500));

		ColliderManager::CollisionLayerCheck(enums::eLayer::Background, enums::eLayer::Player, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Background, enums::eLayer::Enemy, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::floor, enums::eLayer::Enemy, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::floor, enums::eLayer::Sensor, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Player, enums::eLayer::Sensor, true);
	}
	void Goopy_Le_Grande_Stage::Update()
	{
		BossFightScene::Update();
	}
	void Goopy_Le_Grande_Stage::Render(HDC hdc)
	{
		BossFightScene::Render(hdc);
	}
	void Goopy_Le_Grande_Stage::Clear()
	{
		BossFightScene::Clear();

		ColliderManager::CollisionLayerCheck(enums::eLayer::Background, enums::eLayer::Player, false);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Background, enums::eLayer::Enemy, false);
		ColliderManager::CollisionLayerCheck(enums::eLayer::floor, enums::eLayer::Enemy, false);
		ColliderManager::CollisionLayerCheck(enums::eLayer::floor, enums::eLayer::Sensor, false);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Player, enums::eLayer::Sensor, false);
	}
}