#include <iostream>
#include "involutive.h"
#include "timer.h"

using namespace std;

//#define MK_STAT

#ifdef MK_STAT
long int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
#endif

bool GBasis::Criteria1(Triple* p, Triple* g)
{
    Monom tmp = p->getAncLm();
    tmp *= g->getAncLm();

    if (p->getPolyLm() == tmp && !Monom::GCD_degree(p->getAncLm(), g->getAncLm()))
    {
#ifdef MK_STAT
        c1++;
#endif
        return true;
    }
    else
    {
        return false;
    }
}

bool GBasis::Criteria2(Triple* p, Triple* g)
{
    Monom tmp = p->getAncLm();
    tmp *= g->getAncLm();

    if (p->getPolyLm().isTrueDivisibleBy(tmp) && !Monom::GCD_degree(p->getAncLm(), g->getAncLm()))
    {
#ifdef MK_STAT
        c2++;
#endif
        return true;
    }
    else
    {
        return false;
    }
}

bool GBasis::Criteria3(Triple* p, Triple* g)
{
    Monom m = p->getPolyLm(), mp, mg;
    m *= g->getPolyLm();
    //Monom m = p->getAncLm(), mp, mg;
    //m *= g->getAncLm();

    TSET::tsConstIterator ctit(tSet.begin());
    while(ctit != tSet.end())
    {
        mp = p->getAncLm(); mp *= (**ctit).getPolyLm();
        mg = g->getAncLm(); mg *= (**ctit).getPolyLm();
        if(m.isTrueDivisibleBy(mp) && m.isTrueDivisibleBy(mg))
        {
#ifdef MK_STAT
            c3++;
#endif
            return true;
        }
        ctit++;
    }

    return false;
}

