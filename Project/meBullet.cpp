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
		LeftImage = ResourceManager::Load<Texture>(L"bullet_L", L"..\\content\\BossFight\\Cuphead\\Bullet\\BulletImage\\Idle_L_0008.bmp");
		RightImage = ResourceManager::Load<Texture>(L"bullet_R", L"..\\content\\BossFight\\Cuphead\\Bullet\\BulletImage\\Idle_R_0008.bmp");

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
		if (mDirection.y == 1)
		{
			if (flip)
			{
				dir = -1;
				renderer->SetImage(DiagonalDownLefttImage);
				CircleCollider* collider = GetComponent<CircleCollider>();
				collider->SetOffset(math::Vector2(-52.5f, 0));
			}
			else
			{
				renderer->SetImage(DiagonalDownRightImage);
				CircleCollider* collider = GetComponent<CircleCollider>();
				collider->SetOffset(math::Vector2(52.5f, 0));
			}

			if (mDirection.x == 0)
			{
				renderer->SetImage(DownImage);
			}
		}
		else if (mDirection.y == -1)
		{
			if (flip)
			{
				dir = -1;
				renderer->SetImage(DiagonalUpLefttImage);
				CircleCollider* collider = GetComponent<CircleCollider>();
				collider->SetOffset(math::Vector2(-52.5f, 0));
			}
			else
			{
				renderer->SetImage(DiagonalUpRightImage);
				CircleCollider* collider = GetComponent<CircleCollider>();
				collider->SetOffset(math::Vector2(52.5f, 0));
			}

			if (mDirection.x == 0)
			{
				renderer->SetImage(UpImage);
			}
		}
		else
		{
			if (flip)
			{
				dir = -1;
				renderer->SetImage(LeftImage);
				CircleCollider* collider = GetComponent<CircleCollider>();
				collider->SetOffset(math::Vector2(-52.5f, 0));
			}
			else
			{
				renderer->SetImage(RightImage);
				CircleCollider* collider = GetComponent<CircleCollider>();
				collider->SetOffset(math::Vector2(52.5f, 0));
			}
		}

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