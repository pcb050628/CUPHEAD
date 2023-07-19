#pragma once
#include "meComponent.h"

namespace me
{	
	class BoxCollider : public Component
	{
	public:
		BoxCollider(GameObject* gobj, const std::wstring& name);
		virtual ~BoxCollider() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetPos(math::Vector2 pos) { mPos = pos; }
		void SetScale(math::Vector2 scale) { mScale= scale; }
		math::Vector2 GetPos() { return mPos; }
		math::Vector2 GetScale() { return mScale; }

	private:
		math::Vector2 mPos;
		math::Vector2 mScale;
	};
}

