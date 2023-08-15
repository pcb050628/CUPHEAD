#pragma once
#include "DEFAULT.h"
#include "meComponent.h"

namespace me
{
	class Transform : public Component
	{
	public:
		Transform(GameObject* gobj, const std::wstring& name);
		virtual ~Transform() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetPos(math::Vector2 pos) 
		{ 
			mPosition = pos; 
		}

		void SetPos(float x, float y)
		{
			mPosition = math::Vector2(x, y);
		}
		math::Vector2 GetPos() { return mPosition; }

		void SetScale(math::Vector2 scale) { mScale = scale; }
		math::Vector2 GetScale() { return mScale; }

	private:
		math::Vector2 mPosition;
		math::Vector2 mScale;
	};
}

