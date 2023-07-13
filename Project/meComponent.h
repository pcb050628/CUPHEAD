#pragma once
#include "DEFAULT.h"

namespace me
{
	class GameObject;

	class Component 
	{
	public:
		Component(enums::eComponentType type, GameObject* gobj);
		virtual ~Component() = 0;

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual GameObject* GetOwner() { return mOwner; }

		virtual void SetActivate(bool val) { Activate = val; }
		virtual bool GetActivate() { return Activate; }

	private:
		const enums::eComponentType mType;
		GameObject* mOwner;

		bool Activate;
	};
}

