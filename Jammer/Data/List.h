#ifndef JAMMER_DATA_LIST_H
#define JAMMER_DATA_LIST_H

namespace Jammer{
	template <class T>
	class List{
	public:
		struct Node{
			T value;
			Node* next;

			constexpr Node(const T& value_) : value(value_), next(nullptr){}
		};

		class Iterator{
		public:
			constexpr Iterator(const Node* node_) : currentNode(node_){}

			constexpr inline const Node* operator*(){ return currentNode; }
			
			constexpr inline void operator++(){
				if(currentNode != nullptr){
					currentNode = currentNode->next;
				}
			}

			constexpr inline bool operator!=(const Iterator& it_){ return currentNode != it_.currentNode; }

		private:
			const Node* currentNode;
		};

		constexpr List() : size(0), head(nullptr), tail(nullptr){}

		constexpr ~List(){
			while(!IsEmpty()){
				Pop();
			}
		}

		inline void Add(const T& value_){
			Node* newNode = new Node(value_);

			if(IsEmpty()){
				head = newNode;
				tail = head;
			}else{
				tail->next = newNode;
				tail = tail->next;
			}

			size++;
		}

		constexpr inline void Pop(){
			if(IsEmpty()){
				return;
			}else if(size == 1){
				delete head;
				head = nullptr;
				tail = nullptr;
				size--;
				return;
			}

			tail = SecondLast();
			delete tail->next;
			tail->next = nullptr;

			size--;
		}

		constexpr inline void Remove(const Node* node_){
			if(IsEmpty()){
				return;
			}

			if(node_ == head){
				head = head->next;
				delete node_;
			}else if(node_ == tail){
				Pop();
				return;
			}

			Node* prev = head;
			Node* cur = head->next;
			while(cur != nullptr){
				if(cur == node_){
					prev->next = cur->next;
					delete cur;
					return;
				}
			}
		}

		constexpr inline void Remove(const T& value_){
			if(IsEmpty()){
				return;
			}

			if(head->value == value_){
				Node* oldHead = head;
				head = head->next;
				delete oldHead;
			}else if(tail->value == value_){
				Pop();
				return;
			}

			Node* prev = head;
			Node* cur = head->next;
			while(cur != nullptr){
				if(cur->value == value_){
					prev->next = cur->next;
					delete cur;
					return;
				}
			}
		}

		constexpr inline size_t Size() const{ return size; }
		constexpr inline bool IsEmpty() const{ return size == 0; }
		constexpr inline Node* Front(){ return head; }
		constexpr inline Node* Back(){ return tail; }

		constexpr inline Node* SecondLast() const{
			if(IsEmpty()){
				return nullptr;
			}

			Node* prev = nullptr;
			Node* cur = head;
			while(cur != tail && cur != nullptr){
				prev = cur;
				cur = cur->next;
			}

			return prev;
		}

		constexpr Iterator begin(){ return Iterator(head); }
		constexpr const Iterator begin() const{ return Iterator(head); }
		constexpr Iterator end(){ return Iterator(nullptr); }
		constexpr const Iterator end() const{ return Iterator(nullptr); }

	private:
		size_t size;
		Node* head;
		Node* tail;
	};
}

#endif //!JAMMER_DATA_LIST_H