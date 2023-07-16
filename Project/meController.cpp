#include "meController.h"
#include "meGameObject.h"
#include "meTransform.h"

namespace me
{
	Controller::Controller(GameObject* gobj, const std::wstring& name) : Component(enums::eComponentType::Controller, gobj, name)
		, mType(enums::eControlType::none)
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

		if (mType == enums::eControlType::map)
		{
			if (KeyInput::GetKey(KeyCode::UpArrow))
				tr->SetPos(math::Vector2(tr->GetPos().x, tr->GetPos().y - 100.f * Time::GetDeltaTime()));
			if (KeyInput::GetKey(KeyCode::DownArrow))
				tr->SetPos(math::Vector2(tr->GetPos().x, tr->GetPos().y + 100.f * Time::GetDeltaTime()));
			if (KeyInput::GetKey(KeyCode::LeftArrow))
				tr->SetPos(math::Vector2(tr->GetPos().x - 100.f * Time::GetDeltaTime(), tr->GetPos().y));
			if (KeyInput::GetKey(KeyCode::RightArrow))
				tr->SetPos(math::Vector2(tr->GetPos().x + 100.f * Time::GetDeltaTime(), tr->GetPos().y));
		}
		else if (mType == enums::eControlType::stage)
		{
			if(!KeyInput::GetKey(KeyCode::DownArrow) && !KeyInput::GetKey(KeyCode::C))
			{
				if (KeyInput::GetKey(KeyCode::LeftArrow))
					tr->SetPos(math::Vector2(tr->GetPos().x - 100.f * Time::GetDeltaTime(), tr->GetPos().y));
				if (KeyInput::GetKey(KeyCode::RightArrow))
					tr->SetPos(math::Vector2(tr->GetPos().x + 100.f * Time::GetDeltaTime(), tr->GetPos().y));
			}
		}
	}
	void Controller::Render(HDC hdc)
	{
	}
}