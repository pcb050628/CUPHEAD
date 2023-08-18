#include "meTexture.h"
#include "meApplication.h"

extern me::Application app;

namespace me
{
	Texture::Texture(const std::wstring& _name) : Resource(_name)
		, mType(eTextureType::none)
		, mWidth(0)
		, mHeight(0)
		, mImage(NULL)
		, mBitMap(NULL)
		, mHdc(NULL)
	{
	}
	Texture::~Texture()
	{
	}

	bool Texture::Load(const std::wstring& path)
	{
		std::wstring ext = path.substr(path.find_last_of(L".") + 1);

		if (ext == L"bmp")
		{
			mBitMap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0
				, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			if (mBitMap == nullptr)
				return false;

			mType = eTextureType::bmp;

			BITMAP info = {};
			GetObject(mBitMap, sizeof(BITMAP), &info);

			if (info.bmBitsPixel == 32)
				mType = eTextureType::bmp32;

			mWidth = info.bmWidth;
			mHeight = info.bmHeight;

			mHdc = CreateCompatibleDC(app.GetHDC());

			HBITMAP defaultBitMap = (HBITMAP)SelectObject(mHdc, mBitMap);
			DeleteObject(defaultBitMap);

			return true;
		}
		else if (ext == L"png")
		{
			mImage = Gdiplus::Image::FromFile(path.c_str());

			if (mImage == nullptr)
				return false;

			mType = eTextureType::png;

			mWidth = mImage->GetWidth();
			mHeight = mImage->GetHeight();

			return true;
		}
	}
} 