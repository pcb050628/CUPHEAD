#include "meAnimator.h"
#include "meTexture.h"
#include "meTransform.h"
#include "meCamera.h"
#include "meGameObject.h"
#include "meResourceManager.h"

namespace me
{
	Animator::Animator(GameObject* gobj, const std::wstring& name) : Component(enums::eComponentType::Animator, gobj, name)
		, mType(enums::eAnimType::None)
		, mSheet(nullptr)
		, mIdx(0)
		, mScale(math::Vector2::One)
		, mAffectCamera(true)
		, UnitX(0.f)
		, UnitY(0.f)
		, mLoop(true)
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
		if (mIdx >= mTextures.size() && !mLoop)
			SetActivate(false);
		else if (mIdx >= mTextures.size() && mLoop)
			mIdx = 0;

		Transform* tr = GetOwner()->GetComponent<Transform>(L"defaultTransform");
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
			mType = enums::eAnimType::Folder;

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

	bool Animator::AddAnimationX(const std::wstring& name, const std::wstring& SheetsPath, float _UnitX)
	{
		mSheet = ResourceManager::Load<Texture>(name, SheetsPath.c_str());
		if (mSheet == nullptr)
			return false;
		else
		{
			mType = enums::eAnimType::Sheet;
			UnitX = _UnitX;

			return true;
		}
	}

	bool Animator::AddAnimationY(const std::wstring& name, const std::wstring& SheetsPath, float _UnitY)
	{
		mSheet = ResourceManager::Load<Texture>(name, SheetsPath.c_str());
		if (mSheet == nullptr)
			return false;
		else
		{
			mType = enums::eAnimType::Sheet;
			UnitY = _UnitY;

			return true;
		}
	}
}