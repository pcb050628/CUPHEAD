#pragma once
#include "meComponent.h"

namespace me
{	
	class Rigidbody : public Component
	{
	public:
		Rigidbody(GameObject* gobj, const std::wstring& name);
		virtual ~Rigidbody() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void AddForce(math::Vector2 force) { mForce = force; }
		void SetMass(float mass) { mMass = mass; }

	private:
		float mMass;

		float mFirction;
		float mStaticFirction;
		float mKineticFirction;
		float mCoefficentFirction;

		math::Vector2 mAccelation;
		math::Vector2 mForce;
		math::Vector2 mVelocity;
		math::Vector2 mGravity;
	};
}

