#include "meFloor.h"
#include "mePlayer_stage.h"

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
		if (other->GetOwner()->GetTag() == enums::eGameObjType::player 
			&& dynamic_cast<Player_stage*>(other->GetOwner())->GetPrevState() != Player_stage::Player_state::Duck
			&& dynamic_cast<Player_stage*>(other->GetOwner())->GetPrevState() != Player_stage::Player_state::Dash)
		{			
			BoxCollider* box = GetComponent<BoxCollider>();
			BoxCollider* otherBox = dynamic_cast<BoxCollider*>(other);

			float len = fabs(otherBox->GetPos().y - box->GetPos().y);
			float scale = fabs((otherBox->GetSize().y / 2) + (box->GetSize().y / 2));

			if (len < scale)
			{
				Transform* tr = other->GetOwner()->GetComponent<Transform>();
				math::Vector2 PlayerPos = tr->GetPos();
				PlayerPos.y -= (scale - len) + 10.f;

				tr->SetPos(PlayerPos);
			}
		}
		else if (other->GetOwner()->GetTag() == enums::eGameObjType::enemy)
		{
			BoxCollider* box = GetComponent<BoxCollider>();
			if (dynamic_cast<BoxCollider*>(other) == nullptr)
			{
				CircleCollider* otherCircle = dynamic_cast<CircleCollider*>(other);

				float len = fabs(otherCircle->GetPos().y - box->GetPos().y);
				float scale = fabs(otherCircle->GetRadius() + (box->GetSize().y / 2));

				if (len < scale)
				{
					Transform* tr = other->GetOwner()->GetComponent<Transform>();
					math::Vector2 otherPos = tr->GetPos();
					otherPos.y -= (scale - len) - 10.f;

					tr->SetPos(otherPos);
				}
			}
			else
			{
				BoxCollider* otherBox = dynamic_cast<BoxCollider*>(other);

				float len = fabs(otherBox->GetPos().y - box->GetPos().y);
				float scale = fabs((otherBox->GetSize().y / 2) + (box->GetSize().y / 2));

				if (len < scale)
				{
					Transform* tr = other->GetOwner()->GetComponent<Transform>();
					math::Vector2 otherPos = tr->GetPos();
					otherPos.y -= (scale - len) + 10.f;

					tr->SetPos(otherPos);
				}
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