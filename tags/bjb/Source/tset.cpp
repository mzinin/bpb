#include <set>
#include "tset.h"

void TSet::Clear()
{
    JTree.Clear();

    Iterator it = TripleList.begin();
    while (it != TripleList.end())
    {
        delete *it;
        ++it;
    }
    TripleList.clear();
}

void TSet::CollectNonMultiProlongations(TSet::Iterator& iterator, std::list<Triple*>& set)
{
    if (iterator == TripleList.end() || !(*iterator))
    {
        return;
    }

    std::set<Monom::Integer> nonMultiVars = JTree.NonMulti(*iterator);
    std::set<Monom::Integer>::const_iterator nmvIterator = nonMultiVars.begin();
    for (; nmvIterator != nonMultiVars.end(); ++nmvIterator)
    {
        if (!(**iterator).TestNmp(*nmvIterator))
        {
            (**iterator).SetNmp(*nmvIterator);
            Polynom* tmpPolynom = new Polynom(*(**iterator).GetPolynom());

            tmpPolynom->Multiply(*nmvIterator, 1);
            set.push_back(new Triple(tmpPolynom
                                   , (**iterator).GetAncestor()
                                   , (**iterator).GetNmp()
                                   , (*iterator)
                                   , *nmvIterator)
                          );
            delete tmpPolynom;
        }
    }
}