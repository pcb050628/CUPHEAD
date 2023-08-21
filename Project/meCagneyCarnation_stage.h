#pragma once
#include "meBossFightScene.h"

namespace me
{
	class CagneyCarnation_stage : public BossFightScene
	{
	public:
		CagneyCarnation_stage(std::wstring name);
		virtual ~CagneyCarnation_stage() override;

		void Init() override;
		void Setting() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Clear() override;

	private:
		Sound* bgm;

	};
}

