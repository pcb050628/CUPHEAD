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
	}

	void RootPack_Stage::Setting()
	{
		BossFightScene::Setting();

		GetPlayer()->GetComponent<Transform>()->SetPos(math::Vector2(-420, 200));
		AddBoss<RootPack_Boss>(L"rootpack", math::Vector2(400, 0));
	}

	void RootPack_Stage::Update()
	{
		BossFightScene::Update(); // boss 안만들어줘서 오류남, 만들어주면 이걸로 바꿔야함
		//Scene::Update();
	}

	void RootPack_Stage::Render(HDC hdc)
	{
		BossFightScene::Render(hdc);
	}

	void RootPack_Stage::Clear()
	{
		BossFightScene::Clear();
	}
}
