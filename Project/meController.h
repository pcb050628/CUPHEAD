#pragma once
#include "DEFAULT.h"
#include "meComponent.h"

namespace me
{
	class Controller : public Component
	{
	public:
		Controller(GameObject* gobj, const std::wstring& name);
		virtual ~Controller() override;

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:

	};
}

