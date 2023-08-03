#pragma once
#include "meGameObject.h"
#include "mePlayer_stage.h"

namespace me
{
	class HealthBar : public GameObject
	{
	public:
		HealthBar(const std::wstring& name);
		virtual ~HealthBar() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetPlayer(Player_stage* player) { mPlayer = player; }

	private:
		Player_stage* mPlayer;

		SpriteRenderer* Health1;
		SpriteRenderer* Health2;
		SpriteRenderer* Health3;
		SpriteRenderer* Dead;
	};
}

