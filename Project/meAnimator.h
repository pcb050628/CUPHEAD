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

		virtual void SetFlipX(bool value) { isFlipX = value; }
		virtual void SetFlipY(bool value) { isFlipY = value; }

		virtual void AddAnim(Animation* anim)
		{
			mAnims.insert(std::make_pair(anim->GetName(), anim));
		}

		virtual void PlayAnim(const std::wstring& name)
		{
			auto iter = mAnims.find(name);
			if (iter != mAnims.end() && mCurPlayAnim != iter->second)
				mCurPlayAnim = iter->second;

			isPlay = true;
		}

		virtual void StopPlay()
		{
			isPlay = false;
		}

		virtual Animation* GetAnim(const std::wstring& name)
		{
			auto iter = mAnims.find(name);
			if (iter == mAnims.end())
				return nullptr;
			else
				return iter->second;
		}

		virtual Animation* GetCurAnim() { return mCurPlayAnim; }

	private:
		std::map<std::wstring, Animation*> mAnims;
		Animation* mCurPlayAnim;

		math::Vector2 mScale;
		math::Vector2 mOffset;

		bool isFlipX;
		bool isFlipY;

		bool isPlay;
		bool mLoop;

		bool mAffectCamera;
	};
}

