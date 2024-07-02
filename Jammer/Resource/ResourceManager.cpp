#include "Resource/ResourceManager.h"

using namespace Jammer;

ResourceManager::ResourceManager() : resources(32){}

ResourceManager::~ResourceManager(){
	for(size_t i = 0; i < resources.Size(); i++){
		J_BASIC_ASSERT(!resources[i]->HasReferences());
		delete resources[i];
		resources[i] = nullptr;
	}
}

void ResourceManager::AddResource(ResourceContainer* resource_){
	resources.Add(resource_);
}