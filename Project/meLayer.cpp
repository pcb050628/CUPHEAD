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
			gobj->Update();
		}
	}
	void Layer::Render(HDC hdc)
	{
		for (auto gobj : mGameObjs)
		{
			gobj->Render(hdc);
		}
	}
}