bool GBasis::Criteria4(Triple* p, Triple* g)
{
    TSET::tsConstIterator ctit(tSet.begin());

    while (p->getWanc() != *ctit && ctit != tSet.end())
    {
        if ((**ctit).getPoly()->degree() == p->getPoly()->degree()-1)
        {
            Monom tmp1 = p->getAncLm();
            tmp1 *= (**ctit).getAncLm();
            Monom::Integer firstMultiVar = (**ctit).getPolyLm().firstMultiVar();
            for (register Monom::Integer i = 0; i < firstMultiVar; i++)
            {
                Monom tmp2 = (**ctit).getPolyLm();
                tmp2 *= i;
                if (tmp2 == p->getPolyLm())
                {
                    if (tmp2.isTrueDivisibleBy(tmp1))
                    {
#ifdef MK_STAT
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

Polynom* GBasis::NormalForm(Triple* p)
{
    Polynom *h, *q;
    Triple  *involutiveDivisor;
    q = new Polynom();
    h = new Polynom(*p->getPoly());

/*
    involutiveDivisor = tSet.find(h->lm());
    if (p->isCriteriaAppliable() && involutiveDivisor)
    {
        //bool c = Criteria1(p, inv_div) || Criteria2(p, inv_div) || Criteria3(p, inv_div) || Criteria4(p, inv_div);
        bool c = Criteria3(p, involutiveDivisor) || Criteria4(p, involutiveDivisor);
        if (c)
        {
            delete h;
            return q;
        }
    }
*/

    while (!h->isZero())
    {
        involutiveDivisor = tSet.find(h->lm());
        while (involutiveDivisor)
        {
            h->headReduction(*involutiveDivisor->getPoly());
            if (!h->isZero())
            {
                involutiveDivisor = tSet.find(h->lm());
            }
            else
            {
                involutiveDivisor = NULL;
            }
        }

        if (!h->isZero())
        {
            (*q) += h->lm();
            h->ridOfLm();
        }
    }

    delete h;
    return q;
}

Polynom* GBasis::findR(Polynom* p, list<Polynom*> &Q)
{
    if (p->isZero())
    {
        return NULL;
    }

    list<Polynom*>::const_iterator iq(Q.begin()), qEnd(Q.end());
    const Monom& plm = p->lm();

    while (iq != qEnd)
    {
        if (plm.isDivisibleBy((**iq).lm()) )
        {
            return *iq;
        }
        iq++;
    }

    return NULL;
}

Polynom* GBasis::Reduce(Polynom* p, list<Polynom*> &Q)
{
    Polynom *r, *q, *red;
    q = new Polynom();
    r = new Polynom(*p);

    while (!r->isZero())
    {
        red = findR(r, Q);
        while (red)
        {
            r->reduction(*red);
            red = findR(r, Q);
        }
        if (!r->isZero())
        {
            (*q) += r->lm();
            r->ridOfLm();
        }
    }

    delete r;
    return q;
}

void GBasis::ReduceSet()
{
    list<Polynom*> R, P, Q;
    list<Polynom*>::iterator ir(R.begin()), ip(P.begin()), iq(Q.begin());
    list<Polynom*>::const_iterator j(gBasis.begin()), qEnd, rEnd, pEnd;
    Polynom *h, *h1;
    int num;

    R = gBasis;
    while (!R.empty())
    {
        ir = R.begin();
        h = *ir;
        ir = R.erase(ir);
        h = Reduce(h, P);

        if (!h->isZero())
        {
            const Monom& hlm = h->lm();
            ip = P.begin();
            pEnd = P.end();
            while (ip != pEnd)
            {
                if ((**ip).lm().isDivisibleBy(hlm))
                {
                    iq = Q.insert(iq, *ip);
                }
                ip++;
            }

            iq = Q.begin();
            qEnd = Q.end();
            while (iq != qEnd)
            {
                ir = R.begin();
                rEnd = R.end();
                while (ir != rEnd && (**ir) != (**iq))
                {
                    ir++;
                }
                if (ir == rEnd)
                {
                    ir = R.insert(ir, *iq);
                }
                iq++;
            }

            ip = P.begin();
            while (ip != P.end())
            {
                iq = Q.begin();
                qEnd = Q.end();
                while (iq != qEnd && (**iq) != (**ip))
                {
                    iq++;
                }
                if (iq != qEnd)
                {
                    ip = P.erase(ip);
                }
                else
                {
                    ip++;
                }
            }
            ip = P.insert(ip, h);
        }
    }

    R.clear();
    Q.clear();
    ir = R.begin();
    iq = Q.begin();
    ip = P.begin();
    pEnd = P.end();
    while (ip != pEnd)
    {
        iq = Q.insert(iq, *ip);
        ip++;
    }

    ip = P.begin();
    while (ip != pEnd)
    {
        h = *ip;
        iq = Q.begin();
        while ((*h) != (**iq))
        {
            iq++;
        }
        iq = Q.erase(iq);
        h1 = Reduce(h, Q);
        iq = Q.insert(iq, h);
        if (!h1->isZero())
        {
            ir = R.insert(ir, h1);
        }
        ip++;
    }
    gBasis.clear();
    gBasis = R;
}

void GBasis::InvolutiveBasis()
{
    TSET::tsIterator tit(tSet.begin());
    Polynom* h;
    Triple* current_trpl;
    bool lm_changed;

    while (!qSet.empty())
    {
        current_trpl = qSet.get();
        h = NormalForm(current_trpl);

        set<Monom::Integer> n;
        const Triple* qanc = NULL;
        if (!h->isZero() && h->lm() != current_trpl->getPolyLm())
        {
            n = current_trpl->getNmp();
            qanc = current_trpl->getAnc();
            if (qanc == current_trpl)
            {
                qanc = NULL;
            }
        }
        delete current_trpl;

        if (!h->isZero())
        {
            list<Triple*> add_to_qSet;
            tit = tSet.begin();

            while (tit != tSet.end())
            {
                if ((**tit).getPolyLm().isTrueDivisibleBy(h->lm()))
                {
                    qSet.deleteDescendants(*tit);
                    add_to_qSet.push_back(*tit);
                    tit = tSet.erase(tit);
                }
                else
                {
                    tit++;
                }
            }

            tSet.push_back(new Triple(h, qanc, NULL, n, -1));

            qSet.update(tSet.back(), add_to_qSet);
            qSet.insert(add_to_qSet);
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

GBasis::GBasis(list<Polynom*> set): gBasis(), qSet(), tSet()
{
    list<Polynom*>::const_iterator i1(set.begin());
    list<Polynom*>::iterator i2(gBasis.begin());

    Dim = (**i1).lm().dimIndepend();
    while (i1 != set.end())
    {
        i2 = gBasis.insert(i2, new Polynom(**i1));
/*
        for (register Monom::Integer i = 0; i < Dim; i++)
        {
            i2 = gBasis.insert(i2, new Polynom(**i1));
            (**i2) *= i;
        }
*/
        ++i1;
    }
    ReduceSet();

    qSet.insert(gBasis);
    gBasis.clear();
    InvolutiveBasis();

    TSET::tsConstIterator i3(tSet.begin());
    while(i3 != tSet.end())
    {
        gBasis.push_back((**i3).getPoly());
        i3++;
    }
    tSet.clear();
    ReduceSet();


#ifdef MK_STAT
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
    for (register unsigned i = length()-1-num; i > 0; i--)
    {
        it++;
    }
    return *it;
}

unsigned GBasis::length()
{
    return gBasis.size();
}

std::ostream& operator<<(std::ostream& out, GBasis& gBasis)
{
    for (register unsigned i = 0; i < gBasis.length(); i++)
    {
    		out << '[' << i << "] = " << *gBasis[i] << '\n';
    }

    return out;
}
