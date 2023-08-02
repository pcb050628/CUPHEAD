#pragma once

#include <vector>
#include <map>
#include <functional>
#include <string>
#include <queue>
#include <bitset>
#include <assert.h>

#include "framework.h"
#include "meMath.h"
#include "meTime.h"
#include "meKeyInput.h"

#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")


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
			floor,
			Enemy,
			Player,
			Bullet,
			UI,
			End
		};

		enum class eComponentType
		{
			Transform,
			SpriteRenderer,
			Collider,
			Animator,
			Rigidbody,
		};

		enum class eColliderType
		{
			Circle,
			Box,
		};

		enum class eGameObjType
		{
			none,
			obj,
			background,
			floor,
			wall,
			enemy,
			player,
			bullet,
		};

	}
}