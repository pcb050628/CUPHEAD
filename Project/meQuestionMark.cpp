#include "meQuestionMark.h"
#include "mePlayer_stage.h"
#include "meSceneManager.h"

me::QuestionMark::QuestionMark(const std::wstring& name) : Sensor(name)
	 , mAnimator(nullptr)
{
}

me::QuestionMark::~QuestionMark()
{
}

void me::QuestionMark::Init()
{
	Sensor::Init();

	SetParryable(true);
}

void me::QuestionMark::Update()
{
	Sensor::Update();
}

void me::QuestionMark::Render(HDC hdc)
{
	Sensor::Render(hdc);
}

void me::QuestionMark::OnCollisionEnter(Collider* other)
{

}

void me::QuestionMark::OnCollisionStay(Collider* other)
{
	if (dynamic_cast<Player_stage*>(other->GetOwner()) != nullptr && dynamic_cast<Player_stage*>(other->GetOwner())->isParrySuccess())
		SceneManager::Destroy(this);
}

void me::QuestionMark::OnCollisionExit(Collider* other)
{
}
