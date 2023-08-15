#include "meDust.h"
#include "meResourceManager.h"
#include "meSceneManager.h"
#include "meBullet.h"

namespace me
{
	Dust::Dust(const std::wstring& name) : GameObject(name, enums::eGameObjType::enemy)
		, mTransform(nullptr)
		, mCollider(nullptr)
		, mAnimator(nullptr)
		, crash(false)
		, hp(12)
	{
	}
	Dust::~Dust()
	{
	}
	void Dust::Init()
	{
		GameObject::Init();

		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<CircleCollider>(enums::eComponentType::Collider);
		mAnimator = AddComponent<Animator>(enums::eComponentType::Animator);

		mCollider->SetRadius(50.f);

		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"dust_idle", L"..\\content\\Scene\\BossFight\\The Root Pack\\potato\\bullet\\idle\\"));
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"dust_crash", L"..\\content\\Scene\\BossFight\\The Root Pack\\potato\\bullet\\crash\\"));

		mAnimator->GetAnim(L"dust_crash")->SetLoop(false);
	}
	void Dust::Update()
	{
		GameObject::Update();

		if (hp <= 0)
			crash = true;

		if (crash)
		{
			mCollider->SetActivate(false);
			mAnimator->PlayAnim(L"dust_crash");

			if (mAnimator->GetCurAnim()->IsComplete())
				SceneManager::Destroy(this);
		}
		else
		{
			mAnimator->PlayAnim(L"dust_idle");
			mTransform->SetPos(mTransform->GetPos() + math::Vector2(-800 * Time::GetDeltaTime(), 0));
		}

	}
	void Dust::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Dust::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetTag() == enums::eGameObjType::wall)
		{
			mAnimator->SetActivate(false);
			mCollider->SetActivate(false);

			SceneManager::Destroy(this);
		}
		else if (other->GetOwner()->GetTag() == enums::eGameObjType::player)
		{
			dynamic_cast<Player_stage*>(other->GetOwner())->GetHit();
			crash = true;
		}
		else if (other->GetOwner()->GetTag() == enums::eGameObjType::bullet)
		{
			hp -= dynamic_cast<Bullet*>(other->GetOwner())->ReturnDmg();
		}
	}
	void Dust::OnCollisionStay(Collider* other)
	{
	}
	void Dust::OnCollisionExit(Collider* other)
	{
	}
}