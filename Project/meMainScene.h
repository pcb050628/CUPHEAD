#pragma once
#include "meScene.h"

namespace me
{
	class MainScene : public Scene
	{
	public:
		MainScene(std::wstring name);
		virtual ~MainScene() override;

		void Init() override;
		void Setting() override;
		void Update() override;
		void Render(HDC hdc) override;

		virtual void Clear() override;

	private:
		SpriteRenderer* smileSprite;
		Animator* smileAnim;

	};
}

