#pragma once
#include "meResource.h"

namespace me
{
	namespace enums
	{
		enum class eAnimType
		{
			Folder,
			Sheet,
			None
		};
	}

	class Texture;

	class Animation : public Resource
	{
	public:
		Animation(const std::wstring& _name);
		virtual ~Animation() override;

		virtual bool Load(const std::wstring& path) override;
		virtual bool Load(const std::wstring& name, const std::wstring& SheetsPath, math::Vector2 startp, int sliceUnit, int image_count);

		virtual void Render(HDC hdc, math::Vector2 pos, math::Vector2 scale);

		virtual void SetStartPoint(math::Vector2 startPoint) { mStartPoint = startPoint; }

		virtual bool IsComplete() {
			if (mTextures.size() > 0 && mIdx >= mTextures.size())
				return true;
			else if (mSheet != nullptr && mSheetCount <= mIdx)
				return true;

			return false;
		}

		virtual bool IsLoop() { return mLoop; }
		virtual void SetLoop(bool value) { mLoop = value; }

		virtual void Next() { mIdx += 1; }
		virtual void Reset() { mIdx = 0; }

		virtual void SetSpriteSheet(Texture* texture) { mSheet = texture; }
		virtual void SetAnimType(enums::eAnimType type) { mType = type; }
		virtual void SetSheetCount(int count) { mSheetCount = count; }
		virtual void SetUnit(float unit) { mUnitX = unit; }
		virtual void SetDuration(float duration) { mDuration = duration; }

		virtual Texture* GetSheet() { return mSheet; }
		virtual float GetDuration() { return mDuration; }

	private:
		enums::eAnimType mType;

		std::vector<Texture*> mTextures;
		int mIdx;

		Texture* mSheet;
		int mSheetCount;
		int mSheetSliceUnit;
		math::Vector2 mStartPoint;
		float mUnitX;

		float mDuration;
		bool mComplete;
		bool mLoop;
	};
}