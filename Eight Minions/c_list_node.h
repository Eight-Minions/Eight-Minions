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
	~cListNode ();

	void setIndex(int i);
	void setForcedIndex(int i);
	int getIndex(void);

	T getData (void) const;
	void setData (T newData);

	cListNode<T> * getNext (void) const;
	void setNext (cListNode<T> *next);
	
};
// Creates a new dode
template <typename T>
cListNode<T>::cListNode (T newData, cListNode<T> *ptr){
	this->data = newData;
	this->next = ptr;
	this->index = 0;
}
// Delete a node
template <typename T>
cListNode<T>::~cListNode (){
}
// Returns the data
template <typename T>
T cListNode<T>::getData (void) const{
	return data;
}
// Sets tha data
template <typename T>
void cListNode<T>::setData (T newData){
	data = newData;
}
// Gets the next cListNode<T>
template <typename T>
cListNode<T> * cListNode<T>::getNext (void) const{
	return next;
}
// Sets the next cListNode<T>
template <typename T>
void cListNode<T>::setNext(cListNode<T> *ptr){
	next = ptr;
}
// Sets the index (If it hasn't been set)
template <typename T>
void cListNode<T>::setIndex(int i){
	if(this->index == 0)
		this->index = i;
}
// Force sets the index
template <typename T>
void cListNode<T>::setForcedIndex(int i){
	this->index = i;
}

// Gets the index
template <typename T>
int cListNode<T>::getIndex(void){
	return this->index;
}
#endif