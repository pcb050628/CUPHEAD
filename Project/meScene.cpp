#include "meScene.h"
#include "COMPONENTS.h"
#include "mePlayer_map.h"

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

	GameObject* Scene::AddGameObj(enums::eLayer layerType, std::wstring name)
	{
		GameObject* obj = mLayers[(int)layerType].AddGameObj(name);
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

}