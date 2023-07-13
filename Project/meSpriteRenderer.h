#pragma once
#include "DEFAULT.h"
#include "meComponent.h"
#include "meTexture.h"

namespace me
{
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer(GameObject* gobj);
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

		virtual void SetWidth(UINT width) { mWidht = width; }
		virtual void SetHeight(UINT height) { mHeight = height; }
		virtual void SetStartPointX(UINT x) { mStartPointX = x; }
		virtual void SetStartPointY(UINT y) { mStartPointY = y; }
		
	private:
		Texture* mTexture;

		UINT mStartPointX;
		UINT mStartPointY;

		UINT mWidht;
		UINT mHeight;

		math::Vector2 mScale;

		bool mAffectCamera;
	};
}

