#pragma once
#include "meGameObject.h"

namespace me
{
	class Floor : public GameObject
	{
	public:
		Floor(const std::wstring& name);
		virtual ~Floor() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:

	};
}

