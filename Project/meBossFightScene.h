#pragma once
#include "meScene.h"
#include "meBoss.h"
#include "mePlayer_stage.h"
#include "meWall.h"
#include "meFloor.h"
#include "meDeadUI.h"

namespace me
{
	class BossFightScene : public Scene
	{
	public:
		BossFightScene(std::wstring name);
		virtual ~BossFightScene() override;

		void Init() override;
		void Setting() override;
		void Update() override;
		void Render(HDC hdc) override;

		virtual void Clear() override;

		Player_stage* GetPlayer() { return mPlayer; }
		Boss* GetBoss() { return mBoss; }
		
		template <typename T>
		T* AddBoss(const std::wstring& name, math::Vector2 pos)
		{
			T* tmp = new T(name);
			Scene::AddBoss(tmp);
			tmp->Init();			
			tmp->GetComponent<Transform>()->SetPos(pos);
			mBoss = tmp;
			return tmp;
		}

	private:
		Boss*			mBoss;
		Player_stage*	mPlayer;

		Wall* wall1;
		Wall* wall2;
		Floor* floor;

		DeadUI* deadUI;

		float savedTime;
	};
}

