#pragma once
#include "meBossFightScene.h"
#include "mePlatform.h"

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

		Platform* platform1;
		Platform* platform2;
		Platform* platform3;
	};
}

