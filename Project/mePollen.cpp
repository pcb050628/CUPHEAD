#include "mePollen.h"
#include "meResourceManager.h"
#include "meSceneManager.h"

namespace me
{
	Pollen::Pollen(const std::wstring& name) : GameObject(name, enums::eGameObjType::enemy)
		, mTransform(nullptr), mCollider(nullptr), mAnimator(nullptr)
		, button(false)
	{
	}
	Pollen::~Pollen()
	{
	}
	void Pollen::Init()
	{
		GameObject::Init();

		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<CircleCollider>(enums::eComponentType::Collider);
		mAnimator = AddComponent<Animator>(enums::eComponentType::Animator);

		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"pollen"
			, L"..\\content\\Scene\\BossFight\\Cagney Carnation\\Final Form\\Firing Pollen\\Pollen\\B\\"));

		mAnimator->PlayAnim(L"pollen");
	}
	void Pollen::Update()
	{
		GameObject::Update();

		float x = mTransform->GetPos().x;
		float y = mTransform->GetPos().y;

		if (button)
			y -= 100 * Time::GetDeltaTime();
		else
			y += 100 * Time::GetDeltaTime();

		x -= 400 * Time::GetDeltaTime();

		mTransform->SetPos(x, y);

		if (fabs(y) >= 60)
		{
			if (button)
				button = false;
			else
				button = true;
		}
	}
	void Pollen::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Pollen::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetTag() == enums::eGameObjType::player)
		{
			dynamic_cast<Player_stage*>(other->GetOwner())->GetHit();
		}

		if (other->GetOwner()->GetTag() == enums::eGameObjType::wall)
			SceneManager::Destroy(this);
	}
	void Pollen::OnCollisionStay(Collider* other)
	{
	}
	void Pollen::OnCollisionExit(Collider* other)
	{
	}
}