#include "meRigidbody.h"
#include "meGameObject.h"
#include "COMPONENTS.h"

namespace me
{
	Rigidbody::Rigidbody(GameObject* gobj, const std::wstring& name)
		: Component(enums::eComponentType::Rigidbody, gobj, name)
		, mMass(1.0f)
		, mFriction(10.0f)
		, mType(Type::dynamicType)
		, mbGround(false)
	{
		mLimitedVelocty.x = 200.0f;
		mLimitedVelocty.y = 1000.0f;
		mGravity = math::Vector2(0.0f, 800.0f);
	}

	Rigidbody::~Rigidbody()
	{
	}

	void Rigidbody::Init()
	{
	}

	void Rigidbody::Update()
	{
		//이동
		// F = M x A
		// A = F / M
		mAccelation = mForce / mMass;

		// 속도에 가속도를 더한다
		mVelocity += mAccelation * Time::GetDeltaTime();

		if (mType == Type::dynamicType)
		{
			if (mbGround)
			{
				// 땅위에 있을때
				math::Vector2 gravity = mGravity;
				gravity.normalize();
				float dot = math::Dot(mVelocity, gravity);
				mVelocity += gravity * dot;
				//mVelocity.y = 0;
			}
			else
			{
				// 공중에 있을 때
				mVelocity += mGravity * Time::GetDeltaTime();
			}
		}
		else if (mType == Type::staticType)
		{
			math::Vector2 gravity = mGravity;
			gravity.normalize();
			float dot = math::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}


		// 최대 속도 제한
		math::Vector2 gravity = mGravity;
		gravity.normalize();
		float dot = math::Dot(mVelocity, gravity);
		gravity = gravity * dot;

		math::Vector2 sideVelocity = mVelocity - gravity;
		if (mLimitedVelocty.y < gravity.length())
		{
			gravity.normalize();
			gravity *= mLimitedVelocty.y;
		}

		if (mLimitedVelocty.x < sideVelocity.length())
		{
			sideVelocity.normalize();
			sideVelocity *= mLimitedVelocty.x;
		}
		mVelocity = gravity + sideVelocity;

		//마찰력 조건 ( 적용된 힘이 없고, 속도가 0 이 아닐 ??)
		if (!(mVelocity == math::Vector2::Zero))
		{
			// 속도에 반대 방향으로 마찰력을 적용
			math::Vector2 friction = -mVelocity;
			friction = friction.normalize() * mFriction * mMass * Time::GetDeltaTime();

			// 마찰력으로 인한 속도 감소량이 현재 속도보다 더 큰 경우
			if (mVelocity.length() < friction.length())
			{
				// 속도를 0 로 만든다.
				mVelocity = math::Vector2(0.f, 0.f);
			}
			else
			{
				// 속도에서 마찰력으로 인한 반대방향으로 속도를 차감한다.
				mVelocity += friction;
			}
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		math::Vector2 pos = tr->GetPos();
		pos = pos + (mVelocity * Time::GetDeltaTime());
		tr->SetPos(pos);
		mForce.clear();
	}

	void Rigidbody::Render(HDC hdc)
	{

	}

}