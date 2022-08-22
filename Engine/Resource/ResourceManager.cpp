#include "ResourceManager.h"

namespace jemgine
{
	void ResourceManager::Initialize()
	{
	}

	void ResourceManager::Shutdown()
	{
		m_resources.clear();
	}
}
