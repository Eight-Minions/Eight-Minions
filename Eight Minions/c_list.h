#ifndef C_LIST_H
#define C_LIST_H

#include <iostream>
#include <queue>
#include "c_list_node.h"

using std::queue;

template <class T>
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
	
	// Get/Set Start
	cListNode<T> *getStart ();
	void setStart (cListNode<T> *start);
	
	// Get/Set Size
	int getSize ();
	void setSize (int size);
	
	// Searching for Objects
	T getObjectWithID(int search_id);
	cListNode<T> getNodeWithID(int search_id);
	bool checkForObjectWithID(int search_id);

	// Insert or Delete
	int insertInOrder (T newData);
	bool deleteList ();
	bool deleteNode (int index);

	//void printList();
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
cListNode<T>* cList<T>::getStart(){
	return this->start;
}
// Set the start pointer
template <typename T>
void cList<T>::setStart(cListNode<T> *n_start){
	this->start = n_start;
}
// Get the size
template <typename T>
int cList<T>::getSize(){
	return this->size;
}
// Set the size
template <typename T>
void cList<T>::setSize(int n_size){
	this->size = n_size;
}
// Insert and object in order and assign it an index
template <typename T>
int cList<T>::insertInOrder(T newData){
	int new_iterator = 0;
	cListNode<T> *newNode = NULL, *cur = NULL, *prev = NULL;
	newNode = new cListNode<T> (newData);

	if(!freeIterators.empty()){
		new_iterator = freeIterators.front();
		freeIterators.pop();
	}
	else{
		this->maxIterator++;
		new_iterator = this->maxIterator;
	}
	newNode->setIndex(new_iterator);
	cur = this->getStart();

	if (cur == NULL || newNode->getIndex() <= cur->getIndex()) {
		newNode->setNext(NULL);
		this->setStart(newNode);
	}
	else {
		while ((cur != NULL) && (cur->getIndex() <= newNode->getIndex())) {
		prev = cur;
		cur = cur->getNext();
		}
		prev->setNext(newNode);
		newNode->setNext(cur);
	}
	return new_iterator;
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
// Delete a node
template <typename T>
bool cList<T>::deleteNode(int searchIndex){
	cListNode<T> *cur = NULL, *prev = NULL;
	for (cur = this->getStart(); cur != NULL; prev = cur, cur = cur->getNext()){
		if(cur->getIndex() == searchIndex){
			if(prev == NULL){
				this->setStart(cur->getNext());
			}
			else{
				prev->setNext(cur->getNext());
			}
			this->freeIterators.push(cur->getIndex());
			delete (cur);
			return true;
		}
	}
	return false;
}
// Search for an object with an ID, returns the object or null 
// Please note: this function is unsafe and being depreciated
template <typename T>
T cList<T>::getObjectWithID(int search_id){
	cListNode<T> *cur = this->getStart();
	while(cur != NULL){
		if(cur->getIndex() == search_id)
			return cur->getData();
		cur = cur->getNext();
	}
	T empty;
	return empty; //Didn't find anything...
}

// Checks to see if there is an Object with some ID
template <typename T>
bool cList<T>::checkForObjectWithID(int search_id){
	cListNode<T> *cur = this->getStart();
	while(cur != NULL){
		if(cur->getIndex() == search_id)
			return true;
		cur = cur->getNext();
	}
	return false;
}

// Gets a node with some ID, returns NULL if not found
template <typename T>
cListNode<T> cList<T>::getNodeWithID(int search_id){
	cListNode<T> *cur = getStart();
	while(cur != NULL){
		if(cur->getIndex() == search_id)
			return cur;
		cur = cur->getNext();
	}
	return NULL;
}
// TESTING ONLY 
/*
// Print the whole list
template <typename T>
void cList<T>::printList(){
	cListNode<T> *cur = NULL;
	cur = this->getStart();
	cout << "Beginning\n";
	while(cur != NULL){
		cout << "Index: " << cur->getIndex() << " Data: " << cur->getData() << endl;
		cur = cur->getNext();
	}	
	cout << "End\n";
}
*/
#endif