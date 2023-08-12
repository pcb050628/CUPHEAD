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
	GameObject* bgRenderer = AddGameObj<GameObject>(enums::eLayer::Background, L"bgRenderer");
	GameObject* resultRenderer = AddGameObj<GameObject>(enums::eLayer::Background, L"resultRenderer");

	bg = bgRenderer->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
	result = resultRenderer->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);

	bg->SetImage(ResourceManager::Load<Texture>(L"clearSceneBG", L"..\\content\\clearScene\\winscreen_bg.bmp"));
	result->SetImage(ResourceManager::Load<Texture>(L"clearSceneBG", L"..\\content\\clearScene\\winscreen_results_title_korean_0003.bmp"));
}

void me::ClearScene::Setting()
{
}

void me::ClearScene::Update()
{
}

void me::ClearScene::Render(HDC hdc)
{
}
