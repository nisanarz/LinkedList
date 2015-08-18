#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <exception>
#include <cstdio>

/*
template <typename K, typename D, typename Compare, typename Bigger>
class Node{
public:
	K key;
	D data;
	Node* next;
	Node(const K& key, const D& data) : key(key), data(data), next(NULL) {}
	~Node();
};*/

template <typename K, typename D, typename Compare, typename Bigger>
class LinkedList {
public:
	class Node{
	public:
		K key;
		D data;
		Node* next;
		Node(const K& key, const D& data) : key(key), data(data), next(NULL) {}
	};

private: 
	int size;
	Node* head;
	Node* tail;

	Node* getNode(const int versionCode){
		Node* tmp = head;
		while (tmp){
			if (tmp->key == versionCode){
				return tmp;
			}
			tmp = tmp->next;
		}
		return NULL;
	}
public:
	LinkedList() : size(0), head(NULL), tail(NULL) {}
	LinkedList(const K& key, const D& data) : size(1), head(new Node(key,data)),
			tail(head) {
	}
	~LinkedList(){
		if (head != NULL){
			while (head){
				Node* tmp = head;
				head = head->next;
				delete tmp;
			}
		}
	}
	void insertLast(const K& key, const D& data){
		Bigger biggerThan;
		if (head == NULL){
			head = new Node(key, data);
			tail = head;
			size++;
			return;
		}
		if (biggerThan(key, tail->key)){
			Node* nextNode = new Node(key, data);
			tail->next = nextNode;
			tail = nextNode;
			tail->next = NULL;
			size++;
			return;
		}
		throw LinkedListInvalidData();
	}
	D* getData(const K& key){
		if (head == NULL) return NULL;
		Compare comparer;
		Node* tmp = head;
		while (tmp){
			if (comparer(tmp->key, key)){
				return &(tmp->data);
			}
			tmp = tmp->next;
		}
		throw LinkedListKeyNotFound();
	}
	int getSize() const{
		return size;
	}

	int getNextVersion(const int currVersion){
		Node* currVersionNode = getNode(currVersion);
		if (currVersionNode == NULL){
			return -1;				//check this return value
		}
		return currVersionNode->next->key;
	}

	bool isExist(const K& key){
		if (head == NULL) return false;
			Compare comparer;
			Node* tmp = head;
			while (tmp){
				if (comparer(tmp->key, key)){
					return true;
				}
				tmp = tmp->next;
			}
			return false;
	}

	bool isLast(const K& key){
		Compare comparer;
		Node* tmp = head;
		while (tmp){
			if (comparer(tmp->key, key)){
				if (tmp->next == NULL){
					return true;
				}
				break;
			}
			tmp = tmp->next;
		}
		return false;
	}

	template <typename G>
	void updateDataForEach(G updateFunc){
		Node* tmp = head;
		while (tmp){
			updateFunc(tmp->data);
			tmp = tmp->next;
		}
		return;
	}

	class LinkedListKeyNotFound : public std::exception {};
	class LinkedListInvalidData : public std::exception {};
};


#endif
