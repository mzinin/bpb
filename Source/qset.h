#ifndef QSET_H
#define QSET_H

#include "triple64.h"
#include <list>
#include <algorithm>

class QSET
{
	list<Triple64*> trpl_list;

  	Triple64* PfindR(Triple64 *t, list<Triple64*> &Q);
  	Triple64* PReduce(Triple64 *t, list<Triple64*> &Q);

public:
	QSET();
	QSET(list<Poly64*> &basis);
	~QSET();

	void insert(list<Poly64*> &add_list);
	void insert(Triple64* new_trpl) { trpl_list.push_back(new_trpl); }
	Triple64* get();

	bool empty() { return trpl_list.empty(); }
	size_t size() { return trpl_list.size(); }
	Triple64* back() { return trpl_list.back(); }

	void PAutoReduce();
};

#endif // QSET_H
