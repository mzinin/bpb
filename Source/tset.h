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
    FullDegreeInfoMap degreeInfos;

    std::list<Triple*> tripleList;
    JanetTree jTree;

public:
    typedef std::list<Triple*>::iterator iterator;
    typedef std::list<Triple*>::const_iterator const_iterator;

    TSet();
    ~TSet();

    iterator Begin();
    const_iterator Begin() const;
    iterator End();
    const_iterator End() const;

    void Clear();
    iterator Erase(iterator it);
    void PushBack(Triple* newTriple);
    std::size_t Size() const;

    const Triple* Find(const Monom& monom) const;
    Triple* const Back() const;

    void CollectNonMultiProlongations(iterator& iterator, std::list<Triple*>& set);
    std::set<Monom::Integer> NonMultiNova(const Triple* triple);
};


inline const Triple* TSet::Find(const Monom& monom) const
{
    return jTree.Find(monom);
}

inline TSet::iterator TSet::Begin()
{
    return tripleList.begin();
}

inline TSet::const_iterator TSet::Begin() const
{
    return tripleList.begin();
}

inline TSet::iterator TSet::End()
{
    return tripleList.end();
}

inline TSet::const_iterator TSet::End() const
{
    return tripleList.end();
}

inline std::size_t TSet::Size() const
{
    return tripleList.size();
}

inline Triple* const TSet::Back() const
{
    return tripleList.back();
}

#endif // TSET_H
