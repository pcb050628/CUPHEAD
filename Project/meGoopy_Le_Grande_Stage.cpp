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

		GameObject* bg_base = AddGameObj(enums::eLayer::Background, L"stage_backgroung_base");
		SpriteRenderer* base_sr = bg_base->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
		base_sr->SetImage(ResourceManager::Load<Texture>(L"Goopy_Le_Grande_Background_base", L""));

		GameObject* bg_second = AddGameObj(enums::eLayer::Background, L"stage_backgroung_second");
		SpriteRenderer* second_sr = bg_second->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
		second_sr->SetImage(ResourceManager::Load<Texture>(L"Goopy_Le_Grande_Background_second", L""));
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