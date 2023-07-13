#include "meController.h"
#include "meGameObject.h"
#include "meTransform.h"

namespace me
{
	Controller::Controller(GameObject* gobj) : Component(enums::eComponentType::Controller, gobj)
	{
	}
	Controller::~Controller()
	{
	}

	void Controller::Init()
	{
	}
	void Controller::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		if (KeyInput::GetKey(KeyCode::UpArrow))
			tr->SetPos(math::Vector2(tr->GetPos().x, tr->GetPos().y - 100.f * Time::GetDeltaTime()));
		if (KeyInput::GetKey(KeyCode::DownArrow))
			tr->SetPos(math::Vector2(tr->GetPos().x, tr->GetPos().y + 100.f * Time::GetDeltaTime()));
		if (KeyInput::GetKey(KeyCode::LeftArrow))
			tr->SetPos(math::Vector2(tr->GetPos().x - 100.f * Time::GetDeltaTime(), tr->GetPos().y));
		if (KeyInput::GetKey(KeyCode::RightArrow))
			tr->SetPos(math::Vector2(tr->GetPos().x + 100.f * Time::GetDeltaTime(), tr->GetPos().y));
	}
	void Controller::Render(HDC hdc)
	{
	}
}