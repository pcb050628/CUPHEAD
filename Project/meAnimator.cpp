#include "meAnimator.h"
#include "meTexture.h"
#include "meTransform.h"
#include "meCamera.h"
#include "meGameObject.h"
#include "meResourceManager.h"

namespace me
{
	Animator::Animator(GameObject* gobj, const std::wstring& name) : Component(enums::eComponentType::Animator, gobj, name)
		, mCurPlayAnim(nullptr)
		, mScale(math::Vector2::One)
		, mOffset(math::Vector2::Zero)
		, mAffectCamera(true)
		, isFlipX(false)
		, isFlipY(false)
		, isPlay(false)
		, mAlpha(1)
		, flashing(false)
		, flashingLoop(false)
		, flashingDuration(0.1f)
		, prevFlahsingTime(NULL)
	{
		mAnims = {};
	}
	Animator::~Animator()
	{
		mAnims.clear();
	}

	void Animator::Init()
	{
	}
	void Animator::Update()
	{
		if (mCurPlayAnim == nullptr && mNextAnims != nullptr)
		{
			mCurPlayAnim = mNextAnims;
			mNextAnims = nullptr;
		}

		if (flashing)
		{
			if (fabs(prevFlahsingTime - Time::GetTime()) > flashingDuration)
			{
				if (mAlpha == 1)
				{
					mAlpha = 0.5f;
					prevFlahsingTime = Time::GetTime();
				}
				else
				{
					mAlpha = 1;
					prevFlahsingTime = Time::GetTime();
					if(!flashingLoop)
						flashing = false;
				}
			}
		}

		if (mCurPlayAnim != nullptr)
		{
			mCurPlayAnim->SetAlpha(mAlpha);
		}
	}
	void Animator::Render(HDC hdc)
	{
		if (mCurPlayAnim != nullptr /*&& !mCurPlayAnim->IsComplete()*/)
		{
			Transform* tr = GetOwner()->GetComponent<Transform>(L"defaultTransform");
			math::Vector2 pos = tr->GetPos();

			if (mAffectCamera)
				Camera::AffectCameraPos(pos);

			if (mCurPlayAnim->GetType() == enums::eAnimType::Sheet && mCurPlayAnim->GetSheet()->GetType() == eTextureType::png)
			{
				math::Vector2 flipV = {};

				if (isFlipX)
					flipV = math::Vector2(-1, 1);
				else
					flipV = math::Vector2(1, 1);

				mCurPlayAnim->Render(hdc, pos + mOffset, mScale * flipV);
			}
			else
			{
				mCurPlayAnim->Render(hdc, pos + mOffset, mScale);
			}

			if (isPlay)
			{
				if (!mCurPlayAnim->IsComplete() && mCurPlayAnim->GetPrevTime() + mCurPlayAnim->GetDuration() < Time::GetTime())
				{
					mCurPlayAnim->SetPrevTime(Time::GetTime());
					mCurPlayAnim->Next();

					if (!mCurPlayAnim->IsLoop() && mCurPlayAnim->IsComplete() && nullptr == mNextAnims)
					{
						isPlay = false;
						mCurPlayAnim->SetIdx(mCurPlayAnim->GetIdx() - 1);
						mCurPlayAnim->SetComplete(true);
					}
				}
			}

			if (mCurPlayAnim->IsComplete())
			{
				if (mCurPlayAnim->IsLoop())
					mCurPlayAnim->Reset();
				
				
				if (nullptr != mNextAnims)
				{
					mCurPlayAnim = mNextAnims;
					mNextAnims = nullptr;
				}
			}
		}
	}
}