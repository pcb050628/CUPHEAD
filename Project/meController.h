#pragma once
#include "DEFAULT.h"
#include "meComponent.h"

namespace me
{
	namespace enums
	{
		enum class eControlType
		{
			map,
			stage,
			none
		};
	}

	class Controller : public Component
	{
	public:
		Controller(GameObject* gobj, const std::wstring& name);
		virtual ~Controller() override;

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void SetType(enums::eControlType type) { mType = type; }

	private:
		enums::eControlType mType;
	};
}

