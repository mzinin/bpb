#include <iostream>

#include "groebner_basis.h"
#include "pcomparator.h"
#include "resource_counter.h"
#include "settings_manager.h"

Polynom* GroebnerBasis::NormalForm(const Triple* triple)
{
    if (!triple)
    {
        return 0;
    }

    const Triple* involutiveDivisor = 0;
    Polynom* originalForm = 0;
    Polynom* normalForm = new Polynom();

    if (triple->GetVar() == -1)
    {
        originalForm = new Polynom(*triple->GetPoly());
    }
    else
    {
        originalForm = new Polynom(*triple->GetWAnc()->GetPoly());
        (*originalForm) *= triple->GetVar();
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
            originalForm->HeadReduction(*involutiveDivisor->GetPoly());
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

const Polynom* GroebnerBasis::FindR(const Polynom* polynom, const std::list<Polynom*>& set)
{
    if (!polynom || polynom->IsZero())
    {
        return 0;
    }

    std::list<Polynom*>::const_iterator it(set.begin()), setEnd(set.end());
    const Monom& plm = polynom->Lm();

    while (it != setEnd)
    {
        if (plm.IsDivisibleBy((**it).Lm()))
        {
            return *it;
        }
        ++it;
    }

    return 0;
}

Polynom* GroebnerBasis::Reduce(Polynom* polynom, const std::list<Polynom*>& set)
{
    if (!polynom)
    {
        return 0;
    }

    Polynom* result = new Polynom();
    const Polynom* currentReducer = 0;

    while (!polynom->IsZero())
    {
        currentReducer = FindR(polynom, set);
        while (currentReducer)
        {
            polynom->Reduction(*currentReducer);
            currentReducer = FindR(polynom, set);
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

void GroebnerBasis::ReduceSet()
{
    std::list<Polynom*> tmpPolySet;
    GBasis.sort(PointerMoreComparator<Polynom>());

    while (!GBasis.empty())
    {
        Polynom* currentPolynom = GBasis.front();
        GBasis.pop_front();
        currentPolynom = Reduce(currentPolynom, tmpPolySet);

        if (currentPolynom && !currentPolynom->IsZero())
        {
            const Monom& hLm = currentPolynom->Lm();
            std::list<Polynom*>::iterator iteratorTmpPolySet = tmpPolySet.begin();
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
        Polynom* currentPolynom = tmpPolySet.front();
        tmpPolySet.pop_front();
        currentPolynom = Reduce(currentPolynom, tmpPolySet);
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

void GroebnerBasis::ConstructInvolutiveBasis()
{
    TSet::Iterator tit(IntermediateBasis.Begin());
    Polynom* newNormalForm = 0;
    Triple* currentTriple = 0;

    while (!ProlongationsSet.Empty())
    {
        currentTriple = ProlongationsSet.Get();
        newNormalForm = NormalForm(currentTriple);

        std::set<Monom::Integer> currentNmpSet;
        const Triple* currentAncestor = 0;
        if (newNormalForm && !newNormalForm->IsZero() && newNormalForm->Lm() == currentTriple->GetPolyLm())
        {
            currentNmpSet = currentTriple->GetNmp();
            currentAncestor = currentTriple->GetAnc();
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

            std::list<Triple*> newProlongations;
            tit = IntermediateBasis.Begin();

            while (tit != IntermediateBasis.End())
            {
                if ((**tit).GetPolyLm().IsTrueDivisibleBy(newNormalForm->Lm()))
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

            IntermediateBasis.PushBack(new Triple(newNormalForm, currentAncestor, currentNmpSet, 0, -1));
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

GroebnerBasis::GroebnerBasis()
    : GBasis()
    , IntermediateBasis()
    , ProlongationsSet()
{
}

GroebnerBasis::~GroebnerBasis()
{
    Reset();
}

void GroebnerBasis::Reset()
{
    IntermediateBasis.Clear();
    ProlongationsSet.Clear();
    GBasis.clear();
    GetResourceCounter().NonMultiProlongations = 0;
    GetResourceCounter().NonZeroReductions = 0;
}

void GroebnerBasis::Construct(const std::list<Polynom*>& set)
{
    Reset();
    GBasis = set;

    if (GetSettingsManager().GetUseNovaInvolution())
    {
        std::list<Polynom*>::const_iterator i1 = set.begin();
        for (; i1 != set.end(); ++i1)
        {
            if (!*i1)
            {
                continue;
            }

            for (register Monom::Integer var = 0; var < Monom::GetDimIndepend(); ++var)
            {
                GBasis.push_back(new Polynom(**i1));
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

    TSet::ConstIterator i2(IntermediateBasis.Begin());
    while (i2 != IntermediateBasis.End())
    {
        GBasis.push_back(const_cast<Polynom*>((**i2).GetPoly()));
        ++i2;
    }
    ReduceSet();
}

const Polynom& GroebnerBasis::operator[](int num) const
{
    std::list<Polynom*>::const_iterator it(GBasis.begin());
    for (register unsigned i = Length()-1-num; i > 0; i--)
    {
        ++it;
    }
    return **it;
}

unsigned GroebnerBasis::Length() const
{
    return GBasis.size();
}

std::ostream& operator<<(std::ostream& out, const GroebnerBasis& groebnerBasis)
{
    for (register unsigned i = 0; i < groebnerBasis.Length(); ++i)
    {
        out << '[' << i << "] = " << groebnerBasis[i] << '\n';
    }

    return out;
}
