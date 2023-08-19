#include "meBullet.h"
#include "meResourceManager.h"
#include "meSceneManager.h"

namespace me
{
	Bullet::Bullet(const std::wstring& name) : GameObject(name, enums::eGameObjType::bullet)
		, mAnimator(nullptr)
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
	void Bullet::Update()
	{
		GameObject::Update();

		float dir = 1;

		if (flip)
			dir = -1;

		mDirection.normalize();

		Transform* tr = GetComponent<Transform>();
		tr->SetPos(tr->GetPos() + ((mDirection * math::Vector2(dir, 1)) * 1000 * Time::GetDeltaTime()));

		GetComponent<Animator>()->PlayAnim(L"bulletidle", flip);
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
				dynamic_cast<Boss*>(other->GetOwner())->GetHit(4);
		}
		
		if(other->GetOwner()->GetTag() != enums::eGameObjType::player)
			mAnimator->SetActivate(false);
	}
	void Bullet::OnCollisionStay(Collider* other)
	{
	}
	void Bullet::OnCollisionExit(Collider* other)
	{
		SceneManager::Destroy(this);
	}
}