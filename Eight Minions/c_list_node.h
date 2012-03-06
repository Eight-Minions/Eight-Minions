#ifndef C_LIST_NODE_H
#define C_LIST_NODE_H

#include <iostream>

template <typename T>
class cListNode
{
private:
	T data;
	int index;
	cListNode<T> *next;
public:
	
	cListNode (T newData, cListNode<T> *ptr = NULL);
	~ListNode ();

	void setIndex(int i);
	int getIndex(void);

	T getData (void) const;
	void setData (T newData);

	cListNode<T> * getNext (void) const;
	void setNext (cListNode<T> *next);
	
};

template <typename T>
cListNode<T>::ListNode (T newData, ListNode<T> *ptr){
	this->mData = newData;
	this->next = ptr;
	this->index = 0;
}


template <typename T>
cListNode<T>::~cListNode (){
}

template <typename T>
T cListNode<T>::getData (void) const{
	return data;
}

template <typename T>
void cListNode<T>::setData (T newData){
	data = newData;
}

template <typename T>
cListNode<T> * cListNode<T>::getNext (void) const{
	return next;
}

template <typename T>
void cListNode<T>::setNextPtr (cListNode<T> *ptr){
	next = ptr;
}

template <typename T>
void cListNode<T>::setIndex(int i){
	this->index = i;
}

template <typename T>
int cListNode<T>::getIndex(void){
	return this->index;
}
#endif