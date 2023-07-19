#pragma once
#include "DEFAULT.h"

namespace me
{	
	class ColliderManager
	{
	public:
		static void Init();
		static void Update();

	private:
		static std::map<UINT32, bool> mCollisionMap;
		static std::bitset<(UINT)enums::eLayer::End> mLayerMatrix[(UINT)enums::eLayer::End];
	};
}

