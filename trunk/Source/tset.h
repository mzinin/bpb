#ifndef TSET_H
#define TSET_H

#include <list>
#include <map>
#include <algorithm>
#include "janettree.h"
#include "settings_manager.h"

template <typename MonomType>
class TSet
{
private:
    typedef std::map<typename MonomType::Integer, unsigned> VarCountMap;
    struct FullDegreeInfo
    {
        JanetTree<MonomType> JTree;
        VarCountMap VCMap;
    };
    typedef std::map<typename MonomType::Integer, FullDegreeInfo> FullDegreeInfoMap;
    FullDegreeInfoMap DegreeInfos;

    std::list<Triple<MonomType>*> TripleList;
    JanetTree<MonomType> JTree;

public:
    typedef typename std::list<Triple<MonomType>*>::iterator Iterator;
    typedef typename std::list<Triple<MonomType>*>::const_iterator ConstIterator;

    TSet();
    ~TSet();

    Iterator Begin();
    ConstIterator Begin() const;
    Iterator End();
    ConstIterator End() const;

    void Clear();
    Iterator Erase(Iterator it);
    void PushBack(Triple<MonomType>* newTriple);
    std::size_t Size() const;

    const Triple<MonomType>* Find(const MonomType& monom) const;
    Triple<MonomType>* const Back() const;
    
    void CollectNonMultiProlongations(Iterator& iterator, std::list<Triple<MonomType>*>& set);
    std::set<typename MonomType::Integer> NonMultiNova(const Triple<MonomType>* triple);
};

template <typename MonomType>
TSet<MonomType>::TSet()
    : TripleList()
    , JTree()
    , DegreeInfos()
{
}

template <typename MonomType>
TSet<MonomType>::~TSet()
{
    Clear();
}

template <typename MonomType>
inline typename TSet<MonomType>::Iterator TSet<MonomType>::Begin()
{ 
    return TripleList.begin();
}

template <typename MonomType>
inline typename TSet<MonomType>::ConstIterator TSet<MonomType>::Begin() const
{ 
    return TripleList.begin();
}

template <typename MonomType>
inline typename TSet<MonomType>::Iterator TSet<MonomType>::End()
{ 
    return TripleList.end();
}

template <typename MonomType>
inline typename TSet<MonomType>::ConstIterator TSet<MonomType>::End() const 
{ 
    return TripleList.end(); 
}

template <typename MonomType>
inline void TSet<MonomType>::Clear()
{
    JTree.Clear();

    if (GetSettingsManager().GetUseNovaInvolution())
    {
        DegreeInfos.clear();
    }

    Iterator it = TripleList.begin();
    while (it != TripleList.end())
    {
        delete *it;
        ++it;
    }
    TripleList.clear();
}

template <typename MonomType>
inline typename TSet<MonomType>::Iterator TSet<MonomType>::Erase(typename TSet<MonomType>::Iterator it)
{
    if (GetSettingsManager().GetUseNovaInvolution())
    {
        Monom::Integer degree = (**it).GetPolynomLm().Degree();
        DegreeInfos[degree].JTree.Delete(*it);
        VarCountMap& deletedVarCountMap = DegreeInfos[degree].VCMap;
        std::set<Monom::Integer> deletedVarSet = (**it).GetPolynomLm().GetVariablesSet();
        for (std::set<Monom::Integer>::const_iterator i = deletedVarSet.begin(); i != deletedVarSet.end(); ++i)
        {
            --deletedVarCountMap[*i];
        }
    }

    JTree.Delete(*it);
    return TripleList.erase(it);
}

