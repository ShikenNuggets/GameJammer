#ifndef JAMMER_MEMORY_WEAK_PTR_H
#define JAMMER_MEMORY_WEAK_PTR_H

#include "Memory/ReferenceCount.h"
#include "Memory/SharedPtr.h"

namespace Jammer{
	template <class T>
	class WeakPtr{
	public:
		WeakPtr() = delete;

		WeakPtr(const SharedPtr<T>& other_) : object(other_.object), refCount(other_.refCount){
			J_BASIC_ASSERT(refCount != nullptr);
			refCount->IncrementWeakCount();
		}

		~WeakPtr(){
			if(refCount != nullptr){
				refCount->DecrementWeakCount();
			}
		}

		SharedPtr<T> Lock(){
			if(refCount == nullptr || !refCount->HasReferences()){
				return SharedPtr<T>(nullptr);
			}

			return SharedPtr<T>(object, refCount);
		}

	private:
		T* object;
		ReferenceCount* refCount;
	};
}

#endif //!JAMMER_MEMORY_WEAK_PTR_H