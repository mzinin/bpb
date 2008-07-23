#ifndef TSET_H
#define TSET_H

#include "janettree64.h"
#include <list>
#include <algorithm>

class TSET
{
	list<Triple64*> trpl_list;
	JanetTree64 jTree;

public:
	TSET();
	~TSET();

	Triple64* find(const Monom64& m) const { return jTree.find(m); };

	typedef list<Triple64*>::iterator iterator;
	typedef list<Triple64*>::const_iterator const_iterator;

	iterator begin() { return trpl_list.begin(); };
	const_iterator begin() const { return trpl_list.begin(); };
	iterator end() { return trpl_list.end(); };
	const_iterator end() const { return trpl_list.end(); };

	void clear();
	iterator erase(iterator it);
	void push_back(Triple64* new_trpl);
	size_t size() const { return trpl_list.size(); };

	Triple64* const back() const { return trpl_list.back(); };
};

#endif // TSET_H
