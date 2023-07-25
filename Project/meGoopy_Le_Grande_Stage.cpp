#include "meGoopy_Le_Grande_Stage.h"
#include "meGoopy_Le_Grande_Boss.h"
#include "meResourceManager.h"
#include "meColliderManager.h"
#include "meFloor.h"

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

		ColliderManager::CollisionLayerCheck(enums::eLayer::Background, enums::eLayer::Player, true);

		//AddBoss<Goopy_Le_Grande_Boss>(L"Goopy Le Grande");

		GameObject* bg_evergreen = AddGameObj(enums::eLayer::Background, L"1_stage_backgroung_evergreen", enums::eGameObjType::background);
		SpriteRenderer* evergreen_sr = bg_evergreen->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
		evergreen_sr->SetImage(ResourceManager::Load<Texture>(L"Goopy_Le_background_evergreen", L"..\\content\\BossFight\\Goopy Le Grande\\Background\\slime_bg_bg_evergreens.bmp"));

		GameObject* bg_far_forest = AddGameObj(enums::eLayer::Background, L"0_stage_backgroung_far_forest", enums::eGameObjType::background);
		SpriteRenderer* far_forest_sr = bg_far_forest->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
		far_forest_sr->SetImage(ResourceManager::Load<Texture>(L"Goopy_Le_background_far_forest", L"..\\content\\BossFight\\Goopy Le Grande\\Background\\slime_bg_bg_far_forest.bmp"));
		far_forest_sr->SetScale(math::Vector2(1, 1.4f));

		GameObject* testObj = AddGameObj(enums::eLayer::Enemy, L"test", enums::eGameObjType::enemy);
		testObj->AddComponent<BoxCollider>(enums::eComponentType::Collider);

		Floor* floor = AddGameObj<Floor>(enums::eLayer::Background, L"floor_Collider");

	}
	void Goopy_Le_Grande_Stage::Update()
	{
		BossFightScene::Update();
	}
	void Goopy_Le_Grande_Stage::Render(HDC hdc)
	{
		BossFightScene::Render(hdc);
	}
}