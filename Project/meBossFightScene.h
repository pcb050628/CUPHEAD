#pragma once
#include "meScene.h"
#include "meBoss.h"
#include "mePlayer_stage.h"

namespace me
{
	class BossFightScene : public Scene
	{
	public:
		BossFightScene(std::wstring name);
		virtual ~BossFightScene() override;

		void Init() override;
		void Update() override;
		void Render(HDC hdc) override;

		Player_stage* GetPlayer() { return mPlayer; }
		Boss* GetBoss() { return mBoss; }
		
		template <typename T>
		T* AddBoss(const std::wstring& name)
		{
			T* tmp = new T(name);
			Scene::AddBoss(tmp);
			tmp->Init();
			return tmp;
		} 

	private:
		Boss*			mBoss;
		Player_stage*	mPlayer;
	};
}

