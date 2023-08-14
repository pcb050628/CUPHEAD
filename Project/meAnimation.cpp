#include "meAnimation.h"
#include "meResourceManager.h"
#include "meTexture.h"

namespace me
{
	Animation::Animation(const std::wstring& _name) : Resource(_name)
		, mType(enums::eAnimType::None)
		, mIdx(0)
		, mSheet(NULL), mStartPoint(math::Vector2::Zero), mUnitX(0)
		, mSheetCount(0), mSheetSliceUnit(0)
		, mDuration(0.085f)
		, mComplete(false)
		, mLoop(true)
		, alpha(1)
	{
		mTextures = {};
	}
	Animation::~Animation()
	{
		mTextures.clear();
		mSheet = nullptr;
	}

	bool Animation::Load(const std::wstring& path)
	{
		WIN32_FIND_DATA findFileData;
		HANDLE hFind;

		hFind = FindFirstFile((path + L"*.bmp").c_str(), &findFileData);

		if (hFind == INVALID_HANDLE_VALUE)
			return false;
		else
		{
			mType = enums::eAnimType::Folder;

			std::wstring FullPath = path + findFileData.cFileName;
			Texture* image = ResourceManager::Load<Texture>(findFileData.cFileName, FullPath.c_str());
			mTextures.push_back(image);

			while (FindNextFile(hFind, &findFileData) != 0)
			{
				std::wstring FullPath = path + findFileData.cFileName;
				Texture* image = ResourceManager::Load<Texture>(findFileData.cFileName, FullPath.c_str());
				mTextures.push_back(image);
			}

			FindClose(hFind);
			return true;
		}
	}

	bool Animation::Load(const std::wstring& name, const std::wstring& SheetsPath, math::Vector2 startp, int sliceUnit, int image_count)
	{
		mSheet = ResourceManager::Load<Texture>(name, SheetsPath.c_str());

		if (mSheet == nullptr)
			return false;
		else
		{
			mType = enums::eAnimType::Sheet;
			mSheetCount = image_count;
			mSheetSliceUnit = sliceUnit;
			mStartPoint = startp;
			mUnitX = mSheet->GetWidth() / sliceUnit;

			return true;
		}
	}

	bool Animation::Load(const std::wstring& path, eTextureType type)
	{
		WIN32_FIND_DATA findFileData;
		HANDLE hFind = {};

		if(type == eTextureType::bmp)
			hFind = FindFirstFile((path + L"*.bmp").c_str(), &findFileData);
		else if (type == eTextureType::png)
			hFind = FindFirstFile((path + L"*.png").c_str(), &findFileData);

		if (hFind == INVALID_HANDLE_VALUE)
			return false;
		else
		{
			mType = enums::eAnimType::Folder;

			std::wstring FullPath = path + findFileData.cFileName;
			Texture* image = ResourceManager::Load<Texture>(findFileData.cFileName, FullPath.c_str());
			mTextures.push_back(image);

			while (FindNextFile(hFind, &findFileData) != 0)
			{
				std::wstring FullPath = path + findFileData.cFileName;
				Texture* image = ResourceManager::Load<Texture>(findFileData.cFileName, FullPath.c_str());
				mTextures.push_back(image);
			}

			FindClose(hFind);
			return true;
		}
	}

	void Animation::Render(HDC hdc, math::Vector2 pos, math::Vector2 scale)
	{
		if (mType == enums::eAnimType::Folder)
		{
			if (mTextures[mIdx]->GetType() == eTextureType::bmp)
			{
				TransparentBlt(hdc
					, pos.x - (mTextures[mIdx]->GetWidth() * scale.x / 2) + mOffset.x
					, pos.y - (mTextures[mIdx]->GetHeight() * scale.y / 2) + mOffset.y
					, mTextures[mIdx]->GetWidth() * scale.x
					, mTextures[mIdx]->GetHeight() * scale.y
					, mTextures[mIdx]->GetHdc(), 0, 0, mTextures[mIdx]->GetWidth(), mTextures[mIdx]->GetHeight(), RGB(255, 0, 255));
			}
			else if (mTextures[mIdx]->GetType() == eTextureType::png)
			{
				Gdiplus::Graphics graphics(hdc);
				Gdiplus::Rect rect = { 
					(INT)(pos.x - ((mTextures[mIdx]->GetWidth() * scale.x) / 2) + mOffset.x)
					, (INT)(pos.y - ((mTextures[mIdx]->GetHeight() * scale.y) / 2) + mOffset.y)
					, (INT)(mTextures[mIdx]->GetWidth() * scale.x)
					, (INT)(mTextures[mIdx]->GetHeight() * scale.y) 
				};

				graphics.DrawImage
				(
					mTextures[mIdx]->GetImage()
					, rect
					, 0, 0
					, mTextures[mIdx]->GetWidth(), mTextures[mIdx]->GetHeight()
					, Gdiplus::UnitPixel
				);
			}
		}
		else if (mType == enums::eAnimType::Sheet)
		{
			if (mSheet->GetType() == eTextureType::bmp)
			{
				TransparentBlt(hdc
					, pos.x - ((mUnitX * scale.x) / 2) + mOffset.x
					, pos.y - ((mUnitX * scale.y) / 2) + mOffset.y
					, mUnitX * scale.x, mUnitX * scale.y
					, mSheet->GetHdc()
					, mIdx * mUnitX + mStartPoint.x, mStartPoint.y
					, mUnitX, mUnitX, RGB(255, 0, 255));
			}
			else if (mSheet->GetType() == eTextureType::png)
			{
				Gdiplus::Graphics graphics(hdc);
				Gdiplus::Rect rect = { 
					(INT)((pos.x - ((mUnitX * scale.x) / 2)) + mOffset.x)
					, (INT)((pos.y - ((mUnitX * scale.y) / 2)) + mOffset.y)
					, (INT)(mUnitX * scale.x)
					, (INT)(mUnitX * scale.y) 
				};

				graphics.DrawImage
				(
					mSheet->GetImage()
					, rect
					, mIdx * mUnitX + mStartPoint.x, mStartPoint.y
					, mUnitX, mUnitX 
					, Gdiplus::UnitPixel
				);
			}
		}
	}
}