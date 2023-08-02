#pragma once
#include "meGameObject.h"

namespace me
{	
	class Sensor : public GameObject
	{
	public:
		Sensor(const std::wstring& name);
		virtual ~Sensor() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void SetColliderSize(math::Vector2 value) {	mCollider->SetSize(value); }

		void SetTargetType(enums::eGameObjType type) { TargetType = type; }

		bool Sensed() { return mSensed; }

		GameObject* GetSensedObj() { return SensedObj; }

		void SetOwner(GameObject* owner) { mOwner = owner; }

		void SetPos(math::Vector2 value) { GetComponent<Transform>()->SetPos(value); }
		void SetOffset(math::Vector2 value) { mOffset = value; }

		math::Vector2 GetPos() { return GetComponent<Transform>()->GetPos(); }
		math::Vector2 GetOffset() { return mOffset; }

		void SetActive(bool value) { mCollider->SetActivate(value); }

	private:
		GameObject* mOwner;
		BoxCollider* mCollider;
		math::Vector2 mOffset;

		enums::eGameObjType TargetType;
		GameObject* SensedObj;
		bool mSensed;
	};
}

