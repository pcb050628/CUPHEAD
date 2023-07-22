#pragma once
#include "meComponent.h"

namespace me
{	
	class BoxCollider : public Component
	{
	public:
		BoxCollider(GameObject* gobj, const std::wstring& name);
		virtual ~BoxCollider() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void OnCollisionEnter(BoxCollider* other);
		void OnCollisionStay(BoxCollider* other);
		void OnCollisionExit(BoxCollider* other);

		void SetPos(math::Vector2 pos) { mPos = pos; }
		void SetOffset(math::Vector2 offset) { mOffset = offset; }
		void SetSize(math::Vector2 scale) { mSize= scale; }
		math::Vector2 GetPos() { return mPos; }
		math::Vector2 GetOffset() { return mOffset; }
		math::Vector2 GetSize() { return mSize; }

		GameObject* GetCollidedGobj();

	private:
		math::Vector2 mPos;
		math::Vector2 mOffset;
		math::Vector2 mSize;

		bool isCollision;
		GameObject* CollidedObjcet;
	};
}

