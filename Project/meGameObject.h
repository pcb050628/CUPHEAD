#pragma once
#include "DEFAULT.h"
#include "meEntity.h"
#include "meComponent.h"

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
		T* AddComponent()
		{
			T* tmp = new T(this);
			mComponents.push_back(tmp);

			return tmp;
		}

		template <typename T>
		T* GetComponent()
		{
			T* tmp = nullptr;

			for (Component* c : mComponents)
			{
				tmp = dynamic_cast<T*>(c);

				if (tmp != nullptr)
					return tmp;
			}

			return tmp;
		}

	private:
		enums::eGameObjType tag;

		std::vector<Component*> mComponents = {};
	};
}

