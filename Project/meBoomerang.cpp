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
		//������ �������� �̵� ( ó������ ����
	}
	void Boomerang::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Boomerang::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetTag() == enums::eGameObjType::player)
			dynamic_cast<Player_stage*>(other->GetOwner())->GetHit();

		//wall�� �浹�ϸ� ��ġ�� ���� �Ʒ� ���������� �ٲ㼭 �̵��ϰ� �����, ���������� ���ư��� �� �̾��ٸ� destroy ȣ���ϱ�
	}
	void Boomerang::OnCollisionStay(Collider* other)
	{
	}
	void Boomerang::OnCollisionExit(Collider* other)
	{
	}
}