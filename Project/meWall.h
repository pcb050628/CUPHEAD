#pragma once
#include "meGameObject.h"

namespace me
{	
	class Wall : public GameObject
	{
	public:
		Wall(const std::wstring& name);
		virtual ~Wall() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);
	private:
		BoxCollider* mCollider;

	};
}

