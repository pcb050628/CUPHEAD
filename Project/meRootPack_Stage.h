#pragma once
#include "meBossFightScene.h"

namespace me
{	
	class RootPack_Stage : public BossFightScene
	{
	public:
		RootPack_Stage(std::wstring name);
		virtual ~RootPack_Stage() override;

		void Init() override;
		void Setting() override;
		void Update() override;
		void Render(HDC hdc) override;

		virtual void Clear() override;

	private:

	};
}

