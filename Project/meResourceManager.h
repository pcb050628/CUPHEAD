#pragma once
#include "DEFAULT.h"
#include "meResource.h"

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

	private:
		static std::map<std::wstring, Resource*> mResources;
	};
}

