#include "qset.h"

void QSet::Insert(std::list<Polynom*>& addList)
{
    std::list<Polynom*>::const_iterator itBasis(addList.begin());
    while ( itBasis != addList.end() )
    {
        if (*itBasis)
        {
            TripleList.push_back(new Triple(*itBasis));
        }
        ++itBasis;
    }
    TripleList.sort(Triple::Compare);
}

void QSet::Insert(std::list<Triple*>& addList)
{
    addList.sort(Triple::Compare);
    TripleList.merge(addList, Triple::Compare);
}

void QSet::Clear()
{
    std::list<Triple*>::iterator it(TripleList.begin());
    while (it != TripleList.end())
    {
        delete *it;
        ++it;
    }
    TripleList.clear();
}

void QSet::DeleteDescendants(const Triple* ancestor)
{
    if (!ancestor)
    {
        return;
    }

    std::list<Triple*>::iterator it(TripleList.begin());
    while ( it != TripleList.end() )
    {
        if ((**it).GetAncestor() == ancestor || (**it).GetWeakAncestor() == ancestor)
        {
            delete *it;
            it = TripleList.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
