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
	enum class eTextureType;

	class Animation : public Resource
	{
	public:
		Animation(const std::wstring& _name);
		virtual ~Animation() override;

		virtual bool Load(const std::wstring& path) override;
		virtual bool Load(const std::wstring& name, const std::wstring& SheetsPath, math::Vector2 startp, int sliceUnit, int image_count);
		virtual bool Load(const std::wstring& path, eTextureType type);

		virtual void Render(HDC hdc, math::Vector2 pos, math::Vector2 scale);

		virtual void SetStartPoint(math::Vector2 startPoint) { mStartPoint = startPoint; }

		virtual bool IsComplete() {
			if (mTextures.size() > 0 && mIdx >= mTextures.size())
				mComplete = true;
			else if (mSheet != nullptr && mSheetCount <= mIdx)
				mComplete = true;

			return mComplete;
		}

		virtual void SetComplete(bool value) { mComplete = value; }

		virtual bool IsLoop() { return mLoop; }
		virtual void SetLoop(bool value) { mLoop = value; }

		virtual void Next() { mIdx += 1; }
		virtual void Reset() { mIdx = 0; mComplete = false; }

		virtual void SetSpriteSheet(Texture* texture) { mSheet = texture; }
		virtual void SetAnimType(enums::eAnimType type) { mType = type; }
		virtual void SetSheetCount(int count) { mSheetCount = count; }
		virtual void SetUnit(float unit) { mUnitX = unit; }
		virtual void SetDuration(float duration) { mDuration = duration; }
		virtual void SetIdx(int idx) { mIdx = idx; }
		virtual void SetOffset(math::Vector2 offset) { mOffset = offset; }

		virtual int GetIdx() { return mIdx; }

		virtual Texture* GetSheet() { return mSheet; }
		virtual float GetDuration() { return mDuration; }
		virtual float GetPrevTime() { return prevTime; }
		virtual void SetPrevTime(float time) { prevTime = time; }
		virtual math::Vector2 GetOffset() { return mOffset; }

		virtual enums::eAnimType GetType() { return mType; }

		virtual void SetAlpha(float value) { alpha = value; }
		virtual float GetAlpha() { return alpha; }

	private:
		enums::eAnimType mType;

		math::Vector2 mOffset;

		std::vector<Texture*> mTextures;
		int mIdx;

		float alpha;

		Texture* mSheet;
		int mSheetCount;
		int mSheetSliceUnit;
		math::Vector2 mStartPoint;
		float mUnitX;

		float mDuration;
		float prevTime;

		bool mComplete;
		bool mLoop;
	};
}