#ifndef JAMMER_MEMORY_SHARED_PTR_H
#define JAMMER_MEMORY_SHARED_PTR_H

#include "ReferenceCount.h"

namespace Jammer{
	template <class T>
	class SharedPtr{
	public:
		SharedPtr(std::nullptr_t) : object(nullptr), refCount(nullptr){}

		SharedPtr(T* object_) : object(object_), refCount(new ReferenceCount()){
			J_BASIC_ASSERT(refCount != nullptr);
			(*refCount)++;
		}

		SharedPtr(const SharedPtr<T>& other_) : object(other_.object), refCount(other_.refCount){
			J_BASIC_ASSERT(refCount != nullptr);
			(*refCount)++;
		}

		virtual ~SharedPtr(){
			J_ASSERT((refCount == nullptr && object == nullptr) || (refCount != nullptr && refCount != nullptr), "If refCount or object is null, the other MUST be null");
			if(refCount == nullptr){
				return;
			}

			DecrementReferenceCountAndCleanup();
		}

		SharedPtr& operator=(const SharedPtr<T>& other_){
			if(this == &other_){
				return *this;
			}

			DecrementReferenceCountAndCleanup();

			object = other_.object;
			refCount = other_.refCount;

			if(refCount != nullptr){
				(*refCount)++;
			}

			return *this;
		}

		T& operator*(){ return *object; }
		T* operator->(){ return object; }

		bool HasReferences() const{
			J_BASIC_ASSERT(refCount == nullptr || refCount->HasReferences());
			return refCount != nullptr;
		}

	private:
		T* object;
		ReferenceCount* refCount;

		void DecrementReferenceCountAndCleanup(){
			if(refCount == nullptr){
				return;
			}

			(*refCount)--;
			if(!refCount->HasReferences()){
				delete refCount;
				refCount = nullptr;

				delete object;
				object = nullptr;
			}
		}
	};
}

#endif //!JAMMER_MEMORY_SHARED_PTR_H