#include "meLayer.h"

namespace me
{
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{
		if (mGameObjs.size() > 0)
		{
			std::map<std::wstring, GameObject*>::iterator iter = mGameObjs.begin();

			while (iter != mGameObjs.end())
			{
				delete iter++->second;
			}
		}
		mGameObjs.clear();
	}

	void Layer::Update()
	{
		std::map<std::wstring, GameObject*>::iterator iter = mGameObjs.begin();

		while (iter != mGameObjs.end())
		{
			iter++->second->Update();
		}
	}
	void Layer::Render(HDC hdc)
	{
		std::map<std::wstring, GameObject*>::iterator iter = mGameObjs.begin();

		while (iter != mGameObjs.end())
		{
			iter++->second->Render(hdc);
		}
	}
}