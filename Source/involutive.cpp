#include <iostream>
#include "involutive.h"
#include "timer.h"
#include "pcomparator.h"

Polynom* GBasis::NormalForm(const Triple* p)
{
    Polynom *h, *q;
    const Triple  *involutiveDivisor;
    q = new Polynom();

    if (p->GetVar() == -1)
    {
        h = new Polynom(*p->GetPoly());
    }
    else
    {
        h = new Polynom(*p->GetWAnc()->GetPoly());
        (*h) *= p->GetVar();
    }

    while (!h->IsZero())
    {
        involutiveDivisor = tSet.Find(h->Lm());
        while (involutiveDivisor)
        {
            h->HeadReduction(*involutiveDivisor->GetPoly());
            if (!h->IsZero())
            {
                involutiveDivisor = tSet.Find(h->Lm());
            }
            else
            {
                involutiveDivisor = NULL;
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

const Polynom* GBasis::FindR(const Polynom* p, const std::list<Polynom*>& Q)
{
    if (p->IsZero())
    {
        return NULL;
    }

    std::list<Polynom*>::const_iterator iq(Q.begin()), qEnd(Q.end());
    const Monom& plm = p->Lm();

    while (iq != qEnd)
    {
        if (plm.IsDivisibleBy((**iq).Lm()) )
        {
            return *iq;
        }
        iq++;
    }

    return NULL;
}

Polynom* GBasis::Reduce(Polynom* p, const std::list<Polynom*>& Q)
{
    Polynom* result;
    const Polynom* currentReducer;
    result = new Polynom();

    while (!p->IsZero())
    {
        currentReducer = FindR(p, Q);
        while (currentReducer)
        {
            p->Reduction(*currentReducer);
            currentReducer = FindR(p, Q);
        }
        if (!p->IsZero())
        {
            (*result) += p->Lm();
            p->RidOfLm();
        }
    }

    delete p;
    p = result;
    return result;
}

void GBasis::ReduceSet()
{
    std::list<Polynom*> tmpPolySet;
    gBasis.sort(PointerMoreComparator<Polynom>());

    while (!gBasis.empty())
    {
        Polynom* h = gBasis.front();
        gBasis.pop_front();
        h = Reduce(h, tmpPolySet);

        if (!h->IsZero())
        {
            const Monom& hLm = h->Lm();
            std::list<Polynom*>::iterator iteratorTmpPolySet = tmpPolySet.begin();
            while (iteratorTmpPolySet != tmpPolySet.end())
            {
                if ((**iteratorTmpPolySet).Lm().IsDivisibleBy(hLm))
                {
                    gBasis.push_back(*iteratorTmpPolySet);
                    iteratorTmpPolySet = tmpPolySet.erase(iteratorTmpPolySet);
                }
                else
                {
                    iteratorTmpPolySet++;
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

    gBasis = tmpPolySet;
}

void GBasis::InvolutiveBasis()
{
    TSET::iterator tit(tSet.Begin());
    Polynom* newNormalForm;
    Triple* currentTriple;

    while (!qSet.Empty())
    {
        currentTriple = qSet.Get();
        newNormalForm = NormalForm(currentTriple);

        std::set<Monom::Integer> n;
        const Triple* qanc = NULL;
        if (!newNormalForm->IsZero() && newNormalForm->Lm() == currentTriple->GetPolyLm())
        {
            n = currentTriple->GetNmp();
            qanc = currentTriple->GetAnc();
            if (qanc == currentTriple)
            {
                qanc = NULL;
            }
        }
        delete currentTriple;

        if (!newNormalForm->IsZero())
        {
            std::list<Triple*> additionalToQSet;
            tit = tSet.Begin();

            while (tit != tSet.End())
            {
                if ((**tit).GetPolyLm().IsTrueDivisibleBy(newNormalForm->Lm()))
                {
#ifdef USE_NOVA_INVOLUTION
                    (**tit).SetNmp(std::set<Monom::Integer>());
#endif // USE_NOVA_INVOLUTION
                    qSet.DeleteDescendants(*tit);
                    additionalToQSet.push_back(*tit);
                    tit = tSet.Erase(tit);
                }
                else
                {
                    ++tit;
                }
            }

            tSet.PushBack(new Triple(newNormalForm, qanc, n, 0, -1));
            if (!newNormalForm->Degree()) return;

#ifdef USE_NOVA_INVOLUTION
            tit = tSet.Begin();
            for (; tit != tSet.End(); ++tit)
            {
                std::set<Monom::Integer> nonMultiVars = tSet.NonMultiNova(*tit);
                qSet.Update(*tit, nonMultiVars, additionalToQSet);
            }
#else
            qSet.Update(tSet.Back(), additionalToQSet);
#endif // USE_NOVA_INVOLUTION
            qSet.Insert(additionalToQSet);
        }
        else
        {
            delete newNormalForm;
        }
    }
}

GBasis::GBasis(): gBasis(), qSet(), tSet()
{
}

GBasis::GBasis(const std::list<Polynom*>& set): gBasis(set), qSet(), tSet()
{
#ifdef USE_NOVA_INVOLUTION
    std::list<Polynom*>::const_iterator i1 = set.begin();
    for (; i1 != set.end(); ++i1)
    {
        for (register Monom::Integer var = 0; var < Monom::DimIndepend(); ++var)
        {
            gBasis.push_back(new Polynom(**i1));
            (*gBasis.back()) *= var;
        }
    }
#endif
    ReduceSet();

    qSet.Insert(gBasis);
    gBasis.clear();
    InvolutiveBasis();

    TSET::const_iterator i2(tSet.Begin());
    while(i2 != tSet.End())
    {
        gBasis.push_back(const_cast<Polynom*>((**i2).GetPoly()));
        i2++;
    }
    tSet.Clear();
    ReduceSet();
}

Polynom* GBasis::operator[](int num)
{
    std::list<Polynom*>::const_iterator it(gBasis.begin());
    for (register unsigned i = Length()-1-num; i > 0; i--)
    {
        it++;
    }
    return *it;
}

unsigned GBasis::Length()
{
    return gBasis.size();
}

std::ostream& operator<<(std::ostream& out, GBasis& gBasis)
{
    for (register unsigned i = 0; i < gBasis.Length(); i++)
    {
    		out << '[' << i << "] = " << *gBasis[i] << '\n';
    }

    return out;
}



