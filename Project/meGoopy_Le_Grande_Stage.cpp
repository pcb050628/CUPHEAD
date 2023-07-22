#include "meGoopy_Le_Grande_Stage.h"
#include "meGoopy_Le_Grande_Boss.h"
#include "meResourceManager.h"
#include "meColliderManager.h"

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

		GameObject* floor = AddGameObj(enums::eLayer::Background, L"floor_Collider");
		BoxCollider* floor_col =  floor->AddComponent<BoxCollider>(enums::eComponentType::BoxCollider);
		floor_col->SetOffset(math::Vector2(0, 250.f));
		floor_col->SetSize(math::Vector2(1600, 50.f));

		AddBoss<Goopy_Le_Grande_Boss>(L"Goopy Le Grande");

		/*GameObject* bg_evergreen = AddGameObj(enums::eLayer::Background, L"1_stage_backgroung_evergreen");
		SpriteRenderer* evergreen_sr = bg_evergreen->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
		evergreen_sr->SetImage(ResourceManager::Load<Texture>(L"Goopy_Le_background_evergreen", L"..\\content\\BossFight\\Goopy Le Grande\\Background\\slime_bg_bg_evergreens.bmp"));

		GameObject* bg_far_forest = AddGameObj(enums::eLayer::Background, L"0_stage_backgroung_far_forest");
		SpriteRenderer* far_forest_sr = bg_far_forest->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
		far_forest_sr->SetImage(ResourceManager::Load<Texture>(L"Goopy_Le_background_far_forest", L"..\\content\\BossFight\\Goopy Le Grande\\Background\\slime_bg_bg_far_forest.bmp"));
		far_forest_sr->SetScale(math::Vector2(1, 1.4f));*/

		/*Animator* Anim = AddGameObj(enums::eLayer::Player, L"bullet")->AddComponent<Animator>(enums::eComponentType::Animator); 
		Anim->AddAnim(ResourceManager::Load<Animation>(L"bulletidle", L"..\\content\\BossFight\\Cuphead\\Bullet\\Idle\\"));
		Anim->PlayAnim(L"bulletidle");
		Anim->GetAnim(L"bulletidle")->SetLoop(false);*/
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