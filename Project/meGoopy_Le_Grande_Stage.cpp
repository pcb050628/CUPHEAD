#include "meGoopy_Le_Grande_Stage.h"
#include "meResourceManager.h"

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

		/*GameObject* bg_far_forest = AddGameObj(enums::eLayer::Background, L"stage_backgroung_far_forest");
		SpriteRenderer* far_forest_sr = bg_far_forest->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
		far_forest_sr->SetImage(ResourceManager::Load<Texture>(L"Goopy_Le_backgroung_far_forest", L"..\\content\\BossFight\\Cuphead\\Idle\\cuphead_idle_0004.bmp"));
		far_forest_sr->SetScale(math::Vector2(1, 1.4f));*/

		/*GameObject* bg_evergreen = AddGameObj(enums::eLayer::Background, L"stage_backgroung_evergreen");
		SpriteRenderer* evergreen_sr = bg_evergreen->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
		evergreen_sr->SetImage(ResourceManager::Load<Texture>(L"Goopy_Le_backgroung_evergreen", L"..\\content\\BossFight\\Goopy Le Grande\\Background\\slime_bg_bg_evergreens.bmp"));*/
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