#ifndef GROEBNER_BASIS_H
#define GROEBNER_BASIS_H

#include <list>
#include <algorithm>
#include "pcomparator.h"
#include "resource_counter.h"
#include "qset.h"
#include "tset.h"

template <typename MonomType>
class GroebnerBasis
{
private:
    std::list<Polynom<MonomType>*> GBasis;
    TSet<MonomType> IntermediateBasis;
    QSet<MonomType> ProlongationsSet;

public:
    GroebnerBasis();
    ~GroebnerBasis();

    void Construct(const std::list<Polynom<MonomType>*>& set);

    const Polynom<MonomType>& operator[](int number) const;
    unsigned Length() const;

    template <typename SomeMonomType>
    friend std::ostream& operator<<(std::ostream& out, const GroebnerBasis& groebnerBasis);

private:
    Polynom<MonomType>* NormalForm(const Triple<MonomType>* triple) const;
    const Polynom<MonomType>* FindDivisor(const Polynom<MonomType>* polynom
                                        , const std::list<Polynom<MonomType>*>& set
                                        , bool toGroebner) const;
    Polynom<MonomType>* Reduce(Polynom<MonomType>* polynom
                             , const std::list<Polynom<MonomType>*>& set
                             , bool toGroebner) const;
    void ReduceSet(bool toGroebner = true);
    void ConstructInvolutiveBasis();
    void Reset();
};

template <typename MonomType>
GroebnerBasis<MonomType>::GroebnerBasis()
    : GBasis()
    , IntermediateBasis()
    , ProlongationsSet()
{
}

template <typename MonomType>
GroebnerBasis<MonomType>::~GroebnerBasis()
{
    Reset();
}

template <typename MonomType>
void GroebnerBasis<MonomType>::Construct(const std::list<Polynom<MonomType>*>& set)
{
    Reset();
    GBasis = set;

    if (GetSettingsManager().GetUseNovaInvolution())
    {
        typename std::list<Polynom<MonomType>*>::const_iterator i1 = set.begin();
        for (; i1 != set.end(); ++i1)
        {
            if (!*i1)
            {
                continue;
            }

            for (register typename MonomType::Integer var = 0; var < MonomType::GetDimIndepend(); ++var)
            {
                GBasis.push_back(new Polynom<MonomType>(**i1));
                (*GBasis.back()) *= var;
            }
        }
    }

    GetResourceCounter().AutoReductionTimer.Start();
    ReduceSet();
    GetResourceCounter().AutoReductionTimer.Stop();

    ProlongationsSet.Insert(GBasis);
    GBasis.clear();

    ConstructInvolutiveBasis();
    ProlongationsSet.Clear();

    typename TSet<MonomType>::ConstIterator i2(IntermediateBasis.Begin());
    while (i2 != IntermediateBasis.End())
    {
        GBasis.push_back(const_cast<Polynom<MonomType>*>((**i2).GetPolynom()));
        ++i2;
    }
    ReduceSet(true);
}

template <typename MonomType>
const Polynom<MonomType>& GroebnerBasis<MonomType>::operator[](int num) const
{
    typename std::list<Polynom<MonomType>*>::const_iterator it(GBasis.begin());
    for (register unsigned i = Length()-1-num; i > 0; i--)
    {
        ++it;
    }
    return **it;
}

template <typename MonomType>
unsigned GroebnerBasis<MonomType>::Length() const
{
    return GBasis.size();
}

