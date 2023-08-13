#include "meTItleScene.h"
#include "COMPONENTS.h"
#include "meResourceManager.h"
#include "meSceneManager.h"

namespace me
{
	TitleScene::TitleScene(std::wstring name) : Scene(name)
	{
	}
	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Init()
	{
		Scene::Init();

		GameObject* title_bg = AddGameObj(enums::eLayer::Background, L"title_background", enums::eGameObjType::background);
		Texture* image_title_bg = ResourceManager::Load<Texture>(L"title_background", L"..\\content\\Scene\\title screen\\Background\\title_screen_background.png");
		SpriteRenderer* title_bg_sr = title_bg->AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
		title_bg_sr->SetImage(image_title_bg);

		GameObject* title_character = AddGameObj(enums::eLayer::Background, L"title_character", enums::eGameObjType::background);
		title_character->GetComponent<Transform>()->SetPos(math::Vector2(0, 75));
		Animator* title_char_anim = title_character->AddComponent<Animator>(enums::eComponentType::Animator);
		title_char_anim->AddAnim(*ResourceManager::Load<Animation>(L"title_character", L"..\\content\\Scene\\title screen\\Cuphead and Mugman\\"));
		title_char_anim->PlayAnim(L"title_character");
		title_char_anim->GetCurAnim()->SetDuration(0.04f);

		bgm = ResourceManager::Load<Sound>(L"title_song", L"..\\content\\Sound\\AudioClip\\Title\\MUS_Intro_DontDealWithDevil_Vocal.wav");
		bgm->Play(true);
	}
	void TitleScene::Update()
	{
		Scene::Update();

		if (KeyInput::GetKeyDown(KeyCode::Enter))
		{
			SceneManager::LoadScene(L"main");
		}
	}
	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void TitleScene::Clear()
	{
		bgm->Stop(true);
	}
}