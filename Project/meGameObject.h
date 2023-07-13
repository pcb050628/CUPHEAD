#pragma once
#include "DEFAULT.h"
#include "meEntity.h"
#include "COMPONENTS.h"

namespace me
{
	class GameObject : public Entity
	{
	public:
		GameObject(const std::wstring& name);
		virtual ~GameObject() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual enums::eGameObjType GetTag() { return tag; }

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
			case me::enums::eComponentType::Controller:
				name = L"defaultController";
				break;
			case me::enums::eComponentType::Animator:
				name = L"defaultAnimator";
				break;
			}

			T* tmp = new T(this, name);
			mComponents.insert(std::make_pair(tmp->GetName(), tmp));

			return tmp;
		}

		template <typename T>
		T* AddComponent(const std::wstring& name)
		{
			T* tmp = new T(this, name);
			mComponents.insert(std::make_pair(tmp->GetName(), tmp));

			return tmp;
		}

		template <typename T>
		T* GetComponent()
		{
			T* tmp = nullptr;
			auto iter = mComponents.begin();
			
			if (mComponents.size() > 0)
			{
				for (int count = 0; count < mComponents.size(); count++, iter++)
				{
					tmp = dynamic_cast<T*>(iter->second);
					if (tmp != nullptr)
						return tmp;
				}
			}

			return nullptr;
		}

		template <typename T>
		T* GetComponent(const std::wstring& name)
		{
			T* tmp = nullptr;

			auto iter = mComponents.find(name);

			if (iter != mComponents.end())
			{
				tmp = dynamic_cast<T*>(iter->second);
				return tmp;
			}
			else
				return nullptr;
		}

	private:
		enums::eGameObjType tag;

		std::map<std::wstring, Component*> mComponents = {};
	};
}