template <typename MonomType>
inline void TSet<MonomType>::PushBack(Triple<MonomType>* newTriple)
{
    TripleList.push_back(newTriple);
    JTree.Insert(newTriple);
    
    if (GetSettingsManager().GetUseNovaInvolution())
    {
        typename MonomType::Integer degree = newTriple->GetPolynomLm().Degree();
        DegreeInfos[degree].JTree.Insert(newTriple);
        VarCountMap& addedVarCountMap = DegreeInfos[degree].VCMap;
        std::set<typename MonomType::Integer> addedVarSet = newTriple->GetPolynomLm().GetVariablesSet();
        for (typename std::set<typename MonomType::Integer>::const_iterator i = addedVarSet.begin(); i != addedVarSet.end(); ++i)
        {
            ++addedVarCountMap[*i];
        }
    }
}

template <typename MonomType>
inline std::size_t TSet<MonomType>::Size() const 
{ 
    return TripleList.size();
}

template <typename MonomType>
inline const Triple<MonomType>* TSet<MonomType>::Find(const MonomType& monom) const 
{ 
    return JTree.Find(monom);
}

template <typename MonomType>
inline Triple<MonomType>* const TSet<MonomType>::Back() const 
{ 
    return TripleList.back();
}

template <typename MonomType>
void TSet<MonomType>::CollectNonMultiProlongations(typename TSet<MonomType>::Iterator& iterator, std::list<Triple<MonomType>*>& set)
{
    if (iterator == TripleList.end() || !(*iterator))
    {
        return;
    }

    if (GetSettingsManager().GetUseNovaInvolution())
    {
        std::set<typename MonomType::Integer> nonMultiVars = NonMultiNova(*iterator);
        typename std::set<typename MonomType::Integer>::const_iterator nmvIterator = nonMultiVars.begin();
        for (; nmvIterator != nonMultiVars.end(); ++nmvIterator)
        {
            if (!(**iterator).TestNmp(*nmvIterator))
            {
                Polynom<MonomType>* tmpPolynom = new Polynom<MonomType>(*(**iterator).GetPolynom());
                (*tmpPolynom) *= *nmvIterator;

                (**iterator).SetNmp(*nmvIterator);

                if (!tmpPolynom->IsZero())
                {
                    set.push_back(new Triple<MonomType>(tmpPolynom
                                                      , (**iterator).GetAncestor()
                                                      , (**iterator).GetNmp()
                                                      , (*iterator)
                                                      , *nmvIterator)
                                 );
                }
                delete tmpPolynom;
            }
        }
    }
    else
    {
        typename MonomType::Integer firstMultiVar = (**iterator).GetPolynomLm().FirstMultiVar();
        for (register typename MonomType::Integer var = 0; var < firstMultiVar; ++var)
        {
            if (!(**iterator).TestNmp(var))
            {
                Polynom<MonomType>* tmpPolynom = new Polynom<MonomType>(*(**iterator).GetPolynom());
                (*tmpPolynom) *= var;

                (**iterator).SetNmp(var);

                if (!tmpPolynom->IsZero())
                {
                    set.push_back(new Triple<MonomType>(tmpPolynom
                                                      , (**iterator).GetAncestor()
                                                      , (**iterator).GetNmp()
                                                      , (*iterator)
                                                      , var)
                                 );
                }
                delete tmpPolynom;
            }
        }
    }
}

template <typename MonomType>
std::set<typename MonomType::Integer> TSet<MonomType>::NonMultiNova(const Triple<MonomType>* triple)
{
    typename MonomType::Integer degree = triple->GetPolynomLm().Degree();
    std::set<typename MonomType::Integer> nmulti = DegreeInfos[degree].JTree.NonMulti(triple);

    for (typename MonomType::Integer var = 0; var < MonomType::GetDimIndepend(); ++var)
    {
        if (nmulti.find(var) != nmulti.end())
        {
            continue;
        }

        typename MonomType::Integer i = degree;
        for (typename MonomType::Integer i = degree; i > 0; --i)
        {
            if (DegreeInfos[i-1].VCMap[var])
                break;
        }

        if (!i)
        {
            nmulti.insert(var);
        }
    }

    return nmulti;
}

#endif // TSET_H
