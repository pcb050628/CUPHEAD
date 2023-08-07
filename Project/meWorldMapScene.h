#pragma once
#include "meScene.h"
#include "meTexture.h"
#include "meSensor.h"

namespace me
{
	class WorldMapScene : public Scene
	{
	public:
		WorldMapScene(std::wstring name);
		virtual ~WorldMapScene() override;

		void Init() override;
		void Setting() override;
		void Update() override;
		void Render(HDC hdc) override;

		virtual void Clear() override;

	private:
		Sensor* GoopyLeGrandeStage;
		
	};
}

