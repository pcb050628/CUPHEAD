#include "meColliderManager.h"
#include "meSceneManager.h"
#include "meCircleCollider.h"
#include "meScene.h"

namespace me
{
	std::map<UINT64, bool>  ColliderManager::mCollisionMap = {};
	std::bitset<(UINT)enums::eLayer::End>  ColliderManager::mLayerMatrix[(UINT)enums::eLayer::End] = {};

	void ColliderManager::Init()
	{
		CollisionLayerCheck(enums::eLayer::Player, enums::eLayer::Enemy, true);
	}
	void ColliderManager::Update()
	{
		Scene* curScene = SceneManager::GetCurScene();

		for (int row = 0; row < (int)enums::eLayer::End; row++)
		{
			for (int column = 0; column < (int)enums::eLayer::End; column++)
			{
				if (mLayerMatrix[row][column] == true)
				{
					LayerCollision(curScene, (enums::eLayer)row, (enums::eLayer)column);
				}
			}
		}
	}
	void ColliderManager::Release()
	{
	}
	void ColliderManager::Clear()
	{
		mLayerMatrix->reset();
		mCollisionMap.clear();
	}
	void ColliderManager::CollisionLayerCheck(enums::eLayer left, enums::eLayer right, bool enable)
	{
		int row = -1;
		int col = -1;

		if (left > right)
		{
			row = (UINT)left;
			col = (UINT)right;
		}
		else
		{
			row = (UINT)right;
			col = (UINT)left;
		}

		mLayerMatrix[row][col] = enable;
	}

	void ColliderManager::LayerCollision(Scene* scene, enums::eLayer left, enums::eLayer right)
	{
		Layer& leftLayer = scene->GetLayer(left);
		std::vector<GameObject*> leftGobjs = leftLayer.GetGameObjects();

		Layer& rightLayer = scene->GetLayer(right);
		std::vector<GameObject*> rightGobjs = rightLayer.GetGameObjects();

		for (GameObject* leftObj : leftGobjs)
		{
			if (leftObj->GetColliderCount() == 0)
				continue;

			std::vector<Collider*> leftCols = leftObj->GetCollider();

			for (Collider* leftCol : leftCols)
			{
				for (GameObject* rightObj : rightGobjs)
				{
					if (rightObj->GetColliderCount() == 0)
						continue;
					if (leftObj == rightObj) 
						continue;

					std::vector<Collider*> rightCols = rightObj->GetCollider();

					for (Collider* rightCol : rightCols)
					{
						ColliderCollision(leftCol, rightCol);
					}
				}
			}
		}
	}

	void ColliderManager::ColliderCollision(Collider* left, Collider* right)
	{
		ColliderId id = {};
 		id.left = (UINT)left;
		id.right = (UINT)right;

		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(id.id);

		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id, false));
			iter = mCollisionMap.find(id.id);
		}

		if (Intersect(left, right))
		{
			if (iter->second == true)
			{
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
				iter->second = true;
			}
			else
			{
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
				iter->second = true;
			}
		}
		else
		{
			if (iter->second == true)
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
				iter->second = false;
			}
		}
	}

	bool ColliderManager::Intersect(Collider* left, Collider* right)
	{
		if (left->GetType() == enums::eColliderType::Box && right->GetType() == enums::eColliderType::Box)
		{
			math::Vector2 leftPos = dynamic_cast<BoxCollider*>(left)->GetPos();
			math::Vector2 leftSize = dynamic_cast<BoxCollider*>(left)->GetSize();

			math::Vector2 rightPos = dynamic_cast<BoxCollider*>(right)->GetPos();
			math::Vector2 rightSize = dynamic_cast<BoxCollider*>(right)->GetSize();

			if ((fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2.f + rightSize.x / 2.f))
				&& (fabs(leftPos.y - rightPos.y) < fabs(leftSize.y / 2.f + rightSize.y / 2.f)))
			{
				return true;
			}
		}
		else if (left->GetType() == enums::eColliderType::Circle && right->GetType() == enums::eColliderType::Circle)
		{
			math::Vector2 leftPos = dynamic_cast<CircleCollider*>(left)->GetPos();
			float leftVerRadius = dynamic_cast<CircleCollider*>(left)->GetVerticalRadius();
			float leftHorRadius = dynamic_cast<CircleCollider*>(left)->GetHorizontalRadius();

			math::Vector2 rightPos = dynamic_cast<CircleCollider*>(right)->GetPos();
			float rightVerRadius = dynamic_cast<CircleCollider*>(right)->GetVerticalRadius();
			float rightHorRadius = dynamic_cast<CircleCollider*>(right)->GetHorizontalRadius();

			if ((fabs(leftPos.x - rightPos.x) < fabs(leftVerRadius + rightVerRadius))
				&& (fabs(leftPos.y - rightPos.y) < fabs(leftHorRadius + rightHorRadius)))
			{
				return true;
			}
		}
		else if(left->GetType() == enums::eColliderType::Box)
		{
			math::Vector2 leftPos = dynamic_cast<BoxCollider*>(left)->GetPos();
			math::Vector2 leftSize = dynamic_cast<BoxCollider*>(left)->GetSize();

			math::Vector2 rightPos = dynamic_cast<CircleCollider*>(right)->GetPos();
			float rightVerRadius = dynamic_cast<CircleCollider*>(right)->GetVerticalRadius();
			float rightHorRadius = dynamic_cast<CircleCollider*>(right)->GetHorizontalRadius();

			if ((fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2.f + rightVerRadius))
				&& (fabs(leftPos.y - rightPos.y) < fabs(leftSize.y / 2.f + rightHorRadius)))
			{
				return true;
			}
		}
		else if (left->GetType() == enums::eColliderType::Circle)
		{
			math::Vector2 leftPos = dynamic_cast<CircleCollider*>(left)->GetPos();
			float leftVerRadius = dynamic_cast<CircleCollider*>(left)->GetVerticalRadius();
			float leftHorRadius = dynamic_cast<CircleCollider*>(left)->GetHorizontalRadius();

			math::Vector2 rightPos = dynamic_cast<BoxCollider*>(right)->GetPos();
			math::Vector2 rightSize = dynamic_cast<BoxCollider*>(right)->GetSize();

			if ((fabs(leftPos.x - rightPos.x) < fabs(leftVerRadius + rightSize.x / 2.f))
				&& (fabs(leftPos.y - rightPos.y) < fabs(leftHorRadius + rightSize.y / 2.f)))
			{
				return true;
			}
		}

		return false;
	}
}