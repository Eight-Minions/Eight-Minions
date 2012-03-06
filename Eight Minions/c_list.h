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

	bool insertInOrder (T newData);
	bool deleteList ();
	bool deleteNode (T &key);
	
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

}
// Get Start
template <typename T>
cListNode<T> cList<T>::*getStart (){
	return this->start;
}
// Set the start pointer
template <typename T>
void cList<T>::setStart (cListNode<T> *start){

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

	this->size++;
	return true;
}
// Delete the list
template <typename T>
bool cList<T>::deleteList (){

	return true;
}
// Delete a node;
template <typename T>
bool cList<T>::deleteNode (T &key){

	this->size--;
	return true;
}


#endif