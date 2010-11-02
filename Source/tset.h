#ifndef TSET_H
#define TSET_H

#include "janettree.h"
#include <list>
#include <map>
#include <algorithm>

class TSET
{
private:
#ifdef USE_NOVA_INVOLUTION
    typedef std::map<Monom::Integer, unsigned> VarCountMap;
    struct FullDegreeInfo
    {
        JanetTree JTree;
        VarCountMap VCMap;
    };
    typedef std::map<Monom::Integer, FullDegreeInfo> FullDegreeInfoMap;

    FullDegreeInfoMap degreeInfos;
#endif
    std::list<Triple*> tripleList;
    JanetTree jTree;

public:
    typedef std::list<Triple*>::iterator iterator;
    typedef std::list<Triple*>::const_iterator const_iterator;

    TSET();
    ~TSET();

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

#ifdef USE_NOVA_INVOLUTION
    std::set<Monom::Integer> NonMultiNova(const Triple* triple);
#endif
};


inline const Triple* TSET::Find(const Monom& monom) const
{
    return jTree.Find(monom);
}

inline TSET::iterator TSET::Begin()
{
    return tripleList.begin();
}

inline TSET::const_iterator TSET::Begin() const
{
    return tripleList.begin();
}

inline TSET::iterator TSET::End()
{
    return tripleList.end();
}

inline TSET::const_iterator TSET::End() const
{
    return tripleList.end();
}

inline std::size_t TSET::Size() const
{
    return tripleList.size();
}

inline Triple* const TSET::Back() const
{
    return tripleList.back();
}

#endif // TSET_H
