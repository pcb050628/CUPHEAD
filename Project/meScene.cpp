#include "meScene.h"
#include "COMPONENTS.h"
#include "meColliderManager.h"
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

		ColliderManager::CollisionLayerCheck(enums::eLayer::Sensor, enums::eLayer::Enemy, true);
		ColliderManager::CollisionLayerCheck(enums::eLayer::Sensor, enums::eLayer::Player, true);

		// screenfx 추가 코드 - 프레임드랍이 너무 심함
		/*GameObject* scfx = mLayers[(int)enums::eLayer::ScreenFx].AddGameObj(L"scrrenFx");
		scfx->AddComponent<Animator>()->AddAnimation(L"..\\content\\screen fx\\");
		scfx->GetComponent<Animator>()->SetScale(math::Vector2(1.25f, 1.40625f));*/
	}

	void Scene::Update()
	{
		for (Layer& lys : mLayers)
		{
			lys.Update();
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (Layer& lys : mLayers)
		{
			lys.Render(hdc);
		}
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

	void Scene::AddBoss(Boss* boss)
	{
		mLayers[(int)enums::eLayer::Enemy].AddBoss(boss);
	}

	void Scene::Clear()
	{
	}
}