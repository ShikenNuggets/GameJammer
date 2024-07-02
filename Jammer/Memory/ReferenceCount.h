#ifndef JAMMER_MEMORY_REFERENCE_COUNT_H
#define JAMMER_MEMORY_REFERENCE_COUNT_H

#include <atomic>

#include "Debug.h"

namespace Jammer{
	class ReferenceCount{
	public:
		ReferenceCount() : count(0){}

		void Increment(){
			count++;
		}

		void Decrement(){
			J_BASIC_ASSERT(count > 0);
			if(count == 0){
				return;
			}

			count--;
		}

		void operator ++(){
			Increment();
		}

		void operator --(){
			Decrement();
		}

		size_t Count() const{ return count; }
		bool HasReferences() const{ return count > 0; }

	private:
		std::atomic<size_t> count;
	};
}

#endif //!JAMMER_MEMORY_REFERENCE_COUNT_H