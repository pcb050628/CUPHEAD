#include "meChaser.h"
#include "meResourceManager.h"
#include "meSceneManager.h"

namespace me
{
	Chaser::Chaser(const std::wstring& name) : Bullet(name)
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, Target(nullptr)
	{
	}
	Chaser::~Chaser()
	{
	}
	void Chaser::Init()
	{
		Bullet::Init();

		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>(enums::eComponentType::Animator);

		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"chaser_idle", L"..\\content\\Scene\\BossFight\\Cuphead\\Chaser\\Normal\\Idle\\"));
		mAnimator->PlayAnim(L"chaser_idle");
	}
	void Chaser::Update()
	{
		Bullet::Update();

		math::Vector2 pos = mTransform->GetPos();

		if (!mAnimator->GetActivate())
		{
			mTransform->SetPos(mTransform->GetPos() + math::Vector2(700 * Time::GetDeltaTime(), 0));
		}
		else
		{
			if(Target == nullptr)
			{
				mTransform->SetPos(mTransform->GetPos() + math::Vector2(700 * Time::GetDeltaTime(), 0));

				Target = SceneManager::GetCurScene()->GetBoss()->GetHItPoint();
			}
			else
			{
				math::Vector2 targetPos = *Target;

				if (pos.x > targetPos.x)
					pos.x -= 500 * Time::GetDeltaTime();
				else if (pos.x < targetPos.x)
					pos.x += 500 * Time::GetDeltaTime();

				if (pos.y > targetPos.y)
					pos.y -= 500 * Time::GetDeltaTime();
				else if (pos.y < targetPos.y)
					pos.y += 500 * Time::GetDeltaTime();

				mTransform->SetPos(pos);
			}
		}
	}
	void Chaser::Render(HDC hdc)
	{
		Bullet::Render(hdc);
	}
	void Chaser::OnCollisionEnter(Collider* other)
	{
		Bullet::OnCollisionEnter(other);

		if (other->GetOwner()->GetTag() != enums::eGameObjType::player
			&& other->GetOwner()->GetTag() != enums::eGameObjType::platform)
		{
			mAnimator->SetActivate(false);
			SceneManager::Destroy(this);
		}
	}
	void Chaser::OnCollisionStay(Collider* other)
	{
	}
	void Chaser::OnCollisionExit(Collider* other)
	{
	}
}