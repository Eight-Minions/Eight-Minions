#ifndef C_LIST_NODE_H
#define C_LIST_NODE_H

#include <iostream>

template <typename T>
class cListNode
{
private:
	T mData;
	int index;
	cListNode<T> *mNext;
public:
	/*
	cListNode (T newData, cListNode<T> *newPtr = NULL);
	cListNode (cListNode<T> &newNode);
	~ListNode ();
	cListNode & operator= (const cListNode<T> &rhs);
	T getData (void) const;
	void setData (T newData);
	cListNode<T> * getNext (void) const;
	void setNext (cListNode<T> *next);
	*/
};

#endif