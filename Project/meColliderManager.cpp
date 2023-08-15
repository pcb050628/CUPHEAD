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

		if ((UINT)left < (UINT)right)
		{
 			id.left = (UINT)left;
			id.right = (UINT)right;
		}
		else
		{
			id.left = (UINT)right;
			id.right = (UINT)left;
		}

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
			}

			iter->second = false;
		}
	}

	bool ColliderManager::Intersect(Collider* left, Collider* right)
	{
		if (!right->GetActivate() || !right->GetOwner()->GetActive() || !left->GetActivate() || !left->GetOwner()->GetActive())
			return false;

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
			float leftRadius = dynamic_cast<CircleCollider*>(left)->GetRadius();

			math::Vector2 rightPos = dynamic_cast<CircleCollider*>(right)->GetPos();
			float righRadius = dynamic_cast<CircleCollider*>(right)->GetRadius();

			float dist = sqrt(pow((leftPos.x - rightPos.x), 2) + pow((leftPos.y - rightPos.y), 2));

			if (dist < fabs(leftRadius + righRadius))
			{
				return true;
			}
		}
		else if(left->GetType() == enums::eColliderType::Box)
		{
			math::Vector2 leftPos = dynamic_cast<BoxCollider*>(left)->GetPos();
			math::Vector2 leftSize = dynamic_cast<BoxCollider*>(left)->GetSize();

			math::Vector2 rightPos = dynamic_cast<CircleCollider*>(right)->GetPos();
			float righRadius = dynamic_cast<CircleCollider*>(right)->GetRadius();

			float closest_x = std::max<float>(leftPos.x - leftSize.x / 2.0f, std::min<float>(rightPos.x, leftPos.x + leftSize.x / 2.0f));
			float closest_y = std::max<float>(leftPos.y - leftSize.y / 2.0f, std::min<float>(rightPos.y, leftPos.y + leftSize.y / 2.0f));

			float dist = sqrt(pow(fabs(closest_x - rightPos.x), 2) + pow(fabs(closest_y - rightPos.y), 2));

			if (dist < righRadius)
			{
				return true;
			}
		}
		else if (left->GetType() == enums::eColliderType::Circle)
		{
			math::Vector2 leftPos = dynamic_cast<CircleCollider*>(left)->GetPos();
			float leftRadius = dynamic_cast<CircleCollider*>(left)->GetRadius();

			math::Vector2 rightPos = dynamic_cast<BoxCollider*>(right)->GetPos();
			math::Vector2 rightSize = dynamic_cast<BoxCollider*>(right)->GetSize();

			float closest_x = std::max<float>(rightPos.x - rightSize.x / 2.0f, std::min<float>(leftPos.x, rightPos.x + rightSize.x / 2.0f));
			float closest_y = std::max<float>(rightPos.y - rightSize.y / 2.0f, std::min<float>(leftPos.y, rightPos.y + rightSize.y / 2.0f));

			float dist = sqrt(pow(fabs(closest_x - leftPos.x), 2) + pow(fabs(closest_y - leftPos.y), 2));

			if (dist < leftRadius)
			{
				return true;
			}
		}

		return false;
	}
}