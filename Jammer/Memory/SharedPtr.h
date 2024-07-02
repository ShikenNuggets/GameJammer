#ifndef JAMMER_MEMORY_SHARED_PTR_H
#define JAMMER_MEMORY_SHARED_PTR_H

#include "ReferenceCount.h"

namespace Jammer{
	template <class T>
	class WeakPtr;

	template <class T>
	class SharedPtr{
	public:
		SharedPtr(std::nullptr_t) : object(nullptr), refCount(nullptr){}

		explicit SharedPtr(T* object_) : object(object_), refCount(new ReferenceCount()){
			J_BASIC_ASSERT(refCount != nullptr);
			refCount->Increment();
		}

		explicit SharedPtr(T* object_, ReferenceCount* refCount_) : object(object_), refCount(refCount_){
			J_BASIC_ASSERT(refCount != nullptr);
			refCount->Increment();
		}

		SharedPtr(const SharedPtr<T>& other_) : object(other_.object), refCount(other_.refCount){
			J_BASIC_ASSERT(refCount != nullptr);
			refCount->Increment();
		}

		virtual ~SharedPtr(){
			J_ASSERT((refCount == nullptr && object == nullptr) || (refCount != nullptr && object != nullptr), "If refCount or object is null, the other MUST be null");
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
				refCount->Increment();
			}

			return *this;
		}

		constexpr bool operator==(T* other_) const{ return object == other_; }

		T& operator*(){ return *object; }
		T* operator->(){ return object; }

		template <class T2>
		T2* As() const{
			static_assert(std::is_base_of<T, T2>(), "As() type must be derived from SharedPtr type");
			return dynamic_cast<T2*>(object);
		}

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
			
			size_t oldReferenceCount = refCount->Count();
			refCount->Decrement();
			if(oldReferenceCount == 1){
				delete object;
				object = nullptr;
				refCount = nullptr; //Reference count deletes itself
			}
		}

		friend WeakPtr<T>;
	};
}

#endif //!JAMMER_MEMORY_SHARED_PTR_H