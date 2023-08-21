#include "meBoomerang.h"
#include "meResourceManager.h"
#include "mePlayer_stage.h"

namespace me
{
	Boomerang::Boomerang(const std::wstring& name) : GameObject(name, enums::eGameObjType::enemy)
		, mTransform(nullptr)
		, mCollider(nullptr)
		, mAnimator(nullptr)
	{
	}
	Boomerang::~Boomerang()
	{
		mTransform = nullptr;
		mCollider = nullptr;
		mAnimator = nullptr;
	}
	void Boomerang::Init()
	{
		GameObject::Init();

		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<BoxCollider>(enums::eComponentType::Collider);
		mAnimator = AddComponent<Animator>(enums::eComponentType::Animator);

		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Boomerang", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Create Object\\Boomerang\\"));
		mAnimator->PlayAnim(L"Boomerang");
	}
	void Boomerang::Update()
	{
		GameObject::Update();
		//정해진 방향으로 이동 ( 처음에는 왼쪽
	}
	void Boomerang::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Boomerang::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetTag() == enums::eGameObjType::player)
			dynamic_cast<Player_stage*>(other->GetOwner())->GetHit();

		//wall에 충돌하면 위치와 방향 아래 오른쪽으로 바꿔서 이동하게 만들기, 오른쪽으로 돌아가는 중 이었다면 destroy 호출하기
	}
	void Boomerang::OnCollisionStay(Collider* other)
	{
	}
	void Boomerang::OnCollisionExit(Collider* other)
	{
	}
}