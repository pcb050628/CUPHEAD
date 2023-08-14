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

		template <typename T>
		T* AddGameObj(const std::wstring& name)
		{
			GameObject* tmp = new T(name);
			mGameObjs.push_back(tmp);
			return dynamic_cast<T*>(tmp);
		}

		GameObject* AddGameObj(std::wstring name, enums::eGameObjType type)
		{
			GameObject* tmp = new GameObject(name, type);
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

		void RemovePlayer_stage()
		{
			for (std::vector<GameObject*>::iterator iter = mGameObjs.begin();
				iter != mGameObjs.end();
				)
			{
				if (dynamic_cast<Player_stage*>(*iter) != nullptr)
				{
					delete* iter;
					iter = mGameObjs.erase(iter);

					return;
				}
				else
					iter++;
			}
		}

		void AddBoss(Boss* boss)
		{
			mGameObjs.push_back(boss);
		}

		void RemoveBoss()
		{
			for (std::vector<GameObject*>::iterator iter = mGameObjs.begin();
				iter != mGameObjs.end();
				)
			{
				if (dynamic_cast<Boss*>(*iter) != nullptr)
				{
					delete* iter;
					iter = mGameObjs.erase(iter);
				}
				else
					iter++;
			}
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

		bool Destroy(GameObject* gobj)
		{
			for (GameObject* obj : mGameObjs)
			{
				if (obj == gobj)
				{
					delete obj;
					return true;;
				}
			}

			return false;
		}

	private:
		std::vector<GameObject*> mGameObjs = {};
	};
}

