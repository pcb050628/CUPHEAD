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
	{
		mAnims = {};
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
		static float prevTime = 0;

		if (mCurPlayAnim != nullptr && !mCurPlayAnim->IsComplete())
		{
			Transform* tr = GetOwner()->GetComponent<Transform>(L"defaultTransform");
			math::Vector2 pos = tr->GetPos();

			if (mAffectCamera)
				pos = Camera::AffectCameraPos(pos);

			mCurPlayAnim->Render(hdc, pos + mOffset, mScale);

			if (!mCurPlayAnim->IsComplete() && prevTime + mCurPlayAnim->GetDuration() /** Time::GetDeltaTime()*/ < Time::GetTime() && isPlay)
			{
				prevTime = Time::GetTime();
				mCurPlayAnim->Next();
			}

			if (mCurPlayAnim != nullptr && mCurPlayAnim->IsComplete())
			{
				mCurPlayAnim->Reset();
				if(!mCurPlayAnim->IsLoop() && mNextAnims.size() > 0)
				{
					mCurPlayAnim = mNextAnims.front();
					mNextAnims.pop();
				}
			}
		}
	}
}