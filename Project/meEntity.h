#pragma once
#include "DEFAULT.h"

namespace me
{
	class Entity
	{
	public:
		Entity(const std::wstring& _name);
		virtual ~Entity() = 0;

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void SetName(std::wstring _name) { name = _name; }
		virtual std::wstring GetName() { return name; }

	private:
		std::wstring name;
	};
}

