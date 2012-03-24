//Easy Managed List by Jeromy Johnson
//goal: to manage a list of items that is constantly having deletions and lookups


#include <vector>
#include <iostream>
#include <queue>

using std::vector;
using std::queue;
using std::cout;

template <class T>
class EMlist
{
private:
	vector<T> Tvec;
	int maxIter;
	queue<int> openIter;
	T e;
public:

	EMlist()
	{
		maxIter = 0;
	}

	EMlist(T emp)
	{
		//accepts an empty or NULL valued object of type T to use for removals
		maxIter = 0;
		e = emp;
	}

	void setE(T emp)
	{
		e = emp;
	}

	int Add(T item)
	{
		if(openIter.empty())
		{
			maxIter++;
			Tvec.resize(maxIter);
			Tvec[maxIter - 1] = item;
			return maxIter - 1;
		}
		else
		{
			int nid = openIter.front();
			openIter.pop();
			Tvec[nid] = item;
			return nid;
		}
	}

	void Remove(int id)
	{
		Tvec[id] = e;
		this->openIter.push(id);
	}

	T gid(int id)
	{
		if (id < maxIter)
		{
			return Tvec[id];
		}
		else
		{
			cout << "ERR:Tried to access invalid object\n";
			return e;
		}
	}
};