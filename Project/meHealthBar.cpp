#include "meHealthBar.h"
#include "meResourceManager.h"

me::HealthBar::HealthBar(const std::wstring& name) : GameObject(name)
{
}

me::HealthBar::~HealthBar()
{
}

void me::HealthBar::Init()
{
	GameObject::Init();

	Health1 = AddComponent<SpriteRenderer>(L"healthBar1");
	Health2 = AddComponent<SpriteRenderer>(L"healthBar2");
	Health3 = AddComponent<SpriteRenderer>(L"healthBar3");
	Dead = AddComponent<SpriteRenderer>(L"healthBarDead");

	Health1->SetImage(ResourceManager::Load<Texture>(L"HealthBar_1", L"..\\content\\Scene\\BossFight\\CupHead\\Health\\Health_1.bmp"));
	Health2->SetImage(ResourceManager::Load<Texture>(L"HealthBar_2", L"..\\content\\Scene\\BossFight\\CupHead\\Health\\Health_2.bmp"));
	Health3->SetImage(ResourceManager::Load<Texture>(L"HealthBar_3", L"..\\content\\Scene\\BossFight\\CupHead\\Health\\Health_3.bmp"));
	Dead->SetImage(ResourceManager::Load<Texture>(L"HealthBar_dead", L"..\\content\\Scene\\BossFight\\CupHead\\Health\\Health_dead.bmp"));

	GetComponent<Transform>()->SetPos(math::Vector2(100, math::Vector2::Client_Size.y - 50));
	Health1->SetAffectCamera(false);
	Health2->SetAffectCamera(false);
	Health3->SetAffectCamera(false);
	Dead->SetAffectCamera(false);
}

void me::HealthBar::Update()
{
	GameObject::Update();

	if (mPlayer != nullptr && mPlayer->GetHP() == 3)
	{
		Health1->SetActivate(false);
		Health2->SetActivate(false);
		Health3->SetActivate(true);
		Dead->SetActivate(false);
	}
	else if (mPlayer != nullptr && mPlayer->GetHP() == 2)
	{
		Health1->SetActivate(false);
		Health2->SetActivate(true);
		Health3->SetActivate(false);
		Dead->SetActivate(false);
	}
	else if (mPlayer != nullptr && mPlayer->GetHP() == 1)
	{
		Health1->SetActivate(true);
		Health2->SetActivate(false);
		Health3->SetActivate(false);
		Dead->SetActivate(false);
	}
	else
	{
		Health1->SetActivate(false);
		Health2->SetActivate(false);
		Health3->SetActivate(false);
		Dead->SetActivate(true);
	}
}

void me::HealthBar::Render(HDC hdc)
{
	GameObject::Render(hdc);
}
