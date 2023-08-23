#include "mePlatform.h"
#include "meResourceManager.h"
#include "mePlayer_stage.h"

namespace me
{
	Platform::Platform(const std::wstring& name) : GameObject(name, enums::eGameObjType::platform)
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, mCollider(nullptr)
	{
	}
	Platform::~Platform()
	{
		mTransform = nullptr;
		mAnimator = nullptr;
		mCollider = nullptr;
	}

	void Platform::Init()
	{
		GameObject::Init();

		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>(enums::eComponentType::Animator);
		mCollider = AddComponent<BoxCollider>(enums::eComponentType::Collider);

		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Platform_anim", L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Platform\\Platform\\"));
		mAnimator->PlayAnim(L"Platform_anim");

		mCollider->SetOffset(math::Vector2(0, 5));
		mCollider->SetSize(math::Vector2(120, 50));
	}
	void Platform::Update()
	{
		GameObject::Update();
	}
	void Platform::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Platform::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetTag() == enums::eGameObjType::player && other->GetOwner()->GetComponent<Transform>()->GetPos().y < mTransform->GetPos().y)
		{
			dynamic_cast<Player_stage*>(other->GetOwner())->SetIsGround(true);
			dynamic_cast<Player_stage*>(other->GetOwner())->SetGroundType(Player_stage::GroundType::platform);

			float len = fabs(other->GetPos().y - mCollider->GetPos().y);
			float scale = fabs((dynamic_cast<BoxCollider*>(other)->GetSize().y / 2) + (mCollider->GetSize().y / 2));

			if (len < scale)
			{
				Transform* tr = other->GetOwner()->GetComponent<Transform>();
				math::Vector2 PlayerPos = tr->GetPos();
				PlayerPos.y -= (scale - len) + 10.f;

				tr->SetPos(PlayerPos);
			}
		}
	}
	void Platform::OnCollisionStay(Collider* other)
	{
	}
	void Platform::OnCollisionExit(Collider* other)
	{
		if (other->GetOwner()->GetTag() == enums::eGameObjType::player)
			dynamic_cast<Player_stage*>(other->GetOwner())->SetIsGround(false);
	}
}