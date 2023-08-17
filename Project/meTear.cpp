#include "meTear.h"
#include "meResourceManager.h"
#include "mePlayer_stage.h"
#include "meSceneManager.h"

namespace me
{
	Tear::Tear(const std::wstring& name) : GameObject(name, enums::eGameObjType::enemy)
		, mTransform(nullptr)
		, mRigidbody(nullptr)
		, mCollider(nullptr)
		, mAnimator(nullptr)
		, mSpriteRenderer(nullptr)
		, splash(false)
	{
	}
	Tear::~Tear()
	{
	}

	void Tear::Init()
	{
		GameObject::Init();

		mTransform = GetComponent<Transform>();
		mRigidbody = AddComponent<Rigidbody>(enums::eComponentType::Rigidbody);
		mCollider = AddComponent<CircleCollider>(enums::eComponentType::Collider);
		mAnimator = AddComponent<Animator>(enums::eComponentType::Animator);
		mSpriteRenderer = AddComponent<SpriteRenderer>(enums::eComponentType::SpriteRenderer);

		mSpriteRenderer->SetImage(ResourceManager::Load<Texture>(L"tear_drop"
			, L"..\\content\\Scene\\BossFight\\The Root Pack\\onion\\Tears and Tear Drops\\Non Parryable\\Tear Drop A\\veggie_onion_tear_drop_a_0001.bmp"));

		mAnimator->SetActivate(false);
		mAnimator->AddAnim(*ResourceManager::Load<Animation>(L"tear_splash"
			, L"..\\content\\Scene\\BossFight\\The Root Pack\\onion\\Tears and Tear Drops\\Non Parryable\\Tear Drop A Splash\\"));
		mAnimator->GetAnim(L"tear_splash")->SetLoop(false);

	}
	void Tear::Update()
	{
		GameObject::Update();

		if (splash)
		{
			mCollider->SetActivate(false);
			mRigidbody->SetActivate(false);
			mSpriteRenderer->SetActivate(false);
			mAnimator->SetActivate(true);
			mAnimator->PlayAnim(L"tear_splash");

			if (mAnimator->GetCurAnim()->IsComplete())
				SceneManager::Destroy(this);
		}
	}
	void Tear::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Tear::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetTag() == enums::eGameObjType::floor)
		{
			splash = true;
		}
		else if (other->GetOwner()->GetTag() == enums::eGameObjType::player)
		{
			dynamic_cast<Player_stage*>(other->GetOwner())->GetHit();
		}
	}
	void Tear::OnCollisionStay(Collider* other)
	{
	}
	void Tear::OnCollisionExit(Collider* other)
	{
	}
}