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

		CircleCollider* collider = AddComponent<CircleCollider>(enums::eComponentType::Collider);

		renderer = AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);
		LeftImage = ResourceManager::Load<Texture>(L"bullet_L", L"..\\content\\BossFight\\Cuphead\\Bullet\\BulletImage\\Idle_L.bmp");
		RightImage = ResourceManager::Load<Texture>(L"bullet_R", L"..\\content\\BossFight\\Cuphead\\Bullet\\BulletImage\\Idle_R.bmp");
		UpImage = ResourceManager::Load<Texture>(L"bullet_Up", L"..\\content\\BossFight\\Cuphead\\Bullet\\BulletImage\\Idle_up.bmp");
		DownImage = ResourceManager::Load<Texture>(L"bullet_Down", L"..\\content\\BossFight\\Cuphead\\Bullet\\BulletImage\\Idle_down.bmp");
		DiagonalUpLeftImage = ResourceManager::Load<Texture>(L"bullet_diagonal_up_L", L"..\\content\\BossFight\\Cuphead\\Bullet\\BulletImage\\idle_diagonal_up_L.bmp");
		DiagonalUpRightImage = ResourceManager::Load<Texture>(L"bullet_diagonal_up_R", L"..\\content\\BossFight\\Cuphead\\Bullet\\BulletImage\\Idle_diagonal_up_R.bmp");
		DiagonalDownLeftImage = ResourceManager::Load<Texture>(L"bullet_diagonal_down_L", L"..\\content\\BossFight\\Cuphead\\Bullet\\BulletImage\\Idle_diagonal_down_L.bmp");
		DiagonalDownRightImage = ResourceManager::Load<Texture>(L"bullet_diagonal_down_R", L"..\\content\\BossFight\\Cuphead\\Bullet\\BulletImage\\Idle_diagonal_down_R.bmp");

		

		/*Animator* Anim = AddComponent<Animator>(enums::eComponentType::Animator);
		Anim->AddAnim(ResourceManager::Load<Animation>(L"bulletidle_R", L"..\\content\\BossFight\\Cuphead\\Bullet\\Idle_R\\"));
		Anim->AddAnim(ResourceManager::Load<Animation>(L"bulletidle_L", L"..\\content\\BossFight\\Cuphead\\Bullet\\Idle_L\\"));
		Anim->GetAnim(L"bulletidle_R")->SetLoop(false);
		Anim->GetAnim(L"bulletidle_L")->SetLoop(false);
		Anim->GetAnim(L"bulletidle_R")->SetDuration(0.1f);
		Anim->GetAnim(L"bulletidle_L")->SetDuration(0.1f);
		GetComponent<Animator>()->PlayAnim(L"bulletidle", flip);*/
	}
	void Bullet::Update()
	{
		GameObject::Update();

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
	void Bullet::OnCollisionEnter(Collider* other)
	{
		for (Component* comp : GetAllComponent())
		{
			comp->SetActivate(false);
		}

		SetActive(false);

		if (other->GetOwner()->GetTag() == enums::eGameObjType::enemy)
		{
			if(dynamic_cast<Boss*>(other->GetOwner()) != nullptr)
				dynamic_cast<Boss*>(other->GetOwner())->SetHP(dynamic_cast<Boss*>(other->GetOwner())->GetHP() - 4);
		}
	}
	void Bullet::OnCollisionStay(Collider* other)
	{
	}
	void Bullet::OnCollisionExit(Collider* other)
	{
	}
}