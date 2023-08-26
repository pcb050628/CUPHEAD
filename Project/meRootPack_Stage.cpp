#include "meRootPack_Stage.h"
#include "meRootPack_Boss.h"
#include "meResourceManager.h"
#include "meSceneManager.h"
#include "meDust.h"
#include "meTear.h"
#include "meCarrotMissile.h"

namespace me
{
	RootPack_Stage::RootPack_Stage(std::wstring name) : BossFightScene(name)
		,bgm(nullptr)
	{
	}

	RootPack_Stage::~RootPack_Stage()
	{
	}

	void RootPack_Stage::Init()
	{
		BossFightScene::Init();

		GameObject* bg = AddGameObj<GameObject>(enums::eLayer::Background, L"rootpack_bg");
		SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
		sr->SetImage(ResourceManager::Load<Texture>(L"rootpack_stage_bg", L"..\\content\\Scene\\BossFight\\The Root Pack\\rootpack_stage_comp_bg.bmp"));
		sr->SetScale(math::Vector2(1.35f, 1.3f));
		bg->GetComponent<Transform>()->SetPos(bg->GetComponent<Transform>()->GetPos() + math::Vector2(0, 25));

		bgm = ResourceManager::Load<Sound>(L"rootPackStageBgm", L"..\\content\\Sound\\AudioClip\\BossFightScene\\The Root Pack\\bgm_level_veggies.wav");
		bgm->SetVolume(70);
	}

	void RootPack_Stage::Setting()
	{
		BossFightScene::Setting();

		GetPlayer()->GetComponent<Transform>()->SetPos(math::Vector2(-420, 200));
		AddBoss<RootPack_Boss>(L"rootpack", math::Vector2(400, 0));

		bgm->Play(true);
	}

	void RootPack_Stage::Update()
	{
		BossFightScene::Update();
	}

	void RootPack_Stage::Render(HDC hdc)
	{
		BossFightScene::Render(hdc);
	}

	void RootPack_Stage::Clear()
	{
		BossFightScene::Clear();
		bgm->Stop(true);
	}
}
