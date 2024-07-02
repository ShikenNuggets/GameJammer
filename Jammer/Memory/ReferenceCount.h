#ifndef JAMMER_MEMORY_REFERENCE_COUNT_H
#define JAMMER_MEMORY_REFERENCE_COUNT_H

#include <atomic>

#include "Debug.h"

namespace Jammer{
	class ReferenceCount{
	public:
		ReferenceCount() : count(0), weakCount(0){}

		void Increment(){ count++; }
		void IncrementWeakCount(){ weakCount++; }

		void Decrement(){
			J_BASIC_ASSERT(count > 0);
			if(count != 0){
				count--;
			}

			if(count == 0 && weakCount == 0){
				delete this; //This looks scary, but it's intentional
				return; //Redundant, but *absolutely nothing* should happen after deletion
			}
		}

		void DecrementWeakCount(){
			J_BASIC_ASSERT(weakCount > 0);
			if(weakCount != 0){
				weakCount--;
			}

			if(count == 0 && weakCount == 0){
				delete this; //This looks scary, but it's intentional
				return; //Redundant, but *absolutely nothing* should happen after deletion
			}
		}

		size_t Count() const{ return count; }
		bool HasReferences() const{ return count > 0; }

	private:
		std::atomic<size_t> count;
		std::atomic<size_t> weakCount;
	};
}

#endif //!JAMMER_MEMORY_REFERENCE_COUNT_H