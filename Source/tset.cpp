#include "tset.h"

TSET::TSET(): tripleList(), jTree()
{
}

TSET::~TSET()
{
    jTree.clear();

    iterator it(tripleList.begin());
    while (it != tripleList.end())
    {
        delete *it;
        it++;
    }
    tripleList.clear();
}

void TSET::clear()
{
    jTree.clear();
    tripleList.clear();
}

TSET::iterator TSET::erase(TSET::iterator it)
{
    jTree.del(*it);
    return tripleList.erase(it);
}

void TSET::push_back(Triple* newTriple)
{
    tripleList.push_back(newTriple);
    jTree.insert(newTriple);
}
