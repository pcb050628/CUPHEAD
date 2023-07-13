#pragma once
#include "DEFAULT.h"
#include "meComponent.h"
#include "meTexture.h"

namespace me
{
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer(GameObject* gobj, const std::wstring& name);
		virtual ~SpriteRenderer() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void SetImage(Texture* texture) 
		{ 
			mTexture = texture; 
			if (mTexture != nullptr)
			{
				mWidht = mTexture->GetWidth();
				mHeight = mTexture->GetHeight();
			}
		}

		virtual void SetScale(math::Vector2 scale) { mScale = scale; }
		virtual math::Vector2 GetScale() { return mScale; }

		virtual void SetFlipX(bool flip) {
			if (flip)
				mFlipX = -1;
			else
				mFlipX = 1;
		}

		virtual bool IsFlipX() {
			if (mFlipX > 0)
				return false;
			else if (mFlipX < 0)
				return true;
		}

		virtual void SetWidth(ULONG width) { mWidht = width; }
		virtual void SetHeight(ULONG height) { mHeight = height; }
		virtual void SetStartPointX(ULONG x) { mStartPointX = x; }
		virtual void SetStartPointY(ULONG y) { mStartPointY = y; }
		
	private:
		Texture* mTexture;

		ULONG mStartPointX;
		ULONG mStartPointY;

		ULONG mWidht;
		ULONG mHeight;

		math::Vector2 mScale;
		float mFlipX;

		bool mAffectCamera;
	};
}

