#include "Resource/ResourceManager.h"

using namespace Jammer;

ResourceManager::ResourceManager() : resources(32){}

ResourceManager::~ResourceManager(){
	for(size_t i = 0; i < resources.Size(); i++){
		delete resources[i];
		resources[i] = nullptr;
	}
}

void ResourceManager::AddResource(ResourceContainer* resource_){
	resources.Add(resource_);
}

SharedPtr<Resource> ResourceManager::GetResource(const String& name_){
	for(size_t i = 0; i < resources.Size(); i++){
		if(resources[i]->Name() == name_){
			return resources[i]->GetResource();
		}
	}

	J_ASSERT(false, "Tried to load unknown resource [" + name_ + "]!");
	return nullptr;
}