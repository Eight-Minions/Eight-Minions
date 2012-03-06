#ifndef C_LIST_H
#define C_LIST_H

#include <queue>
#include "c_list_node.h"

using std::queue;

template <typename T>
class cList
{
private:
	cListNode<T> *start;
	queue<int> freeIterators;
	int maxIterator;
	int size;
public:
	cList ();
	~cList ();

	cListNode<T> *getStart ();
	void setStart (cListNode<T> *start);

	int getSize ();
	void setSize (int size);

	T *getObjectWithID(int search_id);

	// Not implemented yet 
	bool insertInOrder (T newData);
	bool deleteList ();
	bool deleteNode (T &key);
	//
};

// Create a list
template <typename T>
cList<T>::cList (){
	start = NULL;
	maxIterator = 0;
	size = 0;
}
// Delete the List
template <typename T>
cList<T>::~cList (){
	deleteList();
}
// Get Start
template <typename T>
cListNode<T> cList<T>::*getStart (){
	return this->start;
}
// Set the start pointer
template <typename T>
void cList<T>::setStart (cListNode<T> *n_start){
	this->start = n_start;
}
// Get the size
template <typename T>
int cList<T>::getSize (){
	return this->size;
}
// Set the size
template <typename T>
void cList<T>::setSize (int n_size){
	this->size = n_size;
}
// Insert a new item in order
template <typename T>
bool cList<T>::insertInOrder (T newData){
	int new_iterator = 0;
	cListNode<T> *newNode = NULL, *cur = NULL, *prev = NULL;
	newNode = new cListNode<T> (newData);

	if(!freeIterators.empty()){
		new_iterator = freeIterators.front();
		freeIterators.pop();
	}
	else{
		this->maxIterator++;
		new_iterator = maxIterator;
	}
	newNode->setIndex(new_iterator);

	cur = this->getStart();
	while (cur != NULL){


		cur = cur->getNext();
	}

	// Insert it in the right place...


	this->size++;
	return true;
}
// Delete the list
template <typename T>
bool cList<T>::deleteList (){
	cListNode<T> *temp = NULL, *del = NULL;
	bool success = false;

	temp = this->getStart();
	while (temp != NULL){
		del= temp;
		temp= temp->getNext();
		delete del;
		success = true;
	}
	return success;
}

// Delete a node;
template <typename T>
bool cList<T>::deleteNode (T &key){
	bool success = false;
	cListNode<T> *prev = NULL, *cur = NULL, *temp = NULL;
	cur = this->getStart();
	if (cur != NULL)
	{
		while ((cur != NULL) && ((cur -> getData ()) != key)){
			prev = cur;
			cur = cure->getNext();
		}
		if ((cur != NULL) && (prev != NULL)){
			temp = cur;
			prev->setNext(cur->getNext());
			freeIterators->push((temp->getData())->getIndex());
			delete temp;
			success = true;
			size--;
		}
		else if (cur != NULL){
			temp = cur;
			start = start->getNext();
			freeIterators->push((temp->getData())->getIndex());
			delete temp;
			success = true;
			size --;
		}
	}
	return success;
}

// Search for an object with an ID, returns the object or null 
template <typename T>
T cList<T>::*getObjectWithID(int search_id){
	cListNode<T> cur = this->getStart();
	while(cur != NULL){
		if(((cur->getData())->getIndex()) == search_id)
			return cur->getData();
		cur = cur->getNext();
	}
	return NULL; 
}
#endif