#include "meSpriteRenderer.h"
#include "meCamera.h"
#include "meGameObject.h"
#include "meTransform.h"
#include "meResourceManager.h"

namespace me
{
	SpriteRenderer::SpriteRenderer(GameObject* gobj, const std::wstring& name) : Component(enums::eComponentType::SpriteRenderer, gobj, name)
		, mTexture(nullptr)
		, mScale(math::Vector2::One)
		, mFlipX(1)
		, mAffectCamera(true)
	{
		
	}
	SpriteRenderer::~SpriteRenderer()
	{
	}
	void SpriteRenderer::Init()
	{
	}
	void SpriteRenderer::Update()
	{
	}

	void SpriteRenderer::Render(HDC hdc)
	{
		Transform* tr =  GetOwner()->GetComponent<Transform>();
		math::Vector2 pos = tr->GetPos();

		if(mAffectCamera)
			Camera::AffectCameraPos(pos);

		if (mTexture != nullptr)
		{
			if (mTexture->GetType() == eTextureType::bmp)
			{
				TransparentBlt(hdc
					, pos.x - (mTexture->GetWidth() * mScale.x * mFlipX / 2) + mTexture->GetOffset().x
					, pos.y - (mTexture->GetHeight() * mScale.y / 2) + mTexture->GetOffset().y
					, mTexture->GetWidth() * mScale.x * mFlipX, mTexture->GetHeight() * mScale.y
					, mTexture->GetHdc(), 0, 0, mTexture->GetWidth(), mTexture->GetHeight(), RGB(255, 0, 255));
			}
			else if (mTexture->GetType() == eTextureType::png)
			{
				Gdiplus::Graphics graphics(hdc);
				Gdiplus::Rect rect = 
				{ 
					(int)(pos.x - ((mWidht * mScale.x * mFlipX) / 2) + mTexture->GetOffset().x)
					, (int)(pos.y - ((mHeight * mScale.y) / 2) + mTexture->GetOffset().y)
					, (int)(mWidht * mScale.x * mFlipX)
					, (int)(mHeight * mScale.y) 
				};


				graphics.DrawImage
				(
					mTexture->GetImage()
					, rect
					, mStartPointX, mStartPointY
					, mWidht, mHeight
					, Gdiplus::UnitPixel
				);
			}
			else if(mTexture->GetType() == eTextureType::bmp32)
			{
				BLENDFUNCTION bf = {};
				bf.BlendOp = AC_SRC_OVER; // 무조건 AC_SRC_OVER이어야 하고 원본과 대상 이미지를 합친다는 의미
				bf.BlendFlags = 0; // 무조건 0이어야 한다
				bf.AlphaFormat = AC_SRC_ALPHA; // 비트맵 종류로 일반 비트맵의 경우 0, 32비트 비트맵의 경우 AC_SRC_ALPHA
				bf.SourceConstantAlpha = 255; // 투명도(투명 0 - 불투명 255)

				AlphaBlend(
					hdc
					, (int)(pos.x - (mTexture->GetWidth() * mTexture->GetWidth() / 2) + mTexture->GetOffset().x)
					, (int)(pos.y - (mTexture->GetHeight() * mTexture->GetHeight() / 2) + mTexture->GetOffset().y)
					, (int)(mTexture->GetWidth() * mScale.x)
					, (int)(mTexture->GetHeight() * mScale.y)
					, mTexture->GetHdc()
					, 0, 0
					, (int)mTexture->GetWidth(), (int)mTexture->GetHeight(), bf);
			}
		}
	}
}