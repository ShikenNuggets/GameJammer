#ifndef JAMMER_RESOURCE_RESOURCE_H
#define JAMMER_RESOURCE_RESOURCE_H

#include "Data/String.h"

namespace Jammer{
	class Resource{
	public:
		Resource(const String& name_, const String& path_) : name(name_), path(path_){}
		virtual ~Resource(){}

		String GetName() const{ return name; }
		String GetPath() const{ return path; }

	private:
		String name;
		String path;
	};
}

#endif //!JAMMER_RESOURCE_RESOURCE_H