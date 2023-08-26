#pragma once
#include "meGameObject.h"

namespace me
{	
	class Bullet : public GameObject
	{
	public:
		Bullet(const std::wstring& name);
		virtual ~Bullet() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void SetFlip(bool value) { flip = value; }
		bool GetFlip() { return flip; }

		void SetDmg(int value) { damage = value; }
		int ReturnDmg() { return damage; }

	private:
		float damage;
		bool flip;

	};
}

