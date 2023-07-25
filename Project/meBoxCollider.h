#pragma once
#include "meCollider.h"

namespace me
{	
	class BoxCollider : public Collider
	{
	public:
		BoxCollider(GameObject* gobj, const std::wstring& name);
		virtual ~BoxCollider() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void SetSize(math::Vector2 scale) { mSize= scale; }
		math::Vector2 GetSize() { return mSize; }

	private:
		math::Vector2 mSize;

	};
}

