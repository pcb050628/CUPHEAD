#pragma once
#include "DEFAULT.h"
#include "meGameObject.h"
#include "mePlayer_map.h"
#include "mePlayer_stage.h"

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
			mGameObjs.insert(std::make_pair(name, tmp)); 
			return tmp;
		}

		Player_map* AddPlayer_map(std::wstring name)
		{
			Player_map* tmp = new Player_map(name);
			mGameObjs.insert(std::make_pair(name, tmp));
			return tmp;
		}

		Player_stage* AddPlayer_stage(std::wstring name)
		{
			Player_stage* tmp = new Player_stage(name);
			mGameObjs.insert(std::make_pair(name, tmp));
			return tmp;
		}

		GameObject* GetGameObj(std::wstring name)
		{
			std::map<std::wstring, GameObject*>::iterator iter = mGameObjs.find(name);

			if (iter == mGameObjs.end())
				return nullptr;

			return iter->second;
		}

	private:
		std::map<std::wstring, GameObject*> mGameObjs = {};
	};
}

