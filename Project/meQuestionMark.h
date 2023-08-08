#pragma once
#include "meSensor.h"

namespace me
{
	class QuestionMark : public Sensor
	{
	public:
		QuestionMark(const std::wstring& name);
		virtual ~QuestionMark() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void Disappear();

	private:
		Animator* mAnimator;

		float time;
	};
}

