#include "meRootPack_Stage.h"

namespace me
{
	RootPack_Stage::RootPack_Stage(std::wstring name) : BossFightScene(name)
	{
	}

	RootPack_Stage::~RootPack_Stage()
	{
	}

	void RootPack_Stage::Init()
	{
		BossFightScene::Init();
	}

	void RootPack_Stage::Setting()
	{
		BossFightScene::Setting();
	}

	void RootPack_Stage::Update()
	{
		BossFightScene::Update();
	}

	void RootPack_Stage::Render(HDC hdc)
	{
		BossFightScene::Render(hdc);
	}

	void RootPack_Stage::Clear()
	{
		BossFightScene::Clear();
	}
}
