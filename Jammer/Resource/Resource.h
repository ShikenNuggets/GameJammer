#ifndef JAMMER_RESOURCE_RESOURCE_H
#define JAMMER_RESOURCE_RESOURCE_H

#include "Data/String.h"
#include "Memory/SharedPtr.h"

namespace Jammer{
	class Resource{
	public:
		Resource(){}
		virtual ~Resource(){}
	};

	class ResourceContainer{
	public:
		ResourceContainer(const String& name_, const String& path_) : name(name_), path(path_), resource(nullptr){}
		virtual ~ResourceContainer() = default;

		SharedPtr<Resource> GetResource(){
			if(resource.HasReferences()){
				return resource;
			}

			resource = SharedPtr<Resource>(LoadResource());
		}

		String Name() const{ return name; }
		String Path() const{ return path; }
		bool HasReferences() const{ return resource.HasReferences(); }

	protected:
		virtual Resource* LoadResource() const = 0;

	private:
		String name;
		String path;
		SharedPtr<Resource> resource;
	};
}

#endif //!JAMMER_RESOURCE_RESOURCE_H