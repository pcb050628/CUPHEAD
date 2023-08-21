#include "meCagneyCarnation_stage.h"

namespace me
{
	CagneyCarnation_stage::CagneyCarnation_stage(std::wstring name) : BossFightScene(name)
		, bgm(nullptr)
	{
	}
y	CagneyCarnation_stage::~CagneyCarnation_stage()
	{
	}

	void CagneyCarnation_stage::Init()
	{
	}
	void CagneyCarnation_stage::Setting()
	{
		bgm->Play(true);
	}
	void CagneyCarnation_stage::Update()
	{
	}
	void CagneyCarnation_stage::Render(HDC hdc)
	{
	}
	void CagneyCarnation_stage::Clear()
	{
		bgm->Stop(true);
	}
}