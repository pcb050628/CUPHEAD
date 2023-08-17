#include "meBossFightScene.h"
#include "COMPONENTS.h"
#include "meCamera.h"
#include "meResourceManager.h"
#include "meSceneManager.h"
#include "meColliderManager.h"
#include "meHealthBar.h"

namespace me
{
	BossFightScene::BossFightScene(std::wstring name) : Scene(name)
		, mBoss(NULL)
		, mPlayer(NULL)
		, savedTime(-1)
	{
	}
	BossFightScene::~BossFightScene()
	{
	}

	void BossFightScene::Init()
	{
		Scene::Init();

		wall1 = AddGameObj<Wall>(enums::eLayer::Background, L"Wall_1");
		wall2 = AddGameObj<Wall>(enums::eLayer::Background, L"Wall_2");
		floor = AddGameObj<Floor>(enums::eLayer::floor, L"floor");
	}
	void BossFightScene::Setting()
	{
		Camera::Reset();

		ColliderManager::CollisionLayerCheck(enums::eLayer::Player, enums::eLayer::floor, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Player, enums::eLayer::Enemy, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Bullet, enums::eLayer::Enemy, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Bullet, enums::eLayer::Background, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Player, enums::eLayer::Background, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Bullet, enums::eLayer::floor, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Bullet, enums::eLayer::Player, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Bullet, enums::eLayer::Bullet, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Player, enums::eLayer::Enemy, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::floor, enums::eLayer::Enemy, true);

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

		if (mBoss->GetHP() <= 0 && savedTime == -1)
		{
			savedTime = Time::GetTime();
		}

		if (savedTime != -1 && fabs(savedTime - Time::GetTime()) > 6)
			SceneManager::LoadScene(L"clear");
	}
	void BossFightScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void BossFightScene::Clear()
	{
		RemovePlayer_stage();
		RemoveBoss();
		savedTime = -1;
	}
}