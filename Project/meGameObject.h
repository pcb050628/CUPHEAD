#pragma once
#include "DEFAULT.h"
#include "meEntity.h"
#include "COMPONENTS.h"

namespace me
{
	class GameObject : public Entity
	{
		friend class SceneManager;
	public:
		enum class ObjState
		{
			Active,
			Pause,
			Dead,
			End,
		};

		GameObject(const std::wstring& name, enums::eGameObjType type = enums::eGameObjType::obj);
		virtual ~GameObject() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		virtual enums::eGameObjType GetTag() { return type; }
		
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
			case me::enums::eComponentType::Rigidbody:
				name = L"defaultRigidbody";
				break;
			}

			T* tmp = new T(this, name);
			tmp->Init();
			mComponents.push_back(tmp);

			return tmp;
		}

		template <typename T>
		T* AddComponent(const std::wstring& name)
		{
			T* tmp = new T(this, name);
			tmp->Init();
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

		virtual int GetColliderCount() { return mColliderCount; }
		virtual void ColliderCountIncrease() { mColliderCount += 1; }
		virtual void ColliderCountDecrease() { mColliderCount -= 1; }
		
		virtual std::vector<Collider*> GetCollider() 
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

		virtual std::vector<Component*> GetAllComponent() { return mComponents; }

		virtual void SetActive(bool value) { Activate = value; }
		virtual bool GetActive() { return Activate; }

		virtual ObjState GetObjState() { return mState; }

		void SetParryable(bool value) { IsParryable = value; }
		bool GetIsParryable() { return IsParryable; }

	private:
		void SetState(ObjState state) { mState = state; }

	private:
		ObjState mState;
		bool Activate;

		enums::eGameObjType type;
		bool IsParryable = false;

		std::vector<Component*> mComponents = {};
		int mColliderCount;
	};
}

