#include "tset.h"
#include "settings_manager.h"

TSet::TSet(): tripleList()
            , jTree()
            , degreeInfos()
{
}

TSet::~TSet()
{
    Clear();
}

void TSet::Clear()
{
    jTree.Clear();

    if (GetSettingsManager().UseNovaInvolution)
    {
        degreeInfos.clear();
    }

    iterator it(tripleList.begin());
    while (it != tripleList.end())
    {
        delete *it;
        ++it;
    }
    tripleList.clear();
}

TSet::iterator TSet::Erase(TSet::iterator it)
{
    if (GetSettingsManager().UseNovaInvolution)
    {
        Monom::Integer degree = (**it).GetPolyLm().Degree();
        degreeInfos[degree].JTree.Delete(*it);
        VarCountMap& deletedVarCountMap = degreeInfos[degree].VCMap;
        std::set<Monom::Integer> deletedVarSet = (**it).GetPolyLm().GetVariablesSet();
        for (std::set<Monom::Integer>::const_iterator i = deletedVarSet.begin(); i != deletedVarSet.end(); ++i)
        {
        --deletedVarCountMap[*i];
        }
    }

    jTree.Delete(*it);
    return tripleList.erase(it);
}

void TSet::PushBack(Triple* newTriple)
{
    tripleList.push_back(newTriple);
    jTree.Insert(newTriple);

    if (GetSettingsManager().UseNovaInvolution)
    {
        Monom::Integer degree = newTriple->GetPolyLm().Degree();
        degreeInfos[degree].JTree.Insert(newTriple);
        VarCountMap& addedVarCountMap = degreeInfos[degree].VCMap;
        std::set<Monom::Integer> addedVarSet = newTriple->GetPolyLm().GetVariablesSet();
        for (std::set<Monom::Integer>::const_iterator i = addedVarSet.begin(); i != addedVarSet.end(); ++i)
        {
        ++addedVarCountMap[*i];
        }
    }
}

void TSet::CollectNonMultiProlongations(TSet::iterator& iterator, std::list<Triple*>& set)
{
    if (iterator == tripleList.end() || !(*iterator))
    {
        return;
    }

    if (GetSettingsManager().UseNovaInvolution)
    {
        std::set<Monom::Integer> nonMultiVars = NonMultiNova(*iterator);
        std::set<Monom::Integer>::const_iterator nmvIterator = nonMultiVars.begin();
        for (; nmvIterator != nonMultiVars.end(); ++nmvIterator)
        {
            if (!(**iterator).TestNmp(*nmvIterator))
            {
                Polynom* tmpPolynom = new Polynom(*(**iterator).GetPoly());
                (*tmpPolynom) *= *nmvIterator;

                (**iterator).SetNmp(*nmvIterator);

                if (!tmpPolynom->IsZero())
                {
                    set.push_back(new Triple(tmpPolynom
                                           , (**iterator).GetAnc()
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
        Monom::Integer firstMultiVar = (**iterator).GetPolyLm().FirstMultiVar();
        for (register Monom::Integer var = 0; var < firstMultiVar; ++var)
        {
            if (!(**iterator).TestNmp(var))
        {
                Polynom* tmpPolynom = new Polynom(*(**iterator).GetPoly());
                (*tmpPolynom) *= var;

                (**iterator).SetNmp(var);

                if (!tmpPolynom->IsZero())
                {
                    set.push_back(new Triple(tmpPolynom
                                           , (**iterator).GetAnc()
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

std::set<Monom::Integer> TSet::NonMultiNova(const Triple* triple)
{
    Monom::Integer degree = triple->GetPolyLm().Degree();
    std::set<Monom::Integer> nmulti = degreeInfos[degree].JTree.NonMulti(triple);

    for (Monom::Integer var = 0; var < Monom::DimIndepend(); ++var)
    {
        if (nmulti.find(var) != nmulti.end())
        {
            continue;
        }

        Monom::Integer i = degree;
        for (Monom::Integer i = degree; i > 0; --i)
        {
            if (degreeInfos[i-1].VCMap[var])
                break;
        }

        if (!i)
        {
            nmulti.insert(var);
        }
    }

    return nmulti;
}
