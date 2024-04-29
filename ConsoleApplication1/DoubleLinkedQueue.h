#pragma once
#include"QueueADT.h"
#include"DoubleNode.h"
#include"DoubleLinkedQueue.h"
#include<iostream>
using namespace std;
template<typename T>
class DoubleLinkedQueue:public QueueADT<T> {
protected:
	DoubleNode<T>* frontptr;
	DoubleNode<T>* backptr;
public:
	DoubleLinkedQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	bool enqueuefirst(const T& newEntry);
	bool dequeuelast(T& backEntry);
	void print()const;
	~DoubleLinkedQueue();
};
template<typename T>
DoubleLinkedQueue<T>::DoubleLinkedQueue() {
	frontptr = backptr = nullptr;
}
template<typename T>
bool DoubleLinkedQueue<T>::isEmpty() const {
	return frontptr == nullptr;
}
template<typename T>
bool DoubleLinkedQueue<T>::enqueue(const T& newEntry) {
	DoubleNode<T>* newnode = new DoubleNode<T>(newEntry);
	if (isEmpty()) {
		frontptr = backptr = newnode;
		newnode->setNext(nullptr);
		newnode->setprev(nullptr);
	}
	else {
		backptr->setNext(newnode);
		newnode->setprev(backptr);
		newnode->setNext(nullptr);
		backptr = newnode;
	}
	return true;
}
template<typename T>
bool DoubleLinkedQueue<T>::dequeue(T& frntEntry) {
	if (isEmpty())
		return false;
	else if(frontptr==backptr) {
		frntEntry = frontptr->getItem();
		delete frontptr;
		frontptr = backptr = nullptr;
		return true;
	}
	else{
		frntEntry = frontptr->getItem();
		DoubleNode<T>* cur = frontptr;
		frontptr = frontptr->getNext();
		frontptr->setprev(nullptr);
		delete cur;
		return true;
	}
}

template<typename T>
bool DoubleLinkedQueue<T>::enqueuefirst(const T& newEntry) {
	DoubleNode<T>* newnode = new DoubleNode<T>(newEntry);
	if (frontptr == nullptr) {
		frontptr = backptr = newnode;
		newnode->setNext(nullptr);
		newnode->setprev(nullptr);
	}
	else {
		newnode->setNext(frontptr);
		frontptr->setprev(newnode);
		newnode->setprev(nullptr);
		frontptr = newnode;
	}
	return true;
}

template<typename T>
bool DoubleLinkedQueue<T>::dequeuelast(T& backEntry) {
	if (isEmpty())
		return false;
	else if (frontptr == backptr) {
		backEntry = backptr->getItem();
		delete frontptr;
		frontptr = backptr = nullptr;
		return true;
	}
	else {
		DoubleNode<T>* cur = backptr;
		backEntry = backptr->getItem();
		backptr = backptr->getprev();
		backptr->setNext(nullptr);
		delete cur;
		return true;
	}
}

template<typename T>
bool DoubleLinkedQueue<T>::peek(T& frntEntry)  const {
	if (isEmpty())
		return false;

	frntEntry = frontptr->getItem();
	return true;

}

template<typename T>
void DoubleLinkedQueue<T>::print()const {
	if (isEmpty())return;
	DoubleNode<T>* cur = frontptr;
	while (cur->getNext() != nullptr) {
		cout << cur->getItem() << ", ";
		cur = cur->getNext();
	}
	cout << cur->getItem();
}

template<typename T>
DoubleLinkedQueue<T>::~DoubleLinkedQueue() {
	DoubleNode<T>* cur = frontptr;
	while (cur != nullptr) {
		frontptr = frontptr->getNext();
		delete cur;
		cur = frontptr;
	}
}
