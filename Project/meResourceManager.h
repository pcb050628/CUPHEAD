#pragma once
#include "DEFAULT.h"
#include "meResource.h"
#include "meTexture.h"
#include "meAnimation.h"

namespace me
{
	class ResourceManager
	{
	public:
		template <typename T>
		static T* Find(const std::wstring& name)
		{
			auto iter = mResources.find(name);
			if (iter == mResources.end())
				return nullptr;
			else
				return dynamic_cast<T*>(iter->second);
		}

		template <typename T>
		static T* Load(const std::wstring& name, const std::wstring& path)
		{
			T* resource = ResourceManager::Find<T>(name);
			if (resource != nullptr)
				return dynamic_cast<T*>(resource);

			resource = new T(name);
			if (resource->Load(path))
			{
				resource->SetPath(path);
				mResources.insert(std::make_pair(resource->GetName(), resource));
				return dynamic_cast<T*>(resource);
			}
			else
				return nullptr;
		}

		static Animation* Load(const std::wstring& name, const std::wstring& path, eTextureType type)
		{
			Animation* resource = ResourceManager::Find<Animation>(name);
			if (resource != nullptr)
				return dynamic_cast<Animation*>(resource);

			resource = new Animation(name);
			if (resource->Load(path, type))
			{
				resource->SetPath(path);
				mResources.insert(std::make_pair(resource->GetName(), resource));
				return dynamic_cast<Animation*>(resource);
			}
			else
				return nullptr;
		}

		static Animation* Load(const std::wstring& SheetName, const std::wstring& AnimName, const std::wstring& path, math::Vector2 startpoint, int sliceUnit, int imageCount, float duration = 0.1f)
		{
			Animation* resource = ResourceManager::Find<Animation>(AnimName);
			if (resource != nullptr)
				return resource;

			resource = new Animation(AnimName);
			if (resource->Load(SheetName, path, startpoint, sliceUnit, imageCount))
			{
				resource->SetPath(path);
				resource->SetDuration(duration);
				mResources.insert(std::make_pair(resource->GetName(), resource));
				return resource;
			}
			else
				return nullptr;
		}

		static void Release()
		{
			for (auto iter : mResources)
			{
				delete iter.second;
			}
		}

	private:
		static std::map<std::wstring, Resource*> mResources;
	};
}

