#include <iostream>
#include "involutive.h"
#include "timer.h"
#include "pcomparator.h"

using namespace std;

#ifdef COLLECT_STATISTIC
long int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
#endif

#ifdef USE_CRITERIA
bool GBasis::Criteria1(const Triple* p, const Triple* g)
{
    Monom tmp = p->GetAncLm();
    tmp *= g->GetAncLm();

    if (p->GetPolyLm() == tmp && !Monom::GcdDegree(p->GetAncLm(), g->GetAncLm()))
    {
#ifdef COLLECT_STATISTIC
        c1++;
#endif
        return true;
    }
    else
    {
        return false;
    }
}

bool GBasis::Criteria2(const Triple* p, const Triple* g)
{
    Monom tmp = p->GetAncLm();
    tmp *= g->GetAncLm();

    if (p->GetPolyLm().IsTrueDivisibleBy(tmp) && !Monom::GcdDegree(p->GetAncLm(), g->GetAncLm()))
    {
#ifdef COLLECT_STATISTIC
        c2++;
#endif
        return true;
    }
    else
    {
        return false;
    }
}

bool GBasis::Criteria3(const Triple* p, const Triple* g)
{
    Monom m = p->GetPolyLm(), mp, mg;
    m *= g->GetPolyLm();
    //Monom m = p->getAncLm(), mp, mg;
    //m *= g->getAncLm();

    TSET::const_iterator ctit(tSet.Begin());
    while(ctit != tSet.End())
    {
        mp = p->GetAncLm(); mp *= (**ctit).GetPolyLm();
        mg = g->GetAncLm(); mg *= (**ctit).GetPolyLm();
        if(m.IsTrueDivisibleBy(mp) && m.IsTrueDivisibleBy(mg))
        {
#ifdef COLLECT_STATISTIC
            c3++;
#endif
            return true;
        }
        ctit++;
    }

    return false;
}

bool GBasis::Criteria4(const Triple* p, const Triple* g)
{
    TSET::const_iterator ctit(tSet.Begin());

    while (ctit != tSet.End() && p->GetWanc() != *ctit)
    {
        if ((**ctit).GetPoly()->Degree() == p->GetPoly()->Degree()-1)
        {
            Monom tmp1(p->GetAncLm());
            //tmp1 *= (**ctit).getAncLm();

            Triple* ct = *ctit;
            tmp1 *= ct->GetAncLm();

            Monom::Integer firstMultiVar = (**ctit).GetPolyLm().FirstMultiVar();
            for (register Monom::Integer i = 0; i < firstMultiVar; i++)
            {
                Monom tmp2((**ctit).GetPolyLm());
                tmp2 *= i;
                if (tmp2 == p->GetPolyLm())
                {
                    if (tmp2.IsTrueDivisibleBy(tmp1))
                    {
#ifdef COLLECT_STATISTIC
                        c4++;
#endif
                        return true;
                    }
                }
            }
        }
        ctit++;
    }

    return false;
}
#endif

Polynom* GBasis::NormalForm(const Triple* p)
{
    Polynom *h, *q;
    const Triple  *involutiveDivisor;
    q = new Polynom();
    h = new Polynom(*p->GetPoly());

#ifdef USE_CRITERIA
    involutiveDivisor = tSet.Find(h->Lm());
    if (p->IsCriteriaAppliable() && involutiveDivisor)
    {
        bool c = Criteria1(p, involutiveDivisor) || Criteria2(p, involutiveDivisor) || Criteria3(p, involutiveDivisor);// || Criteria4(p, involutiveDivisor);
        //bool c = Criteria3(p, involutiveDivisor) || Criteria4(p, involutiveDivisor);
        Criteria4(p, involutiveDivisor);
        if (c)
        {
            delete h;
            return q;
        }
    }
#endif

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
    //gBasis.sort(PointerMoreComparator<Polynom>());

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
    Polynom* h;
    Triple* current_trpl;

    while (!qSet.Empty())
    {
        current_trpl = qSet.Get();
        h = NormalForm(current_trpl);

        set<Monom::Integer> n;
        const Triple* qanc = NULL;
        if (!h->IsZero() && h->Lm() == current_trpl->GetPolyLm())
        {
            n = current_trpl->GetNmp();
            qanc = current_trpl->GetAnc();
            if (qanc == current_trpl)
            {
                qanc = NULL;
            }
        }
        delete current_trpl;

        if (!h->IsZero())
        {
            list<Triple*> add_to_qSet;
            tit = tSet.Begin();

            while (tit != tSet.End())
            {
                if ((**tit).GetPolyLm().IsTrueDivisibleBy(h->Lm()))
                {
                    qSet.DeleteDescendants(*tit);
                    add_to_qSet.push_back(*tit);
                    tit = tSet.Erase(tit);
                }
                else
                {
                    tit++;
                }
            }

#ifdef USE_CRITERIA
            tSet.PushBack(new Triple(h, qanc, NULL, n, -1));
#else
            tSet.PushBack(new Triple(h, qanc, n));
#endif
            if (!h->Degree()) return;

            qSet.Update(tSet.Back(), add_to_qSet);
            qSet.Insert(add_to_qSet);
        }
        else
        {
            delete h;
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
cout << "Size: " << gBasis.size() << endl;

#ifdef COLLECT_STATISTIC
    long int all_c = c1 + c2 + c3 + c4;
    cout << "All criteria: " << all_c<<endl;
    cout << "Criterion 1: " << c1 << " (" << (double(c1)/all_c)*100 << "%)" << endl;
    cout << "Criterion 2: " << c2 << " (" << (double(c2)/all_c)*100 << "%)" << endl;
    cout << "Criterion 3: " << c3 << " (" << (double(c3)/all_c)*100 << "%)" << endl;
    cout << "Criterion 4: " << c4 << " (" << (double(c4)/all_c)*100 << "%)" << endl << endl;
#endif
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
