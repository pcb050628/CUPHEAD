#pragma once
#include "DEFAULT.h"
#include "meEntity.h"
#include "COMPONENTS.h"

namespace me
{
	class GameObject : public Entity
	{
	public:
		GameObject(const std::wstring& name, enums::eGameObjType type = enums::eGameObjType::obj);
		virtual ~GameObject() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual enums::eGameObjType GetTag() { return type; }

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);
		
		template <typename T>
		T* AddComponent(enums::eComponentType type)
		{
			std::wstring name = {};

			switch (type)
			{
			case me::enums::eComponentType::Transform:
				name = L"defaultTransform";
				break;
			case me::enums::eComponentType::SpriteRenderer:
				name = L"defaultSpriteRenderer";
				break;
			case me::enums::eComponentType::Collider:
				name = L"defaultCollider";
				break;
			case me::enums::eComponentType::Animator:
				name = L"defaultAnimator";
				break;
			}

			T* tmp = new T(this, name);
			mComponents.push_back(tmp);

			return tmp;
		}

		template <typename T>
		T* AddComponent(const std::wstring& name)
		{
			T* tmp = new T(this, name);
			mComponents.push_back(tmp);

			return tmp;
		}

		template <typename T>
		T* GetComponent()
		{
			T* tmp = nullptr;
			
			if (mComponents.size() > 0)
			{
				for (int i = 0; i < mComponents.size(); i++)
				{
					tmp = dynamic_cast<T*>(mComponents[i]);
					if (tmp != nullptr)
						return tmp;
				}
			}

			return nullptr;
		}

		template <typename T>
		T* GetComponent(const std::wstring& name)
		{
			if (mComponents.size() > 0)
			{
				for (int i = 0; i < mComponents.size(); i++)
				{
					if (mComponents[i]->GetName() == name)
						return dynamic_cast<T*>(mComponents[i]);
				}
			}
			else
				return nullptr;
		}

		int GetColliderCount() { return mColliderCount; }
		void ColliderCountIncrease() { mColliderCount += 1; }

		
		std::vector<Collider*> GetCollider() 
		{
			if (mComponents.size() > 0 && mColliderCount > 0)
			{
				std::vector<Collider*> tmp = {};
				for (int i = 0; i < mComponents.size(); i++)
				{
					if (dynamic_cast<Collider*>(mComponents[i]) != nullptr)
					{
						tmp.push_back(dynamic_cast<Collider*>(mComponents[i]));
					}
				}

				return tmp;
			}
		}

	private:
		enums::eGameObjType type;

		std::vector<Component*> mComponents = {};
		int mColliderCount;
	};
}

