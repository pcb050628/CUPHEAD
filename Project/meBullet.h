#pragma once
#include "meGameObject.h"

namespace me
{	
	class Bullet : public GameObject
	{
	public:
		Bullet(const std::wstring& name);
		virtual ~Bullet() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void SetDirection(math::Vector2 dir, bool value) 
		{ 
			mDirection = dir;
			flip = value;
			if (mDirection.y == 1)
			{
				if (flip)
				{
					mAnimator->PlayAnim(L"bullet_anim_diagonal_down", flip);
					CircleCollider* collider = GetComponent<CircleCollider>();
					collider->SetOffset(math::Vector2(-52.5f, 0));
				}
				else
				{
					mAnimator->PlayAnim(L"bullet_anim_diagonal_down", flip);
					CircleCollider* collider = GetComponent<CircleCollider>();
					collider->SetOffset(math::Vector2(52.5f, 0));
				}

				if (mDirection.x == 0)
				{
					mAnimator->PlayAnim(L"bullet_anim_down");

					if (flip)
						DownAnim->SetOffset(math::Vector2(-52.5f, 0));
					else
						DownAnim->SetOffset(math::Vector2(52.5f, 0));
				}
			}
			else if (mDirection.y == -1)
			{
				if (flip)
				{
					mAnimator->PlayAnim(L"bullet_anim_diagonal_up", flip);
					CircleCollider* collider = GetComponent<CircleCollider>();
					collider->SetOffset(math::Vector2(-52.5f, 0));
				}
				else
				{
					mAnimator->PlayAnim(L"bullet_anim_diagonal_up", flip);
					CircleCollider* collider = GetComponent<CircleCollider>();
					collider->SetOffset(math::Vector2(52.5f, 0));
				}

				if (mDirection.x == 0)
				{
					mAnimator->PlayAnim(L"bullet_anim_up");
					if(flip)
						UpAnim->SetOffset(math::Vector2(-52.5f, 0));
					else
						UpAnim->SetOffset(math::Vector2(52.5f, 0));
				}
			}
			else
			{
				if (flip)
				{
					mAnimator->PlayAnim(L"bullet_anim_straight", flip);
					CircleCollider* collider = GetComponent<CircleCollider>();
					collider->SetOffset(math::Vector2(-52.5f, 0));
				}
				else
				{
					mAnimator->PlayAnim(L"bullet_anim_straight", flip);
					CircleCollider* collider = GetComponent<CircleCollider>();
					collider->SetOffset(math::Vector2(52.5f, 0));
				}
			}
		}
		math::Vector2 GetDirection() { return mDirection; }

		void SetFlip(bool value) { flip = value; }
		bool GetFlip() { return flip; }

		int ReturnDmg() { return damage; }

	private:
		int damage;

		math::Vector2 mDirection;
		bool flip;

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

