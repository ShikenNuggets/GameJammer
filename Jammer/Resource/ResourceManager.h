#ifndef JAMMER_RESOURCE_RESOURCE_MANAGER_H
#define JAMMER_RESOURCE_RESOURCE_MANAGER_H

#include "Data/Array.h"
#include "Resource/Resource.h"

namespace Jammer{
	class ResourceManager{
	public:
		ResourceManager();
		~ResourceManager();

		void AddResource(ResourceContainer* resource_);

		SharedPtr<Resource> GetResource(const String& name_);

	private:
		Array<ResourceContainer*> resources;
	};
}

#endif //!JAMMER_RESOURCE_RESOURCE_MANAGER_H