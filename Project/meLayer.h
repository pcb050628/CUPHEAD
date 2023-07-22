#pragma once
#include "DEFAULT.h"
#include "meGameObject.h"
#include "mePlayer_map.h"
#include "mePlayer_stage.h"
#include "meBoss.h"

namespace me
{	
	class Layer
	{
	public:
		Layer();
		~Layer();

		void Update();
		void Render(HDC hdc);

		GameObject* AddGameObj(std::wstring name)
		{
			GameObject* tmp = new GameObject(name);
			mGameObjs.push_back(tmp);
			return tmp;
		}

		Player_map* AddPlayer_map(std::wstring name)
		{
			Player_map* tmp = new Player_map(name);
			mGameObjs.push_back(tmp);
			return tmp;
		}

		Player_stage* AddPlayer_stage(std::wstring name)
		{
			Player_stage* tmp = new Player_stage(name);
			mGameObjs.push_back(tmp);
			return tmp;
		}

		void AddBoss(Boss* boss)
		{
			mGameObjs.push_back(boss);
		}

		GameObject* GetGameObj(std::wstring name)
		{
			GameObject* tmp = nullptr;

			for (int i = 0; i < mGameObjs.size(); i++)
			{
				tmp = mGameObjs[i];
				if (tmp->GetName() == name)
					return tmp;
			}

			return nullptr;
		}

		std::vector<GameObject*>& GetGameObjects() { return mGameObjs; }

	private:
		std::vector<GameObject*> mGameObjs = {};
	};
}

