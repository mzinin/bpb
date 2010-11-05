#include "tset.h"
#include "settings_manager.h"

TSet::TSet()
    : TripleList()
    , JTree()
    , DegreeInfos()
{
}

TSet::~TSet()
{
    Clear();
}

void TSet::Clear()
{
    JTree.Clear();

    if (GetSettingsManager().UseNovaInvolution)
    {
        DegreeInfos.clear();
    }

    Iterator it(TripleList.begin());
    while (it != TripleList.end())
    {
        delete *it;
        ++it;
    }
    TripleList.clear();
}

TSet::Iterator TSet::Erase(TSet::Iterator it)
{
    if (GetSettingsManager().UseNovaInvolution)
    {
        Monom::Integer degree = (**it).GetPolyLm().Degree();
        DegreeInfos[degree].JTree.Delete(*it);
        VarCountMap& deletedVarCountMap = DegreeInfos[degree].VCMap;
        std::set<Monom::Integer> deletedVarSet = (**it).GetPolyLm().GetVariablesSet();
        for (std::set<Monom::Integer>::const_iterator i = deletedVarSet.begin(); i != deletedVarSet.end(); ++i)
        {
            --deletedVarCountMap[*i];
        }
    }

    JTree.Delete(*it);
    return TripleList.erase(it);
}

void TSet::PushBack(Triple* newTriple)
{
    TripleList.push_back(newTriple);
    JTree.Insert(newTriple);

    if (GetSettingsManager().UseNovaInvolution)
    {
        Monom::Integer degree = newTriple->GetPolyLm().Degree();
        DegreeInfos[degree].JTree.Insert(newTriple);
        VarCountMap& addedVarCountMap = DegreeInfos[degree].VCMap;
        std::set<Monom::Integer> addedVarSet = newTriple->GetPolyLm().GetVariablesSet();
        for (std::set<Monom::Integer>::const_iterator i = addedVarSet.begin(); i != addedVarSet.end(); ++i)
        {
            ++addedVarCountMap[*i];
        }
    }
}

void TSet::CollectNonMultiProlongations(TSet::Iterator& iterator, std::list<Triple*>& set)
{
    if (iterator == TripleList.end() || !(*iterator))
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
    std::set<Monom::Integer> nmulti = DegreeInfos[degree].JTree.NonMulti(triple);

    for (Monom::Integer var = 0; var < Monom::DimIndepend(); ++var)
    {
        if (nmulti.find(var) != nmulti.end())
        {
            continue;
        }

        Monom::Integer i = degree;
        for (Monom::Integer i = degree; i > 0; --i)
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
