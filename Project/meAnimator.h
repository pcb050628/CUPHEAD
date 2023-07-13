#pragma once
#include "meComponent.h"

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

	class Animator : public Component
	{
	public:

		Animator(GameObject* gobj, const std::wstring& name);
		virtual ~Animator() override;

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual bool AddAnimation(const std::wstring& FolderPath);
		virtual bool AddAnimationX(const std::wstring& name, const std::wstring& SheetsPath, float _UnitX);
		virtual bool AddAnimationY(const std::wstring& name, const std::wstring& SheetsPath, float _UnitY);

		virtual void SetScale(math::Vector2 scale) { mScale = scale; }

		virtual enums::eAnimType GetType() { return mType; }
		virtual float GetUnitX() { return UnitX; }
		virtual float GetUnitY() { return UnitY; }

	private:
		enums::eAnimType mType;

		std::vector<Texture*> mTextures;
		math::Vector2 mScale;
		int mIdx;

		Texture* mSheet;
		float UnitX;
		float UnitY;

		bool mAffectCamera;
	};
}

