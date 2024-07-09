#ifndef JAMMER_DATA_HASH_TABLE_H
#define JAMMER_DATA_HASH_TABLE_H

#include "Data/Array.h"
#include "Data/List.h"
#include "Math/Math.h"

namespace Jammer{
	template <class K, class V>
	class HashTable{
	public:
		struct KeyValuePair{
			K key;
			V value;

			constexpr KeyValuePair(const K& key_, const V& value_) : key(key_), value(value_){}
		};

		HashTable(size_t capacity_ = 1024) : data(Math::NextPrime(capacity_)){}

		void Add(const K& key_, const V& value_){
			size_t index = KeyToIndex(key_);
			while(index >= data.Size()){
				data.Add(List<KeyValuePair>());
			}

			data[index].Add(KeyValuePair(key_, value_));
		}

		bool Contains(const K& key_){
			size_t index = KeyToIndex(key_);
			if(index >= data.Size()){
				return false;
			}

			for(const auto& node : data[index]){
				if(node->value.key == key_){
					return true;
				}
			}

			return false;
		}

		void RemoveAt(const K& key_){
			size_t index = KeyToIndex(key_);
			if(index >= data.Size()){
				return;
			}

			if(data[index].IsEmpty()){
				return;
			}

			for(const auto& node : data[index]){
				if(node->value.key == key_){
					data[index].Remove(node);
					return;
				}
			}
		}

		constexpr const V& operator[](const K& key_) const{
			size_t index = KeyToIndex(key_);
			if(index >= data.Size()){
				//There's no safe way to handle this request, so just error out
				throw std::runtime_error("Tried to const[] value at unrecognized HashTable key!");
			}

			for(const auto* node : data[index]){
				GADGET_BASIC_ASSERT(node != nullptr);
				if(node->value.key == key_){
					return node->value.value;
				}
			}

			//There's no safe way to handle this request, so just error out
			throw std::runtime_error("Tried to const[] value at unrecognized HashTable key!");
		}

	private:
		Array<List<KeyValuePair>> data;

		inline size_t KeyToIndex(const K& key_) const{
			return std::hash<const char*>{}(reinterpret_cast<const char*>(&key_)) % data.Capacity();
		}
	};
}

#endif //!JAMMER_DATA_HASH_TABLE_H