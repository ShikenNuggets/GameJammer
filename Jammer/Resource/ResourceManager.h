#ifndef JAMMER_RESOURCE_RESOURCE_MANAGER_H
#define JAMMER_RESOURCE_RESOURCE_MANAGER_H

#include "Resource/Resource.h"

namespace Jammer{
	class ResourceManager{
	public:
		ResourceManager();
		~ResourceManager();

		void AddResource(Resource* resource_);
	};
}

#endif //!JAMMER_RESOURCE_RESOURCE_MANAGER_H