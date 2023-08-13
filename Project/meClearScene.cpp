#include "meClearScene.h"
#include "meResourceManager.h"

me::ClearScene::ClearScene(std::wstring name) : Scene(name)
	, bg(nullptr)
	, result(nullptr)
{
}

me::ClearScene::~ClearScene()
{
	delete bg;
	delete result;
}

void me::ClearScene::Init()
{
	Scene::Init();

	GameObject* bgRenderer = AddGameObj(enums::eLayer::Background, L"1clear_background", enums::eGameObjType::background);
	GameObject* resultRenderer = AddGameObj(enums::eLayer::Background, L"0clear_result", enums::eGameObjType::background);

	bg = bgRenderer->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
	result = resultRenderer->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);

	bg->SetImage(ResourceManager::Load<Texture>(L"clearSceneBG", L"..\\content\\Scene\\clearScene\\winscreen_bg.bmp"));
	result->SetImage(ResourceManager::Load<Texture>(L"clearSceneText", L"..\\content\\Scene\\clearScene\\winscreen_results_title_korean_0003.bmp"));
}

void me::ClearScene::Setting()
{
	Scene::Setting();
}

void me::ClearScene::Update()
{
	Scene::Update();
}

void me::ClearScene::Render(HDC hdc)
{
	Scene::Render(hdc);
}
