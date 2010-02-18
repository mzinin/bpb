#include "tset.h"

TSET::TSET(): tripleList(), jTree()
{
}

TSET::~TSET()
{
    jTree.Clear();

    iterator it(tripleList.begin());
    while (it != tripleList.end())
    {
        delete *it;
        it++;
    }
    tripleList.clear();
}

void TSET::Clear()
{
    jTree.Clear();
    tripleList.clear();
}

TSET::iterator TSET::Erase(TSET::iterator it)
{
    jTree.Delete(*it);
    return tripleList.erase(it);
}

void TSET::PushBack(Triple* newTriple)
{
    tripleList.push_back(newTriple);
    jTree.Insert(newTriple);
}
