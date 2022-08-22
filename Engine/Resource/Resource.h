#pragma once
#include <string>

namespace jemgine
{
	class Resource
	{
	public:
		virtual bool Create(std::string name, ...) = 0;
	};
}