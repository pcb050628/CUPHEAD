#include "meBossFightScene.h"
#include "COMPONENTS.h"
#include "meResourceManager.h"
#include "meSceneManager.h"
#include "meColliderManager.h"
#include "meWall.h"
#include "meHealthBar.h"

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

		ColliderManager::CollisionLayerCheck(enums::eLayer::Player, enums::eLayer::floor, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Player, enums::eLayer::Enemy, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Bullet, enums::eLayer::Enemy, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Bullet, enums::eLayer::Background, true);

		wall1 = AddGameObj<Wall>(enums::eLayer::Background, L"Wall_1");
		wall2 = AddGameObj<Wall>(enums::eLayer::Background, L"Wall_2");

	}
	void BossFightScene::Setting()
	{
		wall1->GetComponent<Transform>()->SetPos(math::Vector2(-690, 0));
		wall2->GetComponent<Transform>()->SetPos(math::Vector2(690, 0));

		mPlayer = AddPlayer_stage(L"CupHead_stage");

		HealthBar* hpbar = AddGameObj<HealthBar>(enums::eLayer::UI, L"hpbar");
		hpbar->SetPlayer(mPlayer);
	}
	void BossFightScene::Update()
	{
		Scene::Update();

		if (KeyInput::GetKeyPressed(KeyCode::Space))
			mPlayer->GetComponent<Transform>()->SetPos(math::Vector2(0, 0));
	}
	void BossFightScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void BossFightScene::Clear()
	{
		RemovePlayer_stage();
		RemoveBoss();
	}
}