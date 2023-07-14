#pragma once
#include "meScene.h"
#include "meBoss.h"
#include "mePlayer_stage.h"

namespace me
{
	class BossFightScene : public Scene
	{
	public:
		BossFightScene(std::wstring name);
		virtual ~BossFightScene() override;

		void Init() override;
		void Update() override;
		void Render(HDC hdc) override;

	private:
		Boss			boss;
		Player_stage	player;
	};
}

