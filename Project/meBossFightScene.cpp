#include "meBossFightScene.h"
#include "COMPONENTS.h"
#include "meResourceManager.h"
#include "meSceneManager.h"

namespace me
{
	BossFightScene::BossFightScene(std::wstring name) : Scene(name)
		, mBoss(NULL)
		, mPlayer(NULL)
	{
	}
	BossFightScene::~BossFightScene()
	{
	}
	void BossFightScene::Init()
	{
		Scene::Init();

		mPlayer = AddPlayer_stage(L"CupHead_stage");
	}
	void BossFightScene::Update()
	{
		Scene::Update();
	}
	void BossFightScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}