#ifndef JAMMER_ARRAY_H
#define JAMMER_ARRAY_H

#include <cassert>

namespace Jammer{
	template <class T>
	class Array{
	public:
		Array(size_t initialCapacity_ = 16) : data(nullptr), size(0), capacity(initialCapacity_){
			data = new T[capacity];
		}

		Array(const Array<T>& array_) : data(nullptr), size(0), capacity(array_.capacity){
			data = new T[capacity];
			for(size_t i = 0; i < array_.Size(); i++){
				Add(array_[i]);
			}
		}

		constexpr Array<T>& operator=(const Array<T>& other_){
			if(data != nullptr){
				delete[] data;
				size = 0;
			}

			capacity = other_.Capacity();
			data = new T[capacity];
			for(size_t i = 0; i < other_.Size(); i++){
				Add(other_[i]);
			}

			return *this;
		}

		~Array(){
			delete[] data;
		}

		void Add(const T& value_){
			if(capacity == 0){
				Reserve(16);
			}

			if(size >= capacity){
				Reserve(capacity * 2);
			}

			data[size] = value_;
			size++;
		}

		void Add(const T* range_, size_t rangeSize_){
			Reserve(size + rangeSize_);
			for(size_t i = 0; i < rangeSize_; i++){
				Add(range_[i]);
			}
		}

		constexpr void Pop(size_t elementsToPop = 1){
			for(size_t i = size - 1; i > size - elementsToPop; i--){
				data[i].~T();
			}

			if(size - elementsToPop < 0){
				size = 0;
			}else{
				size -= elementsToPop;
			}
		}

		constexpr void RemoveAt(size_t index_){
			if(index_ >= size){
				return;
			}

			data[index_].~T();

			for(size_t i = index_; i < size - 1; i++){
				data[i] = data[i + 1];
			}

			size--;
		}

		void Reserve(size_t newCapacity_){
			if(newCapacity_ <= capacity){
				return;
			}

			capacity = newCapacity_;
			Reallocate();
		}

		constexpr const T& operator[](size_t i_) const{
			return data[i_];
		}

		constexpr T& operator[](size_t i_){
			return data[i_];
		}

		constexpr size_t Size() const{ return size; }
		constexpr bool IsEmpty() const{ return size == 0; }
		constexpr size_t Capacity() const{ return capacity; }

	private:
		T* data;
		size_t size;
		size_t capacity;

		void Reallocate(){
			T* newData = new T[capacity];
			assert(capacity >= size);
			for(size_t i = 0; i < size; i++){
				newData[i] = data[i];
			}

			delete[] data;
			data = newData;
		}
	};
}

#endif //!JAMMER_ARRAY_H