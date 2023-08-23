#include "meCagneyCarnation_stage.h"
#include "meCagneyCarnation_Boss.h"
#include "meResourceManager.h"
#include "meColliderManager.h"

namespace me
{
	CagneyCarnation_stage::CagneyCarnation_stage(std::wstring name) : BossFightScene(name)
		, bgm(nullptr)
		, platform1(nullptr)
		, platform2(nullptr)
		, platform3(nullptr)
	{
	}
	CagneyCarnation_stage::~CagneyCarnation_stage()
	{
		bgm = nullptr;
	}

	void CagneyCarnation_stage::Init()
	{
		BossFightScene::Init();

		bgm = ResourceManager::Load<Sound>(L"CagneyCarnation_bgm", L"..\\content\\Sound\\AudioClip\\BossFightScene\\Cagney Carnation\\CagneyCarnation_bgm.wav");
		bgm->SetVolume(30.f);

		GameObject* bg = AddGameObj<GameObject>(enums::eLayer::Background, L"background");
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
		bgsr->SetImage(ResourceManager::Load<Texture>(L"ccbg", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Background\\ccbg_2.bmp"));

		platform1 = AddGameObj<Platform>(enums::eLayer::floor, L"platform_1");
		platform2 = AddGameObj<Platform>(enums::eLayer::floor, L"platform_2");
		platform3 = AddGameObj<Platform>(enums::eLayer::floor, L"platform_3");

		platform1->GetComponent<Transform>()->SetPos(math::Vector2(-400, 100));
		platform2->GetComponent<Transform>()->SetPos(math::Vector2(-150, 100));
		platform3->GetComponent<Transform>()->SetPos(math::Vector2(100, 100));
	}
	void CagneyCarnation_stage::Setting()
	{
		BossFightScene::Setting();

		ColliderManager::CollisionLayerCheck(enums::eLayer::Bullet, enums::eLayer::Sensor, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Player, enums::eLayer::Sensor, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Background, enums::eLayer::Enemy, true);

		AddBoss<CagneyCarnation_Boss>(L"Cagney Carnation", math::Vector2(450, 50));
		bgm->Play(true);
	}
	void CagneyCarnation_stage::Update()
	{
		BossFightScene::Update();
	}
	void CagneyCarnation_stage::Render(HDC hdc)
	{
		BossFightScene::Render(hdc);
	}
	void CagneyCarnation_stage::Clear()
	{
		BossFightScene::Clear();



		bgm->Stop(true);
	}
}