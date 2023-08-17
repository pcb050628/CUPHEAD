#include "meCarrotMissile.h"
#include "meResourceManager.h"
#include "meSceneManager.h"

namespace me
{
	CarrotMissile::CarrotMissile(const std::wstring& name) : GameObject(name, enums::eGameObjType::enemy)
		, mTransform(nullptr)
		, mCollider(nullptr)
		, mSpriteRenderer(nullptr)
		, Target(nullptr)
		, crash(false)
		, hp(24)
		, timeCount(0)
	{
	}
	CarrotMissile::~CarrotMissile()
	{
	}
	void CarrotMissile::Init()
	{
		GameObject::Init();

		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<CircleCollider>(enums::eComponentType::Collider);
		mSpriteRenderer = AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);

		mCollider->SetRadius(20.f);

		mSpriteRenderer->SetImage(ResourceManager::Load<Texture>(L"Carrot", L"..\\content\\Scene\\BossFight\\The Root Pack\\carrot\\attack\\missile\\carrot_missile.bmp"));
		mSpriteRenderer->SetScale(math::Vector2(0.8f, 0.8f));
	}
	void CarrotMissile::Update()
	{
		GameObject::Update();

		timeCount += Time::GetDeltaTime();

		if (Target != nullptr)
		{
			float x = mTransform->GetPos().x;
			float y = mTransform->GetPos().y;

			if (Target->GetPos().x > x)
				x += 100 * Time::GetDeltaTime();
			else
				x -= 100 * Time::GetDeltaTime();

			if (Target->GetPos().y > y)
				y += 100 * Time::GetDeltaTime();
			else
				y -= 100 * Time::GetDeltaTime();

			mTransform->SetPos(x, y);
		}

		if (timeCount >= 5 || crash)
		{
			SceneManager::Destroy(this);
		}
	}
	void CarrotMissile::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void CarrotMissile::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetTag() == enums::eGameObjType::player)
		{
			crash = true;
			dynamic_cast<Player_stage*>(other->GetOwner())->GetHit();
		}
	}
	void CarrotMissile::OnCollisionStay(Collider* other)
	{
	}
	void CarrotMissile::OnCollisionExit(Collider* other)
	{
	}
}