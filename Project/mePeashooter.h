#pragma once
#include "meBullet.h"

namespace me
{
	class Peashooter : public Bullet
	{
	public:
		Peashooter(const std::wstring& name);
		virtual ~Peashooter() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;


		void SetDirection(math::Vector2 dir, bool value)
		{
			mDirection = dir;
			SetFlip(value);
			if (mDirection.y == 1)
			{
				if (GetFlip())
				{
					mAnimator->PlayAnim(L"bullet_anim_diagonal_down", GetFlip());
					CircleCollider* collider = GetComponent<CircleCollider>();
					collider->SetOffset(math::Vector2(-52.5f, 0));
				}
				else
				{
					mAnimator->PlayAnim(L"bullet_anim_diagonal_down", GetFlip());
					CircleCollider* collider = GetComponent<CircleCollider>();
					collider->SetOffset(math::Vector2(52.5f, 0));
				}

				if (mDirection.x == 0)
				{
					mAnimator->PlayAnim(L"bullet_anim_down");

					if (GetFlip())
						DownAnim->SetOffset(math::Vector2(-52.5f, 0));
					else
						DownAnim->SetOffset(math::Vector2(52.5f, 0));
				}
			}
			else if (mDirection.y == -1)
			{
				if (GetFlip())
				{
					mAnimator->PlayAnim(L"bullet_anim_diagonal_up", GetFlip());
					CircleCollider* collider = GetComponent<CircleCollider>();
					collider->SetOffset(math::Vector2(-52.5f, 0));
				}
				else
				{
					mAnimator->PlayAnim(L"bullet_anim_diagonal_up", GetFlip());
					CircleCollider* collider = GetComponent<CircleCollider>();
					collider->SetOffset(math::Vector2(52.5f, 0));
				}

				if (mDirection.x == 0)
				{
					mAnimator->PlayAnim(L"bullet_anim_up");
					if (GetFlip())
						UpAnim->SetOffset(math::Vector2(-52.5f, 0));
					else
						UpAnim->SetOffset(math::Vector2(52.5f, 0));
				}
			}
			else
			{
				if (GetFlip())
				{
					mAnimator->PlayAnim(L"bullet_anim_straight", GetFlip());
					CircleCollider* collider = GetComponent<CircleCollider>();
					collider->SetOffset(math::Vector2(-52.5f, 0));
				}
				else
				{
					mAnimator->PlayAnim(L"bullet_anim_straight", GetFlip());
					CircleCollider* collider = GetComponent<CircleCollider>();
					collider->SetOffset(math::Vector2(52.5f, 0));
				}
			}
		}
		math::Vector2 GetDirection() { return mDirection; }
	private:

		math::Vector2 mDirection;

		Animator* mAnimator;

		Animation* LeftAnim;
		Animation* RightAnim;
		Animation* DiagonalUpLeftAnim;
		Animation* DiagonalUpRightAnim;
		Animation* DiagonalDownLeftAnim;
		Animation* DiagonalDownRightAnim;
		Animation* UpAnim;
		Animation* DownAnim;
	};
}

