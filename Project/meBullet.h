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

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void SetDirection(math::Vector2 dir) 
		{ 
			mDirection = dir;
			/*if (mDirection.y == 1)
			{
				if (flip)
				{
					renderer->SetImage(DiagonalDownLeftImage);
					DiagonalDownLeftImage->SetOffset(math::Vector2(0, -50));
					CircleCollider* collider = GetComponent<CircleCollider>();
					collider->SetOffset(math::Vector2(-52.5f, 0));
				}
				else
				{
					renderer->SetImage(DiagonalDownRightImage);
					DiagonalDownRightImage->SetOffset(math::Vector2(0, -50));
					CircleCollider* collider = GetComponent<CircleCollider>();
					collider->SetOffset(math::Vector2(52.5f, 0));
				}

				if (mDirection.x == 0)
				{
					if (flip)
						DownImage->SetOffset(math::Vector2(-50, 0));
					else
						DownImage->SetOffset(math::Vector2(50, 0));
					renderer->SetImage(DownImage);
				}
			}
			else if (mDirection.y == -1)
			{
				if (flip)
				{
					renderer->SetImage(DiagonalUpLeftImage);
					DiagonalUpLeftImage->SetOffset(math::Vector2(0, 50));
					CircleCollider* collider = GetComponent<CircleCollider>();
					collider->SetOffset(math::Vector2(-52.5f, 0));
				}
				else
				{
					renderer->SetImage(DiagonalUpRightImage);
					DiagonalUpRightImage->SetOffset(math::Vector2(0, 50));
					CircleCollider* collider = GetComponent<CircleCollider>();
					collider->SetOffset(math::Vector2(52.5f, 0));
				}

				if (mDirection.x == 0)
				{
					if (flip)
						UpImage->SetOffset(math::Vector2(-50, 0));
					else
						UpImage->SetOffset(math::Vector2(50, 0));
					renderer->SetImage(UpImage);
				}
			}
			else
			{
				if (flip)
				{
					renderer->SetImage(LeftImage);
					CircleCollider* collider = GetComponent<CircleCollider>();
					collider->SetOffset(math::Vector2(-52.5f, 0));
				}
				else
				{
					renderer->SetImage(RightImage);
					CircleCollider* collider = GetComponent<CircleCollider>();
					collider->SetOffset(math::Vector2(52.5f, 0));
				}
			}*/
		}
		math::Vector2 GetDirection() { return mDirection; }

		void SetFlip(bool value) { flip = value; }
		bool GetFlip() { return flip; }

	private:
		math::Vector2 mDirection;
		bool flip;

		SpriteRenderer* renderer;
		Texture* LeftImage;
		Texture* RightImage;
		Texture* DiagonalUpLeftImage;
		Texture* DiagonalUpRightImage;
		Texture* DiagonalDownLeftImage;
		Texture* DiagonalDownRightImage;
		Texture* UpImage;
		Texture* DownImage;
	};
}

