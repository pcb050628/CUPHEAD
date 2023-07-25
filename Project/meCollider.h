#pragma once
#include "meComponent.h"

namespace me
{
	class Collider : public Component
	{
	public:
		Collider(GameObject* gobj, const std::wstring& name, enums::eColliderType type);
		virtual ~Collider() = 0;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		virtual void SetType(enums::eColliderType type) { mType = type;	}
		virtual enums::eColliderType GetType() { return mType; }

		virtual bool GetCollision() { return isCollision; }

		void SetPos(math::Vector2 pos) { mPos = pos; }
		void SetOffset(math::Vector2 offset) { mOffset = offset; }
		math::Vector2& GetPos() { return mPos; }
		math::Vector2& GetOffset() { return mOffset; }

	private:
		enums::eColliderType mType;
		bool isCollision;

		math::Vector2 mPos;
		math::Vector2 mOffset;

	};
}

