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

		virtual void OnCollisionEnter(BoxCollider* other);
		virtual void OnCollisionStay(BoxCollider* other);
		virtual void OnCollisionExit(BoxCollider* other);

		void SetDirection(math::Vector2 dir) { mDirection = dir; }
		math::Vector2 GetDirection() { return mDirection; }

		void SetFlip(bool value) { flip = value; }
		bool GetFlip() { return flip; }

	private:
		math::Vector2 mDirection;
		bool flip;

		SpriteRenderer* renderer;
		Texture* LeftImage;
		Texture* RightImage;
		Texture* DiagonalUpLefttImage;
		Texture* DiagonalUpRightImage;
		Texture* DiagonalDownLefttImage;
		Texture* DiagonalDownRightImage;
		Texture* UpImage;
		Texture* DownImage;
	};
}