template <typename MonomType>
Polynom<MonomType>* GroebnerBasis<MonomType>::NormalForm(const Triple<MonomType>* triple) const
{
    if (!triple)
    {
        return 0;
    }

    const Triple<MonomType>* involutiveDivisor = 0;
    Polynom<MonomType>* originalForm = 0;
    Polynom<MonomType>* normalForm = new Polynom<MonomType>();

    if (triple->GetVariable() == -1)
    {
        originalForm = new Polynom<MonomType>(*triple->GetPolynom());
    }
    else
    {
        originalForm = new Polynom<MonomType>(*triple->GetWeakAncestor()->GetPolynom());
        (*originalForm) *= triple->GetVariable();
    }

    if (GetSettingsManager().GetCollectStatistics())
    {
        ++GetResourceCounter().NonMultiProlongations;
        GetResourceCounter().NonMultiProlongationsLength += originalForm->Length();
    }

    while (!originalForm->IsZero())
    {
        involutiveDivisor = IntermediateBasis.Find(originalForm->Lm());
        while (involutiveDivisor)
        {
            originalForm->HeadReduction(*involutiveDivisor->GetPolynom());
            if (!originalForm->IsZero())
            {
                involutiveDivisor = IntermediateBasis.Find(originalForm->Lm());
            }
            else
            {
                involutiveDivisor = 0;
            }
        }

        if (!originalForm->IsZero())
        {
            (*normalForm) += originalForm->Lm();
            originalForm->RidOfLm();
        }
    }

    delete originalForm;
    return normalForm;
}

template <typename MonomType>
const Polynom<MonomType>* GroebnerBasis<MonomType>::FindDivisor(const Polynom<MonomType>* polynom
                                                              , const std::list<Polynom<MonomType>*>& set
                                                              , bool toGroebner) const
{
    if (!polynom || polynom->IsZero())
    {
        return 0;
    }

    typename std::list<Polynom<MonomType>*>::const_iterator it(set.begin()), setEnd(set.end());
    const MonomType& plm = polynom->Lm();

    while (it != setEnd)
    {
        if (toGroebner && plm.IsDivisibleBy((**it).Lm()))
        {
            return *it;
        }
        else if (!toGroebner && plm.IsPommaretDivisibleBy((**it).Lm()))
        {
            return *it;
        }
        ++it;
    }

    return 0;
}

template <typename MonomType>
Polynom<MonomType>* GroebnerBasis<MonomType>::Reduce(Polynom<MonomType>* polynom
                                                   , const std::list<Polynom<MonomType>*>& set
                                                   , bool toGroebner) const
{
    if (!polynom)
    {
        return 0;
    }

    Polynom<MonomType>* result = new Polynom<MonomType>();
    const Polynom<MonomType>* currentReducer = 0;

    while (!polynom->IsZero())
    {
        currentReducer = FindDivisor(polynom, set, toGroebner);
        while (currentReducer)
        {
            polynom->Reduction(*currentReducer);
            currentReducer = FindDivisor(polynom, set, toGroebner);
        }
        if (!polynom->IsZero())
        {
            (*result) += polynom->Lm();
            polynom->RidOfLm();
        }
    }

    polynom = result;
    return result;
}

template <typename MonomType>
void GroebnerBasis<MonomType>::ReduceSet(bool toGroebner)
{
    std::list<Polynom<MonomType>*> tmpPolySet;
    GBasis.sort(PointerMoreComparator<Polynom<MonomType> >());

    while (!GBasis.empty())
    {
        Polynom<MonomType>* currentPolynom = GBasis.front();
        GBasis.pop_front();
        currentPolynom = Reduce(currentPolynom, tmpPolySet, toGroebner);

        if (currentPolynom && !currentPolynom->IsZero())
        {
            const MonomType& hLm = currentPolynom->Lm();
            typename std::list<Polynom<MonomType>*>::iterator iteratorTmpPolySet = tmpPolySet.begin();
            while (iteratorTmpPolySet != tmpPolySet.end())
            {
                if ((**iteratorTmpPolySet).Lm().IsDivisibleBy(hLm))
                {
                    GBasis.push_back(*iteratorTmpPolySet);
                    iteratorTmpPolySet = tmpPolySet.erase(iteratorTmpPolySet);
                }
                else
                {
                    ++iteratorTmpPolySet;
                }
            }
            tmpPolySet.push_back(currentPolynom);
        }
    }

    unsigned tmpPolySetSize = tmpPolySet.size();
    for (register unsigned i = 0; i < tmpPolySetSize; ++i)
    {
        Polynom<MonomType>* currentPolynom = tmpPolySet.front();
        tmpPolySet.pop_front();
        currentPolynom = Reduce(currentPolynom, tmpPolySet, toGroebner);
        if (!currentPolynom || currentPolynom->IsZero())
        {
            tmpPolySetSize--;
        }
        else
        {
            tmpPolySet.push_back(currentPolynom);
        }
    }

    GBasis = tmpPolySet;
}

