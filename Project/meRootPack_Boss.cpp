#include "meRootPack_Boss.h"

namespace me
{
	RootPack_Boss::RootPack_Boss(const std::wstring& name) : Boss(name)
	{
	}
	RootPack_Boss::~RootPack_Boss()
	{
	}
	void RootPack_Boss::Init()
	{
		Boss::Init();

		mMainCollider = AddComponent<CircleCollider>(enums::eComponentType::Collider);

		mMainAnimator = AddComponent<Animator>(enums::eComponentType::Animator);
	}
	void RootPack_Boss::Update()
	{
		Boss::Update();
	}
	void RootPack_Boss::Render(HDC hdc)
	{
		Boss::Render(hdc);
	}
	void RootPack_Boss::OnCollisionEnter(Collider* other)
	{
	}
	void RootPack_Boss::OnCollisionStay(Collider* other)
	{
	}
	void RootPack_Boss::OnCollisionExit(Collider* other)
	{
	}
	void RootPack_Boss::Intro()
	{
	}
	void RootPack_Boss::Phase1()
	{
	}
	void RootPack_Boss::Phase2()
	{
	}
	void RootPack_Boss::Phase3()
	{
	}
	void RootPack_Boss::Death()
	{
	}
}