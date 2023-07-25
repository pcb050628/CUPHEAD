#pragma once

#include <vector>
#include <map>
#include <functional>
#include <string>
#include <queue>
#include <bitset>

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
			Player,
			Bullet,
			Enemy,
			UI,
			End
		};

		enum class eComponentType
		{
			Transform,
			SpriteRenderer,
			BoxCollider,
			Animator,
			Rigidbody,
		};

		enum class eGameObjType
		{
			none,
			obj,
			background,
			floor,
			npc,
			enemy,
			player,
			bullet,
		};

	}
}