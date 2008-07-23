#ifndef QSET_H
#define QSET_H

#include "triple64.h"
#include <list>
#include <algorithm>

class QSET
{
public:
	list<Triple64*> trpl_list;
	//list<Poly64*> poly_buffer;

public:
	QSET();
	QSET(list<Poly64*> &basis);
	~QSET();

	void insert(list<Poly64*> &add_list);
	void insert(list<Triple64*> &add_list);
	void update(Triple64* new_trpl, list<Triple64*> &set);
	Triple64* get();

	bool empty() { return trpl_list.empty(); }
	size_t size() { return trpl_list.size(); };
	void delete_Descendant(Triple64* ancestor);
};

#endif // QSET_H
