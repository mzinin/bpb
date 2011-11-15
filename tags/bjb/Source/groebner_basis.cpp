#include <iostream>
#include <set>
#include "groebner_basis.h"
#include "pcomparator.h"
#include "resource_counter.h"
#include "settings_manager.h"
#include "timer.h"

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

void GroebnerBasis::Construct(const std::list<Polynom*>& set)
{
    Reset();
    GBasis = set;

    for (register Monom::Integer i = 0; i < Monom::GetDimIndepend(); ++i)
    {
        Polynom* binomial = new Polynom();
        binomial->SetOne();
        binomial->Multiply(i, 1);
        (*binomial) += Monom();
        binomial->Multiply(i, 1);
        GBasis.push_back(binomial);
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
        if ((*i2)->GetAncestor() == *i2/* && !(*i2)->GetPolynom()->IsBinomial()*/)
        {
            GBasis.push_back(const_cast<Polynom*>((**i2).GetPolynom()));
        }
        ++i2;
    }
    ReduceSet();
    
    std::list<Polynom*>::iterator gbIterator = GBasis.begin();
    while (gbIterator != GBasis.end())
    {
        if ((**gbIterator).IsBinomial())
        {
            gbIterator = GBasis.erase(gbIterator);
        }
        else
        {
            ++gbIterator;
        }
    }
}

const Polynom& GroebnerBasis::operator[](int num) const
{
    std::list<Polynom*>::const_iterator it(GBasis.begin());
    for (register unsigned i = Length() - 1 - num; i > 0; --i) 
    {
        ++it;
    }
    return **it;
}

unsigned GroebnerBasis::Length() const
{
    return GBasis.size();
}

bool GroebnerBasis::Criterion1(const Triple* p, const Triple* g) const
{
    const Monom& pAncestorLm = p->GetAncestor()->GetPolynomLm();
    const Monom& gAncestorLm = g->GetAncestor()->GetPolynomLm();
    Monom tmpMonom = pAncestorLm;
    tmpMonom.Multiply(gAncestorLm);

    return !Monom::GcdDegree(pAncestorLm, gAncestorLm) && p->GetPolynomLm() == tmpMonom;
}

bool GroebnerBasis::Criterion2(const Triple* p, const Triple* g) const
{
    Monom tmpMonom = p->GetAncestor()->GetPolynomLm();
    tmpMonom.Multiply(g->GetAncestor()->GetPolynomLm());
    
    return p->GetPolynomLm().IsTrueDivisibleBy(tmpMonom);
}

bool GroebnerBasis::Criterion3(const Triple* p, const Triple* g) const
{
    Monom tmpMonom = p->GetAncestor()->GetPolynomLm();
    tmpMonom.Multiply(g->GetAncestor()->GetPolynomLm());
    
    TSet::ConstIterator iterator = IntermediateBasis.Begin();
    for (; iterator != IntermediateBasis.End(); ++iterator)
    {
        Monom monomP = p->GetAncestor()->GetPolynomLm();
        monomP.Multiply((**iterator).GetPolynomLm());
        Monom monomG = g->GetAncestor()->GetPolynomLm();
        monomG.Multiply((**iterator).GetPolynomLm());
        
        if (tmpMonom.IsTrueDivisibleBy(monomP) && tmpMonom.IsTrueDivisibleBy(monomG))
        {
            return true;
        }
    }
    
    return false;
}

bool GroebnerBasis::Criterion4(const Triple* p, const Triple* g) const
{
    TSet::ConstIterator iterator = IntermediateBasis.Begin();
    for (; iterator != IntermediateBasis.End() && p->GetWeakAncestor() != *iterator; ++iterator)
    {
        if ((**iterator).GetPolynom()->Degree() != p->GetPolynom()->Degree() - 1)
        {
            continue;
        }
        
        Monom tmpMonom1 = p->GetAncestor()->GetPolynomLm();
        tmpMonom1.Multiply((**iterator).GetAncestor()->GetPolynomLm());

        std::set<Monom::Integer> nmv = IntermediateBasis.NonMulti(*iterator);
        for (std::set<Monom::Integer>::const_iterator it = nmv.begin(); it != nmv.end(); ++it)
        {
            Monom tmpMonom2 = (**iterator).GetPolynomLm();
            tmpMonom2.Prolong(*it);
            if (tmpMonom2 == p->GetPolynomLm() && tmpMonom2.IsTrueDivisibleBy(tmpMonom1))
            {
                return true;
            }
        }
    }
    return false;
}

