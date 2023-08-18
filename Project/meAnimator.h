#pragma once
#include "meComponent.h"
#include "meAnimation.h"

namespace me
{
	class Texture;

	class Animator : public Component
	{
	public:
		Animator(GameObject* gobj, const std::wstring& name);
		virtual ~Animator() override;

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void SetScale(math::Vector2 scale) { mScale = scale; }
		virtual void SetOffset(math::Vector2 offset) { mOffset = offset; }
		math::Vector2 GetOffset() { return mOffset; }

		virtual void SetFlipX(bool value) { isFlipX = value; }
		virtual void SetFlipY(bool value) { isFlipY = value; }

		virtual void AddAnim(Animation anim)
		{
			auto iter = mAnims.find(anim.GetName());
			if(iter == mAnims.end())
				mAnims.insert(std::make_pair(anim.GetName(), anim));
		}

		virtual void ForcePlayAnim(const std::wstring& name)
		{
			auto iter = mAnims.find(name);
			if (iter != mAnims.end())
			{
				mCurPlayAnim = &iter->second;
				isPlay = true;
				mCurPlayAnim->Reset();
			}
		}

		virtual void ForcePlayAnim(const std::wstring& name, bool flip)
		{
			std::wstring _name = name;

			if (flip)
				_name += L"_L";
			else
				_name += L"_R";

			auto iter = mAnims.find(_name);

			if (iter != mAnims.end())
			{
				mCurPlayAnim = &iter->second;
				mCurPlayAnim->Reset();
				isPlay = true;
			}
		}

		virtual void PlayAnim(const std::wstring& name)
		{
			auto iter = mAnims.find(name);
			if (iter != mAnims.end() && mCurPlayAnim != &iter->second)
			{
				mCurPlayAnim = &iter->second;
				isPlay = true;
				mCurPlayAnim->Reset();
			}
		}

		virtual void PlayAnim(const std::wstring& name, bool flip)
		{
			std::wstring _name = name;

			if (flip)
				_name += L"_L";
			else
				_name += L"_R";

			auto iter = mAnims.find(_name);
			if (iter != mAnims.end() && mCurPlayAnim != &iter->second)
			{
				mCurPlayAnim = &iter->second;
				isPlay = true;
				mCurPlayAnim->Reset();
			}
		}

		virtual void PlayAnim(const std::wstring& name, float duration)
		{
			auto iter = mAnims.find(name);
			if (iter != mAnims.end() && mCurPlayAnim != &iter->second)
			{
				mCurPlayAnim = &iter->second;
				isPlay = true;
				mCurPlayAnim->Reset();
				mCurPlayAnim->SetDuration(duration);
			}
		}

		virtual void NextPlayAnim(const std::wstring& name)
		{
			auto iter = mAnims.find(name);
			if (iter != mAnims.end())
			{
				mNextAnims = &iter->second;
			}
		}

		virtual void NextPlayAnim(const std::wstring& name, bool flip)
		{
			std::wstring _name = name;

			if (flip)
				_name += L"_L";
			else
				_name += L"_R";

			auto iter = mAnims.find(_name);
			if (iter != mAnims.end())
			{
				mNextAnims = &iter->second;
			}
		}

		virtual void StopPlay()
		{
			mCurPlayAnim = nullptr;
			isPlay = false;
		}

		virtual Animation* GetAnim(const std::wstring& name)
		{
			auto iter = mAnims.find(name);
			if (iter == mAnims.end())
				return nullptr;
			else
				return &iter->second;
		}

		virtual Animation* GetCurAnim() { return mCurPlayAnim; }

		virtual bool GetFlipX() { return isFlipX; }
		virtual bool GetFlipY() { return isFlipY; }

	private:
		std::map<std::wstring, Animation> mAnims;
		Animation* mCurPlayAnim;

		Animation* mNextAnims;

		math::Vector2 mScale;
		math::Vector2 mOffset;
		float mAlpha; // 알파값이 렌더에 적용되게 만들기

		bool isFlipX;
		bool isFlipY;

		bool isPlay;

		bool mAffectCamera;
	};
}

