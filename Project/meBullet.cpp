#include "meBullet.h"
#include "meResourceManager.h"
#include "meSceneManager.h"
#include "meSensor.h"

namespace me
{
	Bullet::Bullet(const std::wstring& name) : GameObject(name, enums::eGameObjType::bullet)
		, damage(4)
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
	}
	void Bullet::Update()
	{
		GameObject::Update();
	}
	void Bullet::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Bullet::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetTag() == enums::eGameObjType::enemy)
		{
			if (dynamic_cast<Boss*>(other->GetOwner()) != nullptr)
				dynamic_cast<Boss*>(other->GetOwner())->GetHit(damage);
		}	
		else if (other->GetOwner()->GetTag() == enums::eGameObjType::sensor)
		{
			if (dynamic_cast<Boss*>(dynamic_cast<Sensor*>(other->GetOwner())->GetOwner()) != nullptr)
			{
				dynamic_cast<Boss*>(dynamic_cast<Sensor*>(other->GetOwner())->GetOwner())->GetHit(damage);
			}
		}
	}
	void Bullet::OnCollisionStay(Collider* other)
	{
	}
	void Bullet::OnCollisionExit(Collider* other)
	{
	}
}