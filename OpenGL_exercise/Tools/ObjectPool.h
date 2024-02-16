#pragma once


// class Node<T>
template <class T>
class Node {
public:
	T* data;
	Node<T>* next;
	Node(T* data, Node<T>* next);
};


template <class T>
Node<T>::Node(T* data, Node<T>* next) {
	this->data = data;
	this->next = next;
}


// class ObjectPool<T>
template <class T>
class ObjectPool {
private:


public:

	Node<T>* first;
	Node<T>* current;
	Node<T>* last;

	Node<T>* using_first;

	ObjectPool();
	~ObjectPool();

	
	void AddNode(T* data);
	Node<T>* GetNode();
	void Recycle(Node<T>* node);
	int GetLength();
	int GetUsingLength();
};



template <class T>
ObjectPool<T>::ObjectPool() {
	current = nullptr;
	first = nullptr;
	last = nullptr;
	using_first = nullptr;
}

template <class T>
ObjectPool<T>::~ObjectPool() {

}


template <class T>
void ObjectPool<T>::AddNode(T* data) {
	Node<T>* node = new Node<T>(data, nullptr);


	if (first == nullptr) {
		// no object in pool
		first = node;
		last = first;
	}
	else {
		last->next = node;
		last = last->next;
		last->next = nullptr;
	}
}


template <class T>
Node<T>* ObjectPool<T>::GetNode() {
	// get from unuse list
	current = first;
	if (current != nullptr) {
		first = current->next;
		if (current == last) last = nullptr;

		// add to using list
		current->next = using_first;
		using_first = current;
		return current;
	}
	else {
		return nullptr;
	}
}


template <class T>
void ObjectPool<T>::Recycle(Node<T>* node) {
	// if node is in using list, remove it from list
	current = using_first;
	Node<T>* previous = nullptr;
	while (current != nullptr) {
		if (current == node) {
			if (current == using_first) {
				using_first = current->next;
				break;
			}
			else {
				previous->next = current->next;
				break;
			}
		}
		else {
			previous = current;
			current = current->next;
		}
	}

	if (last == nullptr) {
		// no node in unuse list
		first = last = node;
	}
	else {
		last->next = node;
		last = node;
	}
	last->next = nullptr;
}


template <class T>
int ObjectPool<T>::GetLength() {
	int length = 0;
	current = first;
	while (current != nullptr) {
		length++;
		current = current->next;
	}

	return length;
}


template <class T>
int ObjectPool<T>::GetUsingLength() {
	int length = 0;
	current = using_first;
	while (current != nullptr) {
		length++;
		current = current->next;
	}

	return length;
}