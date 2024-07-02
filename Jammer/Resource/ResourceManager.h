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

		template <class T>
		T* GetResource(const String& name_){
			for(size_t i = 0; i < resources.Size(); i++){
				if(resources[i]->Name() == name_){
					J_BASIC_ASSERT(dynamic_cast<T*>(resources[i]->GetResource()) != nullptr);
					return dynamic_cast<T*>(resources[i]->GetResource());
				}
			}

			J_ASSERT(false, "Tried to load unknown resource [" + name_ + "]!");
		}

	private:
		Array<ResourceContainer*> resources;
	};
}

#endif //!JAMMER_RESOURCE_RESOURCE_MANAGER_H