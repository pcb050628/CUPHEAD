#pragma once
#include "meComponent.h"


namespace me
{
	class Rigidbody : public Component
	{
	public:
		enum class Type
		{
			dynamicType,
			staticType,
			end,
		};

		Rigidbody(GameObject* gobj, const std::wstring& name);
		~Rigidbody();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC hdc);

		void AddForce(math::Vector2 force) { mForce += force; }
		void SetMass(float mass) { mMass = mass; }
		void SetGround(bool ground) { mbGround = ground; }
		bool GetIsGround() { return mbGround; }
		math::Vector2 GetVelocity() { return mVelocity; }
		void SetVelocity(math::Vector2 velocity) { mVelocity = velocity; }

		void SetType(Type type) { mType = type; }
		Type GetType(Type type) { return mType; }

	private:
		float mMass;

		float mFriction;
		float mStaticFriction;
		float mKineticFrction;
		float mCoefficentFrction;

		math::Vector2 mForce;
		math::Vector2 mAccelation;
		math::Vector2 mVelocity;
		math::Vector2 mGravity;
		math::Vector2 mLimitedVelocty;

		Rigidbody::Type mType;
		bool mbGround;
	};
}
