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
	/*
	cList ();
	~cList ();
	cListNode<T> *getStart ();
	void setStart (cListNode<T> *start);
	int getSize ();
	void setSize (int size);

	bool insertInOrder (T newData);
	bool deleteList ();
	bool deleteNode (T &key);
	*/
};

#endif