#include <iostream>

#include "groebner_basis.h"
#include "pcomparator.h"
#include "resource_counter.h"
#include "settings_manager.h"

Polynom* GroebnerBasis::NormalForm(const Triple* triple)
{
    Polynom *h, *q;
    const Triple* involutiveDivisor;
    q = new Polynom();

    if (triple->GetVar() == -1)
    {
        h = new Polynom(*triple->GetPoly());
    }
    else
    {
        h = new Polynom(*triple->GetWAnc()->GetPoly());
        (*h) *= triple->GetVar();
    }

    while (!h->IsZero())
    {
        involutiveDivisor = IntermediateBasis.Find(h->Lm());
        while (involutiveDivisor)
        {
            h->HeadReduction(*involutiveDivisor->GetPoly());
            if (!h->IsZero())
            {
                involutiveDivisor = IntermediateBasis.Find(h->Lm());
            }
            else
            {
                involutiveDivisor = 0;
            }
        }

        if (!h->IsZero())
        {
            (*q) += h->Lm();
            h->RidOfLm();
        }
    }

    delete h;
    return q;
}

const Polynom* GroebnerBasis::FindR(const Polynom* polynom, const std::list<Polynom*>& set)
{
    if (polynom->IsZero())
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
    Polynom* result = new Polynom();
    const Polynom* currentReducer;

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
        Polynom* h = GBasis.front();
        GBasis.pop_front();
        h = Reduce(h, tmpPolySet);

        if (!h->IsZero())
        {
            const Monom& hLm = h->Lm();
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
            tmpPolySet.push_back(h);
        }
    }

    unsigned tmpPolySetSize = tmpPolySet.size();
    for (register unsigned i = 0; i < tmpPolySetSize; ++i)
    {
        Polynom* h = tmpPolySet.front();
        tmpPolySet.pop_front();
        h = Reduce(h, tmpPolySet);
        if (h->IsZero())
        {
            tmpPolySetSize--;
        }
        else
        {
            tmpPolySet.push_back(h);
        }
    }

    GBasis = tmpPolySet;
}

void GroebnerBasis::ConstructInvolutiveBasis()
{
    TSet::Iterator tit(IntermediateBasis.Begin());
    Polynom* newNormalForm;
    Triple* currentTriple;

    while (!ProlongationsSet.Empty())
    {
        currentTriple = ProlongationsSet.Get();
        newNormalForm = NormalForm(currentTriple);

        std::set<Monom::Integer> n;
        const Triple* qanc(0);
        if (!newNormalForm->IsZero() && newNormalForm->Lm() == currentTriple->GetPolyLm())
        {
            n = currentTriple->GetNmp();
            qanc = currentTriple->GetAnc();
            if (qanc == currentTriple)
            {
                qanc = 0;
            }
        }
        delete currentTriple;

        if (!newNormalForm->IsZero())
        {
            if (GetSettingsManager().GetCollectStatistics())
            {
                ++GetResourceCounter().NonZeroReductions;
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

            IntermediateBasis.PushBack(new Triple(newNormalForm, qanc, n, 0, -1));
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

            if (GetSettingsManager().GetCollectStatistics())
            {
                GetResourceCounter().NonMultiProlongations += newProlongations.size();
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
            for (register Monom::Integer var = 0; var < Monom::GetDimIndepend(); ++var)
            {
                GBasis.push_back(new Polynom(**i1));
                (*GBasis.back()) *= var;
            }
        }
    }

    ReduceSet();

    ProlongationsSet.Insert(GBasis);
    GBasis.clear();

    if (GetSettingsManager().GetCollectStatistics())
    {
        GetResourceCounter().NonMultiProlongations += ProlongationsSet.Size();
    }

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
