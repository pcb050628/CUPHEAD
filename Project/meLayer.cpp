#include "meLayer.h"

namespace me
{
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{
		for (auto gobj : mGameObjs)
		{
			delete gobj;
		}
		mGameObjs.clear();
	}

	void Layer::Update()
	{
		for (auto gobj : mGameObjs)
		{
			if (gobj->GetActive())
				gobj->Update();
		}
	}
	void Layer::Render(HDC hdc)

	{
		for (auto gobj : mGameObjs)
		{
			if(gobj->GetActive())
				gobj->Render(hdc);
		}

		for (std::vector<GameObject*>::iterator iter = mGameObjs.begin();
			iter != mGameObjs.end();
			)
		{
			if ((*iter)->GetObjState() == GameObject::ObjState::Dead)
			{
				delete *iter;
				iter = mGameObjs.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}
}