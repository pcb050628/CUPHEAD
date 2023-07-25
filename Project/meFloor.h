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

		virtual void OnCollisionEnter(BoxCollider* other);
		virtual void OnCollisionStay(BoxCollider* other);
		virtual void OnCollisionExit(BoxCollider* other);

	private:

	};
}

