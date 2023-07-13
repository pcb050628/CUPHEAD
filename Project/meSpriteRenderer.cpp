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
			pos = Camera::AffectCameraPos(pos);

		if (mTexture != nullptr)
		{
			if (mTexture->GetType() == eTextureType::bmp)
			{
				TransparentBlt(hdc, pos.x - (mTexture->GetWidth() * mScale.x * mFlipX / 2), pos.y - (mTexture->GetHeight() * mScale.y / 2)
					, mTexture->GetWidth() * mScale.x * mFlipX, mTexture->GetHeight() * mScale.y
					, mTexture->GetHdc(), 0, 0, mTexture->GetWidth(), mTexture->GetHeight(), RGB(255, 0, 255));
			}
			else if (mTexture->GetType() == eTextureType::png)
			{
				Gdiplus::Graphics graphics(hdc);
				Gdiplus::Rect rect = { (int)(pos.x - ((mWidht * mScale.x * mFlipX) / 2)), (int)(pos.y - ((mHeight * mScale.y) / 2))
					, (int)(mWidht * mScale.x * mFlipX), (int)(mHeight * mScale.y) };


				graphics.DrawImage
				(
					mTexture->GetImage()
					, rect
					, mStartPointX, mStartPointY
					, mWidht, mHeight
					, Gdiplus::UnitPixel
				);
			}
		}

		wchar_t bufferx[50] = {};
		wchar_t buffery[50] = {};

		swprintf_s(bufferx, L"x : %f", pos.x);
		swprintf_s(buffery, L"y : %f", pos.y);
		int strLen1 = wcsnlen_s(bufferx, 50);
		int strLen2 = wcsnlen_s(buffery, 50);

		TextOut(hdc, 10, 50, bufferx, strLen1);
		TextOut(hdc, 10, 100, buffery, strLen2);
	}
}