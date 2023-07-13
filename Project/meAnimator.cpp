#include "meAnimator.h"
#include "meTexture.h"
#include "meTransform.h"
#include "meCamera.h"
#include "meGameObject.h"
#include "meResourceManager.h"

namespace me
{
	Animator::Animator(GameObject* gobj) : Component(enums::eComponentType::Animator, gobj)
		, mIdx(0)
		, mScale(math::Vector2::One)
		, mAffectCamera(true)
	{
		mTextures = {};
	}
	Animator::~Animator()
	{
	}

	void Animator::Init()
	{
	}
	void Animator::Update()
	{
	}
	void Animator::Render(HDC hdc)
	{
		if (mIdx >= mTextures.size())
			mIdx = 0;

		Transform* tr = GetOwner()->GetComponent<Transform>();
		math::Vector2 pos = tr->GetPos();

		if (mAffectCamera)
			pos = Camera::AffectCameraPos(pos);

		if (!mTextures.empty())
		{
			if (mTextures[mIdx]->GetType() == eTextureType::bmp)
			{
				TransparentBlt(hdc, pos.x - (mTextures[mIdx]->GetWidth() * mScale.x / 2), pos.y - (mTextures[mIdx]->GetHeight() * mScale.y / 2)
					, mTextures[mIdx]->GetWidth() * mScale.x, mTextures[mIdx]->GetHeight() * mScale.y
					, mTextures[mIdx]->GetHdc(), 0, 0, mTextures[mIdx]->GetWidth(), mTextures[mIdx]->GetHeight(), RGB(255, 0, 255));
				mIdx++;
			}
			else if (mTextures[mIdx]->GetType() == eTextureType::png)
			{
				Gdiplus::Graphics graphics(hdc);
				Gdiplus::Rect rect = { (INT)(pos.x - ((mTextures[mIdx]->GetWidth() * mScale.x) / 2)), (INT)(pos.y - ((mTextures[mIdx]->GetHeight() * mScale.y) / 2))
					, (INT)(mTextures[mIdx]->GetWidth() * mScale.x), (INT)(mTextures[mIdx]->GetHeight() * mScale.y) };

				graphics.DrawImage
				(
					mTextures[mIdx]->GetImage()
					, rect
					, 0, 0
					, mTextures[mIdx]->GetWidth(), mTextures[mIdx]->GetHeight()
					, Gdiplus::UnitPixel
				);
				mIdx++;
			}
		}
	}

	bool Animator::AddAnimation(const std::wstring& FolderPath)
	{
		WIN32_FIND_DATA findFileData;
		HANDLE hFind;

		hFind = FindFirstFile((FolderPath + L"*.png").c_str(), &findFileData);

		if (hFind == INVALID_HANDLE_VALUE)
			return false;
		else
		{
			while (FindNextFile(hFind, &findFileData) != 0)
			{
				std::wstring FullPath = FolderPath + findFileData.cFileName;
				Texture* image = ResourceManager::Load<Texture>(findFileData.cFileName, FullPath.c_str());
				mTextures.push_back(image);
			}

			FindClose(hFind);
			return true;
		}
	}
}