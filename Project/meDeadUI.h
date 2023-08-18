#pragma once
#include "meGameObject.h"

namespace me
{
	class DeadUI : public GameObject
	{
	public:
		DeadUI(const std::wstring& name);
		virtual ~DeadUI() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void Change();

		void SelectRetry() { mSpriteRenderer->SetImage(selectRetry); }
		void SelectToMap() { mSpriteRenderer->SetImage(selectToMap); }

	private:
		SpriteRenderer* mSpriteRenderer;
		Texture* selectRetry;
		Texture* selectToMap;


	};
}

