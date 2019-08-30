#pragma once

#include "pcomparator.h"
#include "resource_counter.h"
#include "qset.h"
#include "tset.h"

#include <algorithm>
#include <list>


template <typename MonomType>
class GroebnerBasis
{
public:
    using PolynomType = Polynom<MonomType>;
    using TripleType = Triple<MonomType>;
    using Integer = typename MonomType::Integer;

public:
    ~GroebnerBasis()
    {
        reset();
    }

    void construct(const std::list<PolynomType*>& set)
    {
        reset();
        gBasis_ = set;

        if (settingsManager().useNovaInvolution())
        {
            for (const auto* item : set)
            {
                if (!item)
                {
                    continue;
                }
                for (Integer var = 0; var < MonomType::dimIndepend(); ++var)
                {
                    gBasis_.push_back(new PolynomType(*item));
                    (*gBasis_.back()) *= var;
                }
            }
        }

        resourceCounter().autoReductionTimer.start();
        reduceSet();
        resourceCounter().autoReductionTimer.stop();

        prolongationsSet_.insert(gBasis_);
        gBasis_.clear();

        constructInvolutiveBasis();
        prolongationsSet_.clear();

        for (auto it = intermediateBasis_.begin(); it != intermediateBasis_.end(); ++it)
        {
            gBasis_.push_back((**it).polynom());
        }

        reduceSet(true);
    }

    const PolynomType& operator[](int number) const
    {
        auto it = gBasis_.begin();
        std::advance(it, length() - 1 - number);
        return **it;
    }

    unsigned length() const
    {
        return gBasis_.size();
    }

private:
    PolynomType* normalForm(const TripleType* triple) const
    {
        if (!triple)
        {
            return 0;
        }

        const TripleType* involutiveDivisor = nullptr;
        PolynomType* originalForm = nullptr;
        PolynomType* normalForm = new PolynomType();

        if (triple->variable() == -1)
        {
            originalForm = new PolynomType(*triple->polynom());
        }
        else
        {
            originalForm = new PolynomType(*triple->weakAncestor()->polynom());
            (*originalForm) *= triple->variable();
        }

        if (settingsManager().collectStatistics())
        {
            ++resourceCounter().nonMultiProlongations;
            resourceCounter().nonMultiProlongationsLength += originalForm->length();
        }

        while (!originalForm->isZero())
        {
            involutiveDivisor = intermediateBasis_.find(originalForm->lm());
            while (involutiveDivisor)
            {
                originalForm->headReduction(*involutiveDivisor->polynom());
                if (!originalForm->isZero())
                {
                    involutiveDivisor = intermediateBasis_.find(originalForm->lm());
                }
                else
                {
                    involutiveDivisor = nullptr;
                }
            }

            if (!originalForm->isZero())
            {
                (*normalForm) += originalForm->lm();
                originalForm->ridOfLm();
            }
        }

        delete originalForm;
        return normalForm;
    }

    const PolynomType* findDivisor(const PolynomType* polynom,
                                   const std::list<PolynomType*>& set,
                                   bool toGroebner) const
    {
        if (!polynom || polynom->isZero())
        {
            return nullptr;
        }

        const MonomType& polynomLm = polynom->lm();
        for (const auto* item : set)
        {
            if ((toGroebner && polynomLm.isDivisibleBy(item->lm())) ||
                (!toGroebner && polynomLm.isPommaretDivisibleBy(item->lm())))
            {
                return item;
            }
        }

        return nullptr;
    }

    PolynomType* reduce(PolynomType* polynom,
                        const std::list<PolynomType*>& set,
                        bool toGroebner) const
    {
        if (!polynom)
        {
            return nullptr;
        }

        PolynomType* result = new PolynomType();
        const PolynomType* currentReducer = nullptr;

        while (!polynom->isZero())
        {
            currentReducer = findDivisor(polynom, set, toGroebner);
            while (currentReducer)
            {
                polynom->reduction(*currentReducer);
                currentReducer = findDivisor(polynom, set, toGroebner);
            }
            if (!polynom->isZero())
            {
                (*result) += polynom->lm();
                polynom->ridOfLm();
            }
        }

        polynom = result;
        return result;
    }

