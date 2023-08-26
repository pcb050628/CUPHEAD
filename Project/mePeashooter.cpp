#include "mePeashooter.h"
#include "meResourceManager.h"
#include "meSceneManager.h"

namespace me
{
	Peashooter::Peashooter(const std::wstring& name) : Bullet(name)
		, mAnimator(nullptr)
		, mDirection(math::Vector2(1, 0))
	{
	}
	Peashooter::~Peashooter()
	{
	}
	void Peashooter::Init()
	{
		Bullet::Init();

		LeftAnim = ResourceManager::Load<Animation>(L"bullet_anim_straight_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Bullet\\Left\\");
		RightAnim = ResourceManager::Load<Animation>(L"bullet_anim_straight_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Bullet\\Right\\");
		UpAnim = ResourceManager::Load<Animation>(L"bullet_anim_up", L"..\\content\\Scene\\BossFight\\Cuphead\\Bullet\\Up\\");
		DownAnim = ResourceManager::Load<Animation>(L"bullet_anim_down", L"..\\content\\Scene\\BossFight\\Cuphead\\Bullet\\Down\\");
		DiagonalUpLeftAnim = ResourceManager::Load<Animation>(L"bullet_anim_diagonal_up_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Bullet\\Diagonal Up\\Left\\");
		DiagonalUpRightAnim = ResourceManager::Load<Animation>(L"bullet_anim_diagonal_up_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Bullet\\Diagonal Up\\Right\\");
		DiagonalDownLeftAnim = ResourceManager::Load<Animation>(L"bullet_anim_diagonal_down_L", L"..\\content\\Scene\\BossFight\\Cuphead\\Bullet\\Diagonal Down\\Left\\");
		DiagonalDownRightAnim = ResourceManager::Load<Animation>(L"bullet_anim_diagonal_down_R", L"..\\content\\Scene\\BossFight\\Cuphead\\Bullet\\Diagonal Down\\Right\\");

		mAnimator = AddComponent<Animator>(enums::eComponentType::Animator);
		mAnimator->AddAnim(*LeftAnim);
		mAnimator->AddAnim(*RightAnim);
		mAnimator->AddAnim(*UpAnim);
		mAnimator->AddAnim(*DownAnim);
		mAnimator->AddAnim(*DiagonalUpLeftAnim);
		mAnimator->AddAnim(*DiagonalUpRightAnim);
		mAnimator->AddAnim(*DiagonalDownLeftAnim);
		mAnimator->AddAnim(*DiagonalDownRightAnim);

		LeftAnim->SetLoop(false);
		RightAnim->SetLoop(false);
		UpAnim->SetLoop(false);
		DownAnim->SetLoop(false);
		DiagonalUpLeftAnim->SetLoop(false);
		DiagonalUpRightAnim->SetLoop(false);
		DiagonalDownLeftAnim->SetLoop(false);
		DiagonalDownRightAnim->SetLoop(false);

		DiagonalUpLeftAnim->SetOffset(math::Vector2(-52.5f, 0));
		DiagonalUpRightAnim->SetOffset(math::Vector2(52.5f, 0));
		DiagonalDownLeftAnim->SetOffset(math::Vector2(-52.5f, 0));
		DiagonalDownRightAnim->SetOffset(math::Vector2(52.5f, 0));
	}
	void Peashooter::Update()
	{
		Bullet::Update();

		float dir = 1;

		if (GetFlip())
			dir = -1;

		mDirection.normalize();

		Transform* tr = GetComponent<Transform>();
		tr->SetPos(tr->GetPos() + ((mDirection * math::Vector2(dir, 1)) * 1000 * Time::GetDeltaTime()));

		GetComponent<Animator>()->PlayAnim(L"bulletidle", GetFlip());
	}
	void Peashooter::Render(HDC hdc)
	{
		Bullet::Render(hdc);
	}
	void Peashooter::OnCollisionEnter(Collider* other)
	{
		Bullet::OnCollisionEnter(other);

		if (other->GetOwner()->GetTag() != enums::eGameObjType::player
			&& other->GetOwner()->GetTag() != enums::eGameObjType::platform)
			mAnimator->SetActivate(false);
	}
	void Peashooter::OnCollisionStay(Collider* other)
	{
	}
	void Peashooter::OnCollisionExit(Collider* other)
	{
		if (!mAnimator->GetActivate())
			SceneManager::Destroy(this);
	}
}