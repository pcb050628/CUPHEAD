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
		virtual void Setting() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Clear() override;


	private:
		SpriteRenderer* bg;
		SpriteRenderer* result;

	};
}

