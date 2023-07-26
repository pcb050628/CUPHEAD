#pragma once
#include "meScene.h"

namespace me
{
	class TitleScene : public Scene
	{
	public:
		TitleScene(std::wstring name);
		virtual ~TitleScene() override;

		void Init() override;
		void Update() override;
		void Render(HDC hdc) override;

		virtual void Clear() override;

	private:

	};
}

