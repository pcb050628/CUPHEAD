#include "meBossFightScene.h"
#include "COMPONENTS.h"
#include "meResourceManager.h"
#include "meSceneManager.h"

namespace me
{
	BossFightScene::BossFightScene(std::wstring name) : Scene(name)
		, boss(NULL)
		, player(NULL)
	{
	}
	BossFightScene::~BossFightScene()
	{
	}
	void BossFightScene::Init()
	{
		Scene::Init();
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