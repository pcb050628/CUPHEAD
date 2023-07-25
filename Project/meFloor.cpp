#include "meFloor.h"

namespace me
{
	Floor::Floor(const std::wstring& name) : GameObject(name, enums::eGameObjType::floor)
	{
	}
	Floor::~Floor()
	{
	}
	void Floor::Init()
	{
		GameObject::Init();

		BoxCollider* floor_col = AddComponent<BoxCollider>(enums::eComponentType::Collider);
		floor_col->SetOffset(math::Vector2(0, 300.f));
		floor_col->SetSize(math::Vector2(1600, 50.f));
	}
	void Floor::Update()
	{
		GameObject::Update();
	}
	void Floor::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Floor::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetTag() == enums::eGameObjType::player)
		{			
			BoxCollider* box = GetComponent<BoxCollider>();
			BoxCollider* otherBox = dynamic_cast<BoxCollider*>(other);

			if (box->GetPos().y - box->GetSize().y / 2 < otherBox->GetPos().y + otherBox->GetSize().y / 2)
			{
				Transform* tr = other->GetOwner()->GetComponent<Transform>();
				/*float len = fabs(other->GetSize().y / 2 + box->GetSize().y / 2);
				float dif = fabs(box->GetPos().x - other->GetPos().y);

				len -= dif;
				tr->SetPos(tr->GetPos() + math::Vector2(0, -len));*/

				float len = box->GetPos().y - 460 - tr->GetPos().y;
				tr->SetPos(tr->GetPos() + math::Vector2(0, len));
			}
		}
	}
	void Floor::OnCollisionStay(Collider* other)
	{
	}
	void Floor::OnCollisionExit(Collider* other)
	{
	}
}