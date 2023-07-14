#pragma once
#include "DEFAULT.h"
#include "meEntity.h"
#include "meLayer.h"

namespace me
{
	class Player_map;

	class Scene : public Entity
	{
	public:
		Scene(std::wstring name);
		virtual ~Scene() override;

		void Init() override;
		void Update() override;
		void Render(HDC hdc) override;

		virtual GameObject* AddGameObj(enums::eLayer layerType, std::wstring name);
		virtual GameObject* GetGameObj(enums::eLayer layerType, std::wstring name);

		virtual Player_map* AddPlayer_map(std::wstring name);

	private:
		std::vector<Layer> mLayers;
	};
}

