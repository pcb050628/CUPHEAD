#pragma once
#include "DEFAULT.h"
#include "meEntity.h"

namespace me
{
	class Resource : public Entity
	{
	public:
		Resource(const std::wstring& _name);
		virtual ~Resource() override;

		virtual bool Load(const std::wstring& path) = 0;	

		const virtual std::wstring& GetPath() { return path; }
		virtual void SetPath(const std::wstring& _path) { path = _path; }

	private:
		std::wstring path = {};
	};
}