template <typename MonomType>
void GroebnerBasis<MonomType>::ConstructInvolutiveBasis()
{
    typename TSet<MonomType>::Iterator tit(IntermediateBasis.Begin());
    Polynom<MonomType>* newNormalForm = 0;
    Triple<MonomType>* currentTriple = 0;

    while (!ProlongationsSet.Empty())
    {
        currentTriple = ProlongationsSet.Get();
        newNormalForm = NormalForm(currentTriple);

        std::set<typename MonomType::Integer> currentNmpSet;
        const Triple<MonomType>* currentAncestor = 0;
        if (newNormalForm && !newNormalForm->IsZero() && newNormalForm->Lm() == currentTriple->GetPolynomLm())
        {
            currentNmpSet = currentTriple->GetNmp();
            currentAncestor = currentTriple->GetAncestor();
            if (currentAncestor == currentTriple)
            {
                currentAncestor = 0;
            }
        }
        delete currentTriple;

        if (newNormalForm && !newNormalForm->IsZero())
        {
            if (GetSettingsManager().GetCollectStatistics())
            {
                ++GetResourceCounter().NonZeroReductions;
                GetResourceCounter().NonZeroReductionsLength += newNormalForm->Length();
            }

            std::list<Triple<MonomType>*> newProlongations;
            tit = IntermediateBasis.Begin();

            while (tit != IntermediateBasis.End())
            {
                if ((**tit).GetPolynomLm().IsTrueDivisibleBy(newNormalForm->Lm()))
                {
                    if (GetSettingsManager().GetUseNovaInvolution())
                    {
                        (**tit).SetNmp(std::set<Monom::Integer>());
                    }
                    ProlongationsSet.DeleteDescendants(*tit);
                    newProlongations.push_back(*tit);
                    tit = IntermediateBasis.Erase(tit);
                }
                else
                {
                    ++tit;
                }
            }

            IntermediateBasis.PushBack(new Triple<MonomType>(newNormalForm, currentAncestor, currentNmpSet, 0, -1));
            if (!newNormalForm->Degree())
            {
                return;
            }

            if (GetSettingsManager().GetUseNovaInvolution())
            {
                tit = IntermediateBasis.Begin();
                for (; tit != IntermediateBasis.End(); ++tit)
                {
                    IntermediateBasis.CollectNonMultiProlongations(tit, newProlongations);
                }
            }
            else
            {
                IntermediateBasis.CollectNonMultiProlongations(--IntermediateBasis.End(), newProlongations);
            }

            ProlongationsSet.Insert(newProlongations);
        }
        else
        {
            delete newNormalForm;
        }
    }
}

template <typename MonomType>
void GroebnerBasis<MonomType>::Reset()
{
    IntermediateBasis.Clear();
    ProlongationsSet.Clear();
    GBasis.clear();
    GetResourceCounter().NonMultiProlongations = 0;
    GetResourceCounter().NonZeroReductions = 0;
}

template <typename MonomType>
std::ostream& operator<<(std::ostream& out, const GroebnerBasis<MonomType>& groebnerBasis)
{
    for (register unsigned i = 0; i < groebnerBasis.Length(); ++i)
    {
        out << '[' << i << "] = " << groebnerBasis[i] << '\n';
    }

    return out;
}

#endif // GROEBNER_BASIS_H
