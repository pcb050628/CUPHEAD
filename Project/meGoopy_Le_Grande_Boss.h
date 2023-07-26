#pragma once
#include "meBoss.h"

namespace me
{	
	class Goopy_Le_Grande_Boss : public Boss
	{
	public:
		Goopy_Le_Grande_Boss(const std::wstring& name);
		virtual ~Goopy_Le_Grande_Boss() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void Phase1() override;
		virtual void Phase2() override;
		virtual void Phase3() override;
		virtual void Death() override;

		void Jump();
		void Punch();
		void Smash();

	private:
		Animator* mAnimator;

	};
}

