#include "meBullet.h"
#include "meResourceManager.h"
#include "meSceneManager.h"

namespace me
{
	Bullet::Bullet(const std::wstring& name) : GameObject(name, enums::eGameObjType::bullet)
		, mDirection(math::Vector2(1, 0))
		, flip(false)
	{
	}
	Bullet::~Bullet()
	{
	}
	void Bullet::Init()
	{
		GameObject::Init();

		BoxCollider* collider = AddComponent<BoxCollider>(enums::eComponentType::BoxCollider); 
		collider->SetSize(math::Vector2(100, 30));
		
		Animator* Anim = AddComponent<Animator>(enums::eComponentType::Animator);
		Anim->AddAnim(ResourceManager::Load<Animation>(L"bulletidle", L"..\\content\\BossFight\\Cuphead\\Bullet\\Idle\\"));
		Anim->GetAnim(L"bulletidle")->SetLoop(false);
	}
	void Bullet::Update()
	{
		GameObject::Update();

		GetComponent<Animator>()->PlayAnim(L"bulletIdle", flip);

		float dir = 1;
		if (flip)
			dir = -1;

		mDirection.normalize();

		Transform* tr = GetComponent<Transform>();
		tr->SetPos(tr->GetPos() + ((mDirection * math::Vector2(dir, 1)) * 600 * Time::GetDeltaTime()));
	}
	void Bullet::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Bullet::OnCollisionEnter(BoxCollider* other)
	{
		SceneManager::Destroy(this, enums::eLayer::Bullet);
	}
	void Bullet::OnCollisionStay(BoxCollider* other)
	{
	}
	void Bullet::OnCollisionExit(BoxCollider* other)
	{
	}
}