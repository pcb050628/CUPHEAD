#pragma once
#include "meEntity.h"
#include "DEFAULT.h"

namespace me
{
	class GameObject;

	class Component : public Entity
	{
	public:
		Component(enums::eComponentType type, GameObject* gobj, const std::wstring& name);
		virtual ~Component() = 0;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual GameObject* GetOwner() { return mOwner; }

		virtual void SetActivate(bool val) { mActivate = val; }
		virtual bool GetActivate() { return mActivate; }

	private:
		const enums::eComponentType mType;
		GameObject* mOwner;

		bool mActivate;
	};
}