Polynom* GroebnerBasis::NormalForm(const Triple* triple) const
{
    if (!triple)
    {
        return 0;
    }

    const Triple* involutiveDivisor = 0;
    if (triple->GetVariable() != -1 && (involutiveDivisor = IntermediateBasis.FindDivisor(triple->GetPolynomLm())))
    {
        if (Criterion1(triple, involutiveDivisor) || 
            Criterion2(triple, involutiveDivisor)/* || 
            Criterion3(triple, involutiveDivisor) || 
            Criterion4(triple, involutiveDivisor)*/)
        {
            return 0;
        }
    }

    Polynom* originalForm = 0;
    if (triple->GetVariable() == -1)
    {
        originalForm = new Polynom(*triple->GetPolynom());
    }
    else
    {
        originalForm = new Polynom(*triple->GetWeakAncestor()->GetPolynom());
        originalForm->Multiply(triple->GetVariable(), 1);
    }
    
    if (GetSettingsManager().GetCollectStatistics())
    {
        ++GetResourceCounter().NonMultiProlongations;
        GetResourceCounter().NonMultiProlongationsLength += originalForm->Length();
    }

    Polynom* normalForm = new Polynom();
    while (!originalForm->IsZero())
    {
        involutiveDivisor = IntermediateBasis.FindDivisor(originalForm->Lm());
        while (involutiveDivisor)
        {
            originalForm->HeadReduction(*involutiveDivisor->GetPolynom());
            if (!originalForm->IsZero())
            {
                involutiveDivisor = IntermediateBasis.FindDivisor(originalForm->Lm());
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

const Polynom* GroebnerBasis::FindDivisor(const Polynom* polynom, const std::list<Polynom*>& set) const
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

Polynom* GroebnerBasis::Reduce(Polynom* polynom, const std::list<Polynom*>& set) const
{
    if (!polynom)
    {
        return 0;
    }

    Polynom* result = new Polynom();
    const Polynom* currentReducer = 0;

    while (!polynom->IsZero())
    {
        currentReducer = FindDivisor(polynom, set);
        while (currentReducer)
        {
            polynom->Reduction(*currentReducer);
            currentReducer = FindDivisor(polynom, set);
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
            --tmpPolySetSize;
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

            std::list<Triple*> newProlongations;
            tit = IntermediateBasis.Begin();
            while (tit != IntermediateBasis.End())
            {
                if ((**tit).GetPolynomLm().IsTrueDivisibleBy(newNormalForm->Lm()))
                {
                    //(**tit).SetNmp(std::set<Monom::Integer>());
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

            tit = IntermediateBasis.Begin();
            for (; tit != IntermediateBasis.End(); ++tit)
            {
                IntermediateBasis.CollectNonMultiProlongations(tit, newProlongations);
            }
            ProlongationsSet.Insert(newProlongations);
        }
        else
        {
            delete newNormalForm;
        }
    }
}

void GroebnerBasis::Reset()
{
    IntermediateBasis.Clear();
    ProlongationsSet.Clear();
    GBasis.clear();
    GetResourceCounter().NonMultiProlongations = 0;
    GetResourceCounter().NonZeroReductions = 0;
}

std::ostream& operator<<(std::ostream& out, const GroebnerBasis& groebnerBasis) 
{
    for (register unsigned i = 0; i < groebnerBasis.Length(); ++i)
    {
        out << '[' << i << "] = " << groebnerBasis[i] << '\n';
    }
  
    return out;
}