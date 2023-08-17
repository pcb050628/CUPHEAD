#include "meScene.h"
#include "COMPONENTS.h"
#include "meColliderManager.h"
#include "meResourceManager.h"
#include "mePlayer_map.h"
#include "mePlayer_stage.h"

namespace me
{
	Scene::Scene(std::wstring name) : Entity(name)
	{
	}

	Scene::~Scene()
	{

	}

	void Scene::Init()
	{
		mLayers.reserve((int)enums::eLayer::End);

		for (int i = 0; i < (int)enums::eLayer::End; i++)
		{
			mLayers.push_back(Layer());
		}

		fadeoutRenderer = AddGameObj(enums::eLayer::Background, L"fadeout", enums::eGameObjType::background)->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
		fadeoutRenderer->SetImage(ResourceManager::Load<Texture>(L"blackScreen32bmp", L"..\\content\\Scene\\test.bmp"));
		fadeoutRenderer->SetActivate(false);

		//ColliderManager::CollisionLayerCheck(enums::eLayer::Sensor, enums::eLayer::Enemy, true);
		//ColliderManager::CollisionLayerCheck(enums::eLayer::Sensor, enums::eLayer::Player, true);
	}

	void Scene::Setting()
	{
	}

	void Scene::Update()
	{
		if (!isSetting)
		{
			isSetting = true;
			Setting();
		}

		for (Layer& lys : mLayers)
		{
			lys.Update();
		}

		/*if (KeyInput::GetKeyPressed(KeyCode::K))
		{
			if (!fadeoutCall)
				RunFadeout();
			else
				StopFadeout();
		}*/
	}

	void Scene::Render(HDC hdc)
	{
		if (fadeoutCall)
		{
			fadeoutRenderer->SetAlpha(fadeoutRenderer->GetAlpha() + 0.1f * Time::GetDeltaTime());
		}

		for (Layer& lys : mLayers)
		{
			lys.Render(hdc);
		}
	}
	void Scene::RunFadeout()
	{
		fadeoutCall = true;
		fadeoutRenderer->SetActivate(true);
	}
	void Scene::StopFadeout()
	{
		fadeoutCall = false;
		fadeoutRenderer->SetActivate(false);
		fadeoutRenderer->SetAlpha(0);
	}
	GameObject* Scene::AddGameObj(enums::eLayer layerType, std::wstring name, enums::eGameObjType type)
	{
		GameObject* obj = mLayers[(int)layerType].AddGameObj(name, type);
		obj->Init();
		return obj;
	}

	GameObject* Scene::GetGameObj(enums::eLayer layerType, std::wstring name)
	{
		return mLayers[(int)layerType].GetGameObj(name);
	}

	Player_map* Scene::AddPlayer_map(std::wstring name)
	{
		Player_map* p = mLayers[(int)enums::eLayer::Player].AddPlayer_map(name);
		p->Init();
		return p;
	}

	Player_stage* Scene::AddPlayer_stage(std::wstring name)
	{
		Player_stage* p = mLayers[(int)enums::eLayer::Player].AddPlayer_stage(name);
		p->Init();
		p->GetComponent<Transform>()->SetPos(math::Vector2(-300, 0));
		return p;
	}

	void Scene::RemovePlayer_stage()
	{
		mLayers[(int)enums::eLayer::Player].RemovePlayer_stage();
	}

	void Scene::AddBoss(Boss* boss)
	{
		mLayers[(int)enums::eLayer::Enemy].AddBoss(boss);
	}

	void Scene::RemoveBoss()
	{
		mLayers[(int)enums::eLayer::Enemy].RemoveBoss();
	}

	void Scene::DeleteAllSensor()
	{

	}

	void Scene::Clear()
	{
		isSetting = false;
	}
}