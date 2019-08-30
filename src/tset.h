#pragma once

#include "janettree.h"
#include "polynom.h"
#include "settings_manager.h"
#include "triple.h"

#include <algorithm>
#include <list>
#include <map>


template <typename MonomType>
class TSet
{
public:
    using PolynomType = Polynom<MonomType>;
    using TripleType = Triple<MonomType>;
    using Integer = typename MonomType::Integer;

    using Iterator = typename std::list<TripleType*>::iterator;
    using ConstIterator = typename std::list<TripleType*>::const_iterator;

public:
    TSet() = default;

    ~TSet()
    {
        clear();
    }

    Iterator begin()
    {
        return tripleList_.begin();
    }

    ConstIterator begin() const
    {
        return tripleList_.begin();
    }

    Iterator end()
    {
        return tripleList_.end();
    }

    ConstIterator end() const
    {
        return tripleList_.end();
    }

    void clear()
    {
        jTree_.clear();
        if (settingsManager().useNovaInvolution())
        {
            degreeInfo_.clear();
        }

        for (auto* triple : tripleList_)
        {
            delete triple;
        }
        tripleList_.clear();
    }

    Iterator erase(Iterator it)
    {
        if (settingsManager().useNovaInvolution())
        {
            Integer degree = (**it).polynomLm().degree();
            degreeInfo_[degree].jTree.erase(*it);

            auto& deletedVarCountMap = degreeInfo_[degree].vcMap;
            auto deletedVarSet = (**it).polynomLm().variablesSet();
            for (const auto& var : deletedVarSet)
            {
                --deletedVarCountMap[var];
            }
        }

        jTree_.erase(*it);
        return tripleList_.erase(it);
    }

    void pushBack(TripleType* newTriple)
    {
        tripleList_.push_back(newTriple);
        jTree_.insert(newTriple);

        if (settingsManager().useNovaInvolution())
        {
            Integer degree = newTriple->polynomLm().degree();
            degreeInfo_[degree].jTree.insert(newTriple);
            auto& addedVarCountMap = degreeInfo_[degree].vcMap;
            auto addedVarSet = newTriple->polynomLm().variablesSet();
            for (const auto& var : addedVarSet)
            {
                ++addedVarCountMap[var];
            }
        }
    }

    std::size_t size() const
    {
        return tripleList_.size();
    }

    const TripleType* find(const MonomType& monom) const
    {
        return jTree_.find(monom);
    }

    const TripleType* back() const
    {
        return tripleList_.back();
    }

    void collectNonMultiProlongations(Iterator& iterator, std::list<TripleType*>& set)
    {
        if (iterator == tripleList_.end() || !(*iterator))
        {
            return;
        }

        if (settingsManager().useNovaInvolution())
        {
            for (const auto& var : nonMultiNova(*iterator))
            {
                if (!(**iterator).testNmp(var))
                {
                    PolynomType* tmpPolynom = new PolynomType(*(**iterator).polynom());
                    (*tmpPolynom) *= var;

                    (**iterator).setNmp(var);

                    if (!tmpPolynom->isZero())
                    {
                        set.push_back(new TripleType(tmpPolynom,
                                                     (**iterator).ancestor(),
                                                     (**iterator).nmp(),
                                                     (*iterator),
                                                     var));
                    }
                    delete tmpPolynom;
                }
            }
        }
        else
        {
            Integer firstMultiVar = (**iterator).polynomLm().firstMultiVar();
            for (typename MonomType::Integer var = 0; var < firstMultiVar; ++var)
            {
                if (!(**iterator).testNmp(var))
                {
                    PolynomType* tmpPolynom = new PolynomType(*(**iterator).polynom());
                    (*tmpPolynom) *= var;

                    (**iterator).setNmp(var);

                    if (!tmpPolynom->isZero())
                    {
                        set.push_back(new TripleType(tmpPolynom,
                                                     (**iterator).ancestor(),
                                                     (**iterator).nmp(),
                                                     (*iterator),
                                                     var));
                    }
                    delete tmpPolynom;
                }
            }
        }
    }

    std::set<Integer> nonMultiNova(const TripleType* triple)
    {
        Integer degree = triple->polynomLm().degree();
        std::set<Integer> nmulti = degreeInfo_[degree].jTree.nonMulti(triple);

        for (Integer var = 0; var < MonomType::dimIndepend(); ++var)
        {
            if (nmulti.find(var) != nmulti.end())
            {
                continue;
            }

            Integer i = degree;
            for (; i > 0; --i)
            {
                if (degreeInfo_[i - 1].vcMap[var])
                {
                    break;
                }
            }

            if (!i)
            {
                nmulti.insert(var);
            }
        }

        return nmulti;
    }

private:
    std::list<TripleType*> tripleList_;
    JanetTree<MonomType> jTree_;

    struct FullDegreeInfo
    {
        JanetTree<MonomType> jTree;
        std::map<Integer, unsigned> vcMap;
    };

    std::map<Integer, FullDegreeInfo> degreeInfo_;
};
