#include "meGoopy_Le_Grande_Boss.h"

namespace me
{
	Goopy_Le_Grande_Boss::Goopy_Le_Grande_Boss(const std::wstring& name) : Boss(name)
	{
	}
	Goopy_Le_Grande_Boss::~Goopy_Le_Grande_Boss()
	{
	}
	void Goopy_Le_Grande_Boss::Init()
	{
		Boss::Init();

		mAnimator = AddComponent<Animator>(enums::eComponentType::Animator);


	}
	void Goopy_Le_Grande_Boss::Update()
	{
		Boss::Update();
	}
	void Goopy_Le_Grande_Boss::Render(HDC hdc)
	{
		Boss::Render(hdc);
	}
}
