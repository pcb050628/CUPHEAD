#include "meBossFightScene.h"
#include "COMPONENTS.h"
#include "meResourceManager.h"
#include "meSceneManager.h"
#include "meColliderManager.h"
#include "meWall.h"

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

		Wall* wall_1 = AddGameObj<Wall>(enums::eLayer::Background, L"Wall_1");
		Wall* wall_2 = AddGameObj<Wall>(enums::eLayer::Background, L"Wall_2");

		wall_1->GetComponent<Transform>()->SetPos(wall_1->GetComponent<Transform>()->GetPos() - math::Vector2(690, 0));
		wall_2->GetComponent<Transform>()->SetPos(wall_2->GetComponent<Transform>()->GetPos() + math::Vector2(690, 0));

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
	void BossFightScene::Clear()
	{
	}
}