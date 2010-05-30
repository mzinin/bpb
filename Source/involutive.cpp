#include <iostream>
#include "involutive.h"
#include "timer.h"
#include "pcomparator.h"

using namespace std;

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

const Polynom* GBasis::FindR(const Polynom* p, const list<Polynom*>& Q)
{
    if (p->IsZero())
    {
        return NULL;
    }

    list<Polynom*>::const_iterator iq(Q.begin()), qEnd(Q.end());
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

Polynom* GBasis::Reduce(Polynom* p, const list<Polynom*>& Q)
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
    list<Polynom*> tmpPolySet;
    gBasis.sort(PointerMoreComparator<Polynom>());

    while (!gBasis.empty())
    {
        Polynom* h = gBasis.front();
        gBasis.pop_front();
        h = Reduce(h, tmpPolySet);

        if (!h->IsZero())
        {
            const Monom& hLm = h->Lm();
            list<Polynom*>::iterator iteratorTmpPolySet = tmpPolySet.begin();
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

        set<Monom::Integer> n;
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
            list<Triple*> additionalToQSet;
            tit = tSet.Begin();

            while (tit != tSet.End())
            {
                if ((**tit).GetPolyLm().IsTrueDivisibleBy(newNormalForm->Lm()))
                {
                    //(**tit).SetNmp(std::set<Monom::Integer>());
                    qSet.DeleteDescendants(*tit);
                    additionalToQSet.push_back(*tit);
                    tit = tSet.Erase(tit);
                }
                else
                {
                    tit++;
                }
            }

            tSet.PushBack(new Triple(newNormalForm, qanc, n, 0, -1));
            if (!newNormalForm->Degree()) return;

            qSet.Update(tSet.Back(), additionalToQSet);
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

GBasis::GBasis(const list<Polynom*>& set): gBasis(set), qSet(), tSet()
{
    ReduceSet();

    qSet.Insert(gBasis);
    gBasis.clear();
    InvolutiveBasis();

    TSET::const_iterator i3(tSet.Begin());
    while(i3 != tSet.End())
    {
        gBasis.push_back(const_cast<Polynom*>((**i3).GetPoly()));
        i3++;
    }
    tSet.Clear();
    ReduceSet();
}

Polynom* GBasis::operator[](int num)
{
    list<Polynom*>::const_iterator it(gBasis.begin());
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
