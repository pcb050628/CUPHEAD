#pragma once
#include "meGameObject.h"

namespace me
{	
	namespace enums
	{
		enum class SenseType
		{
			Enter,
			Stay,
			none,
		};
	}

	class Sensor : public GameObject
	{
	public:
		Sensor(const std::wstring& name);
		virtual ~Sensor() override;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void SetColliderSize(math::Vector2 value) {	mCollider->SetSize(value); }
		math::Vector2 GetColliderSize() { return mCollider->GetSize(); }

		void AddTargetType(enums::eGameObjType type) { 
			for (enums::eGameObjType target : TargetTypes)
			{
				if (target == type)
					return;
			}

			TargetTypes.push_back(type);
			isSensed.insert(std::make_pair(type, enums::SenseType::none));
			SensedObjs.insert(std::make_pair(type, nullptr));
		}

		bool FindTargetType(enums::eGameObjType type) {
			for (enums::eGameObjType target : TargetTypes)
			{
				if (target == type)
					return true;
			}

			return false;
		}

		enums::SenseType Sensed() {
			if (TargetTypes.size() > 0)
			{
				for (auto iter : isSensed)
				{
					return iter.second;
				}
			}
		}

		enums::SenseType Sensed(enums::eGameObjType type) { 
			if(isSensed.find(type) != isSensed.end())
				return isSensed.find(type)->second;

			return enums::SenseType::none;
		}

		GameObject* GetSensedObj() {
			if (SensedObjs.size() > 0)
			{
				for (auto iter : SensedObjs)
				{
					return iter.second;
				}
			}
			
			return nullptr;
		}

		GameObject* GetSensedObj(enums::eGameObjType type) {
			for (auto iter : SensedObjs)
			{
				if(iter.first == type)
					return iter.second;
			}

			return nullptr;
		}

		void RemoveSensedObj(enums::eGameObjType type)
		{
			for (auto iter : SensedObjs)
			{
				if (iter.first == type)
				{
					iter.second = nullptr;
				}
			}
		}

		void SetOwner(GameObject* owner) { mOwner = owner; }
		GameObject* GetOwner() { return mOwner; }

		void SetPos(math::Vector2 value) { GetComponent<Transform>()->SetPos(value); }
		void SetOffset(math::Vector2 value) { mOffset = value; }

		math::Vector2 GetPos() { return GetComponent<Transform>()->GetPos(); }
		math::Vector2 GetOffset() { return mOffset; }

		void SetActive(bool value) { mCollider->SetActivate(value); }

	private:
		GameObject* mOwner;
		BoxCollider* mCollider;
		math::Vector2 mOffset;

		std::vector<enums::eGameObjType> TargetTypes;
		std::map<enums::eGameObjType, GameObject*> SensedObjs;
		std::map<enums::eGameObjType, enums::SenseType> isSensed;
	};
}

