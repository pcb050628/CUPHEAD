#pragma once

#include <vector>
#include <map>
#include <functional>
#include <string>

#include "framework.h"
#include "meMath.h"
#include "meTime.h"
#include "meKeyInput.h"


namespace me
{
	static float CLIENT_WIDTH;
	static float CLIENT_HEIGHT;

	namespace enums
	{
		enum class eLayer
		{
			Background,
			Map,
			Enemy,
			Player,
			UI,
			ScreenFx,
			End
		};

		enum class eComponentType
		{
			Transform,
			SpriteRenderer,
			Collider,
			Controller,
			Animator
		};

		enum class eGameObjType
		{
			npc,
			enemy,
			player,
			door
		};
	}
}