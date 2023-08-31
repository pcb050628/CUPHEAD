#pragma once
#include "meGameObject.h"

namespace me
{
	class PauseUI : public GameObject
	{
	public:
		PauseUI(const std::wstring& name);
		virtual ~PauseUI() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void Change(bool value) {
			if (value)
			{
				if (mSpriteRenderer->GetImage() == selectRetry)
				{
					mSpriteRenderer->SetImage(selectContinue);
				}
				else if(mSpriteRenderer->GetImage() == selectToMap)
				{
					mSpriteRenderer->SetImage(selectRetry);
				}
			}
			else if (!value)
			{
				if (mSpriteRenderer->GetImage() == selectContinue)
				{
					mSpriteRenderer->SetImage(selectRetry);
				}
				else if (mSpriteRenderer->GetImage() == selectRetry)
				{
					mSpriteRenderer->SetImage(selectToMap);
				}
			}
		}

	private:
		SpriteRenderer* mSpriteRenderer;
		Texture*		selectContinue;
		Texture*		selectRetry;
		Texture*		selectToMap;

	};
}

