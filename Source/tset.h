#ifndef TSET_H
#define TSET_H

#include "janettree.h"
#include <list>
#include <map>
#include <algorithm>

class TSet
{
private:
    typedef std::map<Monom::Integer, unsigned> VarCountMap;
    struct FullDegreeInfo
    {
        JanetTree JTree;
        VarCountMap VCMap;
    };
    typedef std::map<Monom::Integer, FullDegreeInfo> FullDegreeInfoMap;
    FullDegreeInfoMap DegreeInfos;

    std::list<Triple*> TripleList;
    JanetTree JTree;

public:
    typedef std::list<Triple*>::iterator Iterator;
    typedef std::list<Triple*>::const_iterator ConstIterator;

    TSet();
    ~TSet();

    Iterator Begin();
    ConstIterator Begin() const;
    Iterator End();
    ConstIterator End() const;

    void Clear();
    Iterator Erase(Iterator it);
    void PushBack(Triple* newTriple);
    std::size_t Size() const;

    const Triple* Find(const Monom& monom) const;
    Triple* const Back() const;

    void CollectNonMultiProlongations(Iterator& iterator, std::list<Triple*>& set);
    std::set<Monom::Integer> NonMultiNova(const Triple* triple);
};


inline const Triple* TSet::Find(const Monom& monom) const
{
    return JTree.Find(monom);
}

inline TSet::Iterator TSet::Begin()
{
    return TripleList.begin();
}

inline TSet::ConstIterator TSet::Begin() const
{
    return TripleList.begin();
}

inline TSet::Iterator TSet::End()
{
    return TripleList.end();
}

inline TSet::ConstIterator TSet::End() const
{
    return TripleList.end();
}

inline std::size_t TSet::Size() const
{
    return TripleList.size();
}

inline Triple* const TSet::Back() const
{
    return TripleList.back();
}

#endif // TSET_H
