#include "qset.h"

QSET::QSET(): tripleList()
{
}

QSET::QSET(const std::list<Polynom*>& basis): tripleList()
{
    std::list<Polynom*>::const_iterator itBasis(basis.begin());
    while (itBasis != basis.end())
    {
        tripleList.push_back(new Triple(*itBasis));
        itBasis++;
    }
    tripleList.sort(Triple::Compare);
}

QSET::~QSET()
{
    std::list<Triple*>::iterator it(tripleList.begin());
    while( it != tripleList.end() )
    {
        delete *it;
        it++;
    }
    tripleList.clear();
}

void QSET::Insert(std::list<Polynom*>& addList)
{
    std::list<Polynom*>::const_iterator itBasis(addList.begin());
    while ( itBasis != addList.end() )
    {
        tripleList.push_back(new Triple(*itBasis));
        itBasis++;
    }
    tripleList.sort(Triple::Compare);
}

void QSET::Insert(std::list<Triple*>& addList)
{
    addList.sort(Triple::Compare);
    tripleList.merge(addList, Triple::Compare);
}

Triple* QSET::Get()
{
    Triple* result = tripleList.back();
    tripleList.pop_back();
    return result;
}

void QSET::DeleteDescendants(const Triple* ancestor)
{
    std::list<Triple*>::iterator it(tripleList.begin());
    while ( it != tripleList.end() )
    {
        if ((**it).GetAnc() == ancestor || (**it).GetWAnc() == ancestor)
        {
            delete *it;
            it = tripleList.erase(it);
        }
        else
        {
            it++;
        }
    }
}
