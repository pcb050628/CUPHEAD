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
		//�̵�
		// F = M x A
		// A = F / M
		mAccelation = mForce / mMass;

		// �ӵ��� ���ӵ��� ���Ѵ�
		mVelocity += mAccelation * Time::GetDeltaTime();

		if (mType == Type::dynamicType)
		{
			if (mbGround)
			{
				// ������ ������
				math::Vector2 gravity = mGravity;
				gravity.normalize();
				float dot = math::Dot(mVelocity, gravity);
				mVelocity += gravity * dot;
				//mVelocity.y = 0;
			}
			else
			{
				// ���߿� ���� ��
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


		// �ִ� �ӵ� ����
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

		//������ ���� ( ����� ���� ����, �ӵ��� 0 �� �ƴ� ??)
		if (!(mVelocity == math::Vector2::Zero))
		{
			// �ӵ��� �ݴ� �������� �������� ����
			math::Vector2 friction = -mVelocity;
			friction = friction.normalize() * mFriction * mMass * Time::GetDeltaTime();

			// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� �� ū ���
			if (mVelocity.length() < friction.length())
			{
				// �ӵ��� 0 �� �����.
				mVelocity = math::Vector2(0.f, 0.f);
			}
			else
			{
				// �ӵ����� ���������� ���� �ݴ�������� �ӵ��� �����Ѵ�.
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