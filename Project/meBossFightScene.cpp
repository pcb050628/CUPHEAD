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
		, floor(nullptr)
		, wall1(nullptr)
		, wall2(nullptr)
		, deadUI(nullptr)
		, pauseUI(nullptr)
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

		deadUI = AddGameObj<DeadUI>(enums::eLayer::UI, L"deadUI");
		deadUI->SetActive(false);

		pauseUI = AddGameObj<PauseUI>(enums::eLayer::UI, L"pauseUI");
		pauseUI->SetActive(false);
	}
	void BossFightScene::Setting()
	{
		Camera::Reset();

		ColliderManager::CollisionLayerCheck(enums::eLayer::Player, enums::eLayer::floor, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Player, enums::eLayer::Enemy, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Player, enums::eLayer::Boss, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Bullet, enums::eLayer::Enemy, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Bullet, enums::eLayer::Boss, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Bullet, enums::eLayer::Background, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Player, enums::eLayer::Background, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Bullet, enums::eLayer::floor, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Bullet, enums::eLayer::Player, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Bullet, enums::eLayer::Bullet, true);
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

		if (mPlayer != nullptr && mPlayer->GetHP() <= 0)
		{
			if(!gameover)
				gameover = true;

			if (!deadUI->GetActive())
			{
				deadUI->SetActive(true);
			}

			if (KeyInput::GetKeyPressed(KeyCode::DownArrow) || KeyInput::GetKeyPressed(KeyCode::UpArrow))
			{
				deadUI->Change();
			}

			if (KeyInput::GetKeyPressed(KeyCode::Z))
				return;
		}

		if (KeyInput::GetKeyPressed(KeyCode::Space))
			mPlayer->GetComponent<Transform>()->SetPos(math::Vector2(0, 0));

		if (mBoss != nullptr && mBoss->GetHP() <= 0)
		{
			ColliderManager::CollisionLayerCheck(enums::eLayer::Player, enums::eLayer::Enemy, false);
			ColliderManager::CollisionLayerCheck(enums::eLayer::Player, enums::eLayer::Sensor, false);

			if (!IsFadeoutRunning() && !IsFadeoutEnd())
				RunFadeout();
			else if (!IsFadeoutRunning() && IsFadeoutEnd())
				SceneManager::LoadScene(L"clear");
		}
	}
	void BossFightScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void BossFightScene::Clear()
	{
		Scene::Clear();
		ColliderManager::Clear();
		RemovePlayer_stage();
		mPlayer = nullptr;
		RemoveBoss();
		mBoss = nullptr;
		deadUI->SetActive(false);
		gameover = false;
	}
}