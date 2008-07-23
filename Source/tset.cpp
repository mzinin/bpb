#include "tset.h"

TSET::TSET(): trpl_list(), jTree()
{
}

TSET::~TSET()
{
	jTree.clear();

	list<Triple64*>::iterator it(trpl_list.begin());
	while( it != trpl_list.end() )
	{
		delete *it;
		it++;
	}
	trpl_list.clear();
}

void TSET::clear()
{
	jTree.clear();
	trpl_list.clear();
}

TSET::iterator TSET::erase(TSET::iterator it)
{
	jTree.del(*it);
	return trpl_list.erase(it);
}

void TSET::push_back(Triple64* new_trpl)
{
	trpl_list.push_back(new_trpl);
	jTree.insert(new_trpl);
}
