#include "meBoss.h"
#include "COMPONENTS.h"
#include "meResourceManager.h"

namespace me
{
	Boss::Boss(const std::wstring& name) : GameObject(name, enums::eGameObjType::enemy)
		, mHP(500)
	{
	}
	Boss::~Boss()
	{
	}
	void Boss::Init()
	{
		GameObject::Init();
	}
	void Boss::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case me::BossPhase_state::phase1:
			Phase1();
			break;
		case me::BossPhase_state::phase2:
			Phase2();
			break;
		case me::BossPhase_state::phase3:
			Phase3();
			break;
		case me::BossPhase_state::death:
			Death();
			break;
		}
	}
	void Boss::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Boss::Phase1()
	{
	}
	void Boss::Phase2()
	{
	}
	void Boss::Phase3()
	{
	}
	void Boss::Death()
	{
	}
}