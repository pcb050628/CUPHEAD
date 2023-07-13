#pragma once
#include "meScene.h"
#include "meTexture.h"

namespace me
{
	class WorldMapScene : public Scene
	{
	public:
		WorldMapScene(std::wstring name);
		virtual ~WorldMapScene() override;

		void Init() override;
		void Update() override;
		void Render(HDC hdc) override;

	private:

	};
}

