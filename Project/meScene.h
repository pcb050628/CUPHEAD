#pragma once
#include "DEFAULT.h"
#include "meEntity.h"
#include "meLayer.h"

namespace me
{
	class Player_map;
	class Player_stage;

	class Scene : public Entity
	{
	public:
		Scene(std::wstring name);
		virtual ~Scene() override;

		virtual void Init() override;
		virtual void Setting();
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void RunFadeout();
		virtual void StopFadeout();
		virtual bool IsFadeoutRunning() { return fadeoutCall; }
		virtual bool IsFadeoutEnd() { return fadeoutEnd; }

		virtual GameObject* AddGameObj(enums::eLayer layerType, std::wstring name, enums::eGameObjType type);
		virtual GameObject* GetGameObj(enums::eLayer layerType, std::wstring name);

		template <typename T>
		T* AddGameObj(enums::eLayer layerType, const std::wstring& name)
		{
			GameObject* obj = mLayers[(int)layerType].AddGameObj<T>(name);
			obj->Init();
			return dynamic_cast<T*>(obj);
		}

		virtual Player_map* AddPlayer_map(std::wstring name);
		virtual Player_stage* AddPlayer_stage(std::wstring name);
		virtual Player_map* GetPlayer_map() {
			return mLayers[(int)enums::eLayer::Player].GetPlayer_map();
		}
		virtual Player_stage* GetPlayer_stage() {
			return mLayers[(int)enums::eLayer::Player].GetPlayer_stage();
		}
		virtual void RemovePlayer_stage();

		virtual void AddBoss(Boss* boss);
		virtual Boss* GetBoss() {
			return mLayers[(int)enums::eLayer::Boss].GetBoss();
		}
		virtual void RemoveBoss();

		virtual void DeleteAllSensor();

		virtual Layer& GetLayer(enums::eLayer type) { return mLayers[(int)type]; }

		bool Destroy(GameObject* gobj, enums::eLayer layerType)
		{
			return mLayers[(int)layerType].Destroy(gobj);
		}

		virtual void Clear();

	private:
		std::vector<Layer> mLayers;
		bool isSetting;

		SpriteRenderer* fadeoutRenderer;
		bool fadeoutCall;
		bool fadeoutEnd;
	};
}

