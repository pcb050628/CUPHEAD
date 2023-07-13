#pragma once
#include "meComponent.h"

namespace me
{
	class Texture;

	class Animator : public Component
	{
	public:
		Animator(GameObject* gobj);
		virtual ~Animator() override;

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual bool AddAnimation(const std::wstring& FolderPath);

		virtual void SetScale(math::Vector2 scale) { mScale = scale; }

	private:
		std::vector<Texture*> mTextures;
		math::Vector2 mScale;
		int mIdx;

		bool mAffectCamera;
	};
}

