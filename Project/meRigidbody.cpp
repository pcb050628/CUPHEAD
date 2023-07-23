#include "meRigidbody.h"
#include "meGameObject.h"
#include "COMPONENTS.h"

namespace me
{
	Rigidbody::Rigidbody(GameObject* gobj, const std::wstring& name) : Component(enums::eComponentType::Rigidbody, gobj, name)
		, mMass(1.f)
	{
	}
	Rigidbody::~Rigidbody()
	{
	}
	void Rigidbody::Init()
	{
	}
	void Rigidbody::Update()
	{
		mAccelation = mForce / mMass;

		mVelocity += mAccelation * Time::GetDeltaTime();

		if (!(mVelocity == math::Vector2::Zero))
		{
			math::Vector2 friction = -mVelocity;
			friction = friction.normalize() * mFirction * mMass * Time::GetDeltaTime();

			if (mVelocity.Length() < friction.Length())
			{
				mVelocity = math::Vector2::Zero;
			}
			else
			{
				mVelocity += friction;
			}
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		math::Vector2 pos = tr->GetPos();
		pos += mVelocity * Time::GetDeltaTime();
		tr->SetPos(pos);

		mForce.Clear();
	}
	void Rigidbody::Render(HDC hdc)
	{
	}
}