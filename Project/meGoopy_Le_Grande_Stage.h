#pragma once
#include "meBossFightScene.h"

namespace me
{
	class Goopy_Le_Grande_Stage : public BossFightScene
	{
	public:
		Goopy_Le_Grande_Stage(std::wstring name);
		virtual ~Goopy_Le_Grande_Stage() override;

		void Init() override;
		void Update() override;
		void Render(HDC hdc) override;

	private:

	};
}
