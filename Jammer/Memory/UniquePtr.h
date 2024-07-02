#ifndef JAMMER_MEMORY_UNIQUE_PTR_H
#define JAMMER_MEMORY_UNIQUE_PTR_H

#include "Debug.h"

namespace Jammer{
	template <class T>
	class UniquePtr{
	public:
		explicit UniquePtr(T* object_) : object(object_){}

		~UniquePtr(){
			Reset();
		}

		UniquePtr(const UniquePtr&) = delete;
		UniquePtr(const UniquePtr&&) = delete;
		UniquePtr& operator=(const UniquePtr&) = delete;
		UniquePtr& operator=(const UniquePtr&&) = delete;

		T* Get(){ return object; }
		const T* const Get() const{ return object; }

		//Deletes the owned memory and resets the pointer to null
		void Reset(){
			delete object;
			object = nullptr;
		}

		//Releases ownership of the pointer WITHOUT deleting it
		T* ReleaseOwnership(){
			T* oldObj = object;
			object = nullptr;
			return oldObj;
		}

		//Assign a new pointer to be owned by the UniquePtr
		void AssignPtr(T* object_){
			J_ASSERT(object == nullptr, "Possible memory leak - Assigning new pointer to a UniquePtr that already owns one");
			J_BASIC_ASSERT(object_ != nullptr);
			object = object_;
		}

	private:
		T* object;
	};
}

#endif //!JAMMER_MEMORY_UNIQUE_PTR_H