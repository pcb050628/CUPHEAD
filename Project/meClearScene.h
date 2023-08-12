#pragma once
#include "meScene.h"

namespace me
{	
	class ClearScene : public Scene
	{
	public:
		ClearScene(std::wstring name);
		virtual ~ClearScene() override;

		virtual void Init() override;
		virtual void Setting();
		virtual void Update() override;
		virtual void Render(HDC hdc) override;


	private:
		SpriteRenderer* bg;
		SpriteRenderer* result;

	};
}

