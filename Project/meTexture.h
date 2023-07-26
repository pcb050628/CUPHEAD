#pragma once
#include "meResource.h"

namespace me
{
	enum class eTextureType
	{
		png,
		bmp,
		none
	};
	
	class Texture : public Resource
	{
	public:
		Texture(const std::wstring& _name);
		virtual ~Texture() override;

		virtual bool Load(const std::wstring& path) override;

		Gdiplus::Image* GetImage() { return mImage; }

		HDC GetHdc() { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

		void SetOffset(math::Vector2 offset) { mOffset = offset; }
		math::Vector2 GetOffset() { return mOffset; }

		eTextureType GetType() { return mType; }

	private:
		eTextureType mType;

		Gdiplus::Image* mImage;

		HBITMAP	mBitMap;
		HDC		mHdc;

		UINT	mWidth;
		UINT	mHeight;
		math::Vector2 mOffset;
	};
}
