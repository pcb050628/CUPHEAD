#pragma once
#include "meGameObject.h"

namespace me
{
	class Boss : public GameObject
	{
	public:
		Boss(const std::wstring& name);
		virtual ~Boss() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
