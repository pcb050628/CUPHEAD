#include "meBossFightScene.h"
#include "COMPONENTS.h"
#include "meResourceManager.h"
#include "meSceneManager.h"
#include "meColliderManager.h"

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

		mPlayer = AddPlayer_stage(L"CupHead_stage");
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
}