    void reduceSet(bool toGroebner = true)
    {
        std::list<PolynomType*> tmpPolySet;
        gBasis_.sort(PointerGreaterComparator<PolynomType>());

        while (!gBasis_.empty())
        {
            PolynomType* currentPolynom = gBasis_.front();
            gBasis_.pop_front();
            currentPolynom = reduce(currentPolynom, tmpPolySet, toGroebner);

            if (currentPolynom && !currentPolynom->isZero())
            {
                const MonomType& hLm = currentPolynom->lm();
                for (auto it = tmpPolySet.begin(); it != tmpPolySet.end();)
                {
                    if ((**it).lm().isDivisibleBy(hLm))
                    {
                        gBasis_.push_back(*it);
                        it = tmpPolySet.erase(it);
                    }
                    else
                    {
                        ++it;
                    }
                }
                tmpPolySet.push_back(currentPolynom);
            }
        }

        unsigned tmpPolySetSize = tmpPolySet.size();
        for (unsigned i = 0; i < tmpPolySetSize; ++i)
        {
            PolynomType* currentPolynom = tmpPolySet.front();
            tmpPolySet.pop_front();

            currentPolynom = reduce(currentPolynom, tmpPolySet, toGroebner);

            if (!currentPolynom || currentPolynom->isZero())
            {
                tmpPolySetSize--;
            }
            else
            {
                tmpPolySet.push_back(currentPolynom);
            }
        }

        gBasis_ = tmpPolySet;
    }

    void constructInvolutiveBasis()
    {
        while (!prolongationsSet_.empty())
        {
            auto* currentTriple = prolongationsSet_.get();
            auto* newNormalForm = normalForm(currentTriple);

            std::set<Integer> currentNmpSet;
            const TripleType* currentAncestor = nullptr;

            if (newNormalForm && !newNormalForm->isZero() && newNormalForm->lm() == currentTriple->polynomLm())
            {
                currentNmpSet = currentTriple->nmp();
                if (currentTriple->ancestor() != currentTriple)
                {
                    currentAncestor = currentTriple->ancestor();
                }
            }
            delete currentTriple;

            if (!newNormalForm || newNormalForm->isZero())
            {
                delete newNormalForm;
                continue;
            }

            if (settingsManager().collectStatistics())
            {
                ++resourceCounter().nonZeroReductions;
                resourceCounter().nonZeroReductionsLength += newNormalForm->length();
            }

            std::list<TripleType*> newProlongations;
            for (auto tit = intermediateBasis_.begin();tit != intermediateBasis_.end();)
            {
                if ((**tit).polynomLm().isTrueDivisibleBy(newNormalForm->lm()))
                {
                    if (settingsManager().useNovaInvolution())
                    {
                        (**tit).setNmp(std::set<Monom::Integer>());
                    }
                    prolongationsSet_.deleteDescendants(*tit);
                    newProlongations.push_back(*tit);
                    tit = intermediateBasis_.erase(tit);
                }
                else
                {
                    ++tit;
                }
            }

            intermediateBasis_.pushBack(new TripleType(newNormalForm, currentAncestor, currentNmpSet, 0, -1));
            if (!newNormalForm->degree())
            {
                return;
            }

            if (settingsManager().useNovaInvolution())
            {
                for (auto tit = intermediateBasis_.begin(); tit != intermediateBasis_.end(); ++tit)
                {
                    intermediateBasis_.collectNonMultiProlongations(tit, newProlongations);
                }
            }
            else
            {
                intermediateBasis_.collectNonMultiProlongations(--intermediateBasis_.end(), newProlongations);
            }

            prolongationsSet_.insert(newProlongations);
        }
    }

    void reset()
    {
        intermediateBasis_.clear();
        prolongationsSet_.clear();
        gBasis_.clear();
        resourceCounter().nonMultiProlongations = 0;
        resourceCounter().nonZeroReductions = 0;
    }

private:
    std::list<PolynomType*> gBasis_;
    TSet<MonomType> intermediateBasis_;
    QSet<MonomType> prolongationsSet_;
};


template <typename MonomType>
std::ostream& operator<<(std::ostream& out, const GroebnerBasis<MonomType>& groebnerBasis)
{
    for (unsigned i = 0; i < groebnerBasis.length(); ++i)
    {
        out << '[' << i << "] = " << groebnerBasis[i] << '\n';
    }

    return out;
}
