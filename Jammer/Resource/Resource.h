#ifndef JAMMER_RESOURCE_RESOURCE_H
#define JAMMER_RESOURCE_RESOURCE_H

#include "Data/String.h"
#include "Memory/SharedPtr.h"
#include "Memory/WeakPtr.h"

namespace Jammer{
	class Resource{
	public:
		Resource(){}
		virtual ~Resource(){}
	};

	class ResourceContainer{
	public:
		ResourceContainer(const String& name_, const String& path_) : name(name_), path(path_), resource(){}
		virtual ~ResourceContainer() = default;

		SharedPtr<Resource> GetResource(){
			SharedPtr<Resource> resPtr = resource.Lock();
			if(resPtr == nullptr){
				resPtr = SharedPtr<Resource>(LoadResource());
			}

			return resPtr;
		}

		String Name() const{ return name; }
		String Path() const{ return path; }
		bool HasReferences() const{ return resource.IsValid(); }

	protected:
		virtual Resource* LoadResource() const = 0;

	private:
		String name;
		String path;
		WeakPtr<Resource> resource;
	};
}

#endif //!JAMMER_RESOURCE_RESOURCE_H