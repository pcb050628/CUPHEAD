#include "meQuestionMark.h"
#include "mePlayer_stage.h"
#include "meSceneManager.h"
#include "meResourceManager.h"

me::QuestionMark::QuestionMark(const std::wstring& name) : Sensor(name)
	, mAnimator(nullptr)
	, time(0)
{
}

me::QuestionMark::~QuestionMark()
{
}

void me::QuestionMark::Init()
{
	Sensor::Init();

	SetParryable(true);

	mAnimator = AddComponent<Animator>(enums::eComponentType::Animator);

	mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Question_Mark_Appear", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 1\\Question Marks\\Appear\\"));
	mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"Question_Mark_Disappear", L"..\\content\\Scene\\BossFight\\Goopy Le Grande\\Phase 1\\Question Marks\\Disappear\\"));

	mAnimator->GetAnim(L"Question_Mark_Appear")->SetLoop(false);
	mAnimator->GetAnim(L"Question_Mark_Disappear")->SetLoop(false);

	mAnimator->GetAnim(L"Question_Mark_Appear")->SetDuration(0.05f);
	mAnimator->GetAnim(L"Question_Mark_Disappear")->SetDuration(0.05f);

	mAnimator->PlayAnim(L"Question_Mark_Appear");
}

void me::QuestionMark::Update()
{
	Sensor::Update();

	time += Time::GetDeltaTime();

	if (time >= 3)
		Disappear();
}

void me::QuestionMark::Render(HDC hdc)
{
	Sensor::Render(hdc);
}

void me::QuestionMark::OnCollisionEnter(Collider* other)
{
	if (dynamic_cast<Player_stage*>(other->GetOwner()) != nullptr && dynamic_cast<Player_stage*>(other->GetOwner())->isParrySuccess())
	{
		Disappear();
	}
}

void me::QuestionMark::OnCollisionStay(Collider* other)
{
	if (dynamic_cast<Player_stage*>(other->GetOwner()) != nullptr && dynamic_cast<Player_stage*>(other->GetOwner())->isParrySuccess())
	{
		Disappear();
	}
}

void me::QuestionMark::OnCollisionExit(Collider* other)
{
}

void me::QuestionMark::Disappear()
{
	mAnimator->PlayAnim(L"Question_Mark_Disappear");
	SceneManager::Destroy(this);
}
