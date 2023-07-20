#pragma once
#include "DEFAULT.h"
#include "meBoxCollider.h"

namespace me
{	
	union ColliderId
	{
		struct
		{
			UINT left;
			UINT right;
		};
		UINT64 id;
	};

	class ColliderManager
	{
	public:
		static void Init();
		static void Update();
		static void Release();

		static void Clear();

		static void CollisionLayerCheck(enums::eLayer left, enums::eLayer right, bool enable);
		static void LayerCollision(class Scene* scene, enums::eLayer left, enums::eLayer right);
		static void ColliderCollision(BoxCollider* left, BoxCollider* right);
		static bool Intersect(BoxCollider* left, BoxCollider* right);

	private:
		static std::map<UINT64, bool> mCollisionMap;
		static std::bitset<(UINT)enums::eLayer::End> mLayerMatrix[(UINT)enums::eLayer::End];
	};
}

