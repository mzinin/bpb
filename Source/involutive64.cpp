#include <iostream>
#include "involutive64.h"
#include "timer.h"

using namespace std;

//#define MK_STAT

#ifdef MK_STAT
long int c1=0, c2=0, c3=0, c4=0;
#endif

bool GBasis64::Criteria1(Triple64 *p, Triple64 *g)
{
  	Monom64 tmp = p->getAncLm();
  	tmp.mult1(g->getAncLm());

  	if ( p->getPolyLm()==tmp && !p->getAncLm().gcd(g->getAncLm()) )
#ifdef MK_STAT
  	{
    		c1++;
#endif
    		return true;
#ifdef MK_STAT
  	}
#endif
  	else
    		return false;
}

bool GBasis64::Criteria2(Triple64 *p, Triple64 *g)
{
  	Monom64 tmp = p->getAncLm();
  	tmp.mult1(g->getAncLm());

  	if ( p->getPolyLm().divisibilityTrue(tmp) && !p->getAncLm().gcd(g->getAncLm()) )
#ifdef MK_STAT
  	{
    		c2++;
#endif
    		return true;
#ifdef MK_STAT
  	}
#endif
  	else
    		return false;
}

bool GBasis64::Criteria3(Triple64 *p, Triple64 *g)
{
  	Monom64  m = p->getPolyLm(), mp, mg;
	m.mult1(g->getPolyLm());
  	//Monom64  m = p->getAncLm(), mp, mg;
	//m.mult1(g->getAncLm());

  	TSET::const_iterator ctit(tSet.begin());
  	while( ctit != tSet.end() )
  	{
    		mp = p->getAncLm(); mp.mult1((**ctit).getPolyLm());
    		mg = g->getAncLm(); mg.mult1((**ctit).getPolyLm());
    		if( m.divisibilityTrue(mp) && m.divisibilityTrue(mg) )
#ifdef MK_STAT
    		{
      			c3++;
#endif
      			return true;
#ifdef MK_STAT
    		}
#endif
    		ctit++;
  	}

  	return false;
}

bool GBasis64::Criteria4(Triple64 *p, Triple64 *g)
{
  	TSET::const_iterator ctit(tSet.begin());
  	int dim = p->getAncLm().dimIndepend();
  	bitset<64> nm;

  	while ( p->getWanc() != *ctit && ctit!=tSet.end() )
    		if ((**ctit).getPoly()->degree() != p->getPoly()->degree()-1)
      			ctit++;
    		else
    		{
      			Monom64 tmp1 = p->getAncLm();
      			tmp1.mult((**ctit).getAncLm());
      			nm = (**ctit).getPoly()->Pnmv();
      			for (int i=0; i<dim; i++)
        			if (nm.test(i))
        			{
          				Monom64 tmp2 = (**ctit).getPolyLm();
          				tmp2.prolong(i);
          				if ( tmp2 == p->getPolyLm() )
            					if (tmp2.divisibilityTrue(tmp1))
#ifdef MK_STAT
            					{
              						c4++;
#endif
              						return true;
#ifdef MK_STAT
             					}
#endif
        			}
      			ctit++;
    		}

  	return false;
}

Poly64* GBasis64::NormalForm(Triple64 *p)
{
  	Poly64 *h,*q;
  	Triple64  *inv_div;
  	q = new Poly64();
	h = new Poly64(*p->getPoly());
/*
  	inv_div = tSet.find(h->lm());
  	if (p->isCriteriaAppliable() && inv_div)
  	{
    		//bool c = Criteria1(p, inv_div) || Criteria2(p, inv_div) || Criteria3(p, inv_div) || Criteria4(p, inv_div);
    		bool c = Criteria3(p, inv_div) || Criteria4(p, inv_div);
    		if (c)
    		{
      			delete h;
      			return q;
    		}
  	}
*/
  	while (!h->isZero())
  	{
		inv_div = tSet.find(h->lm());
    		while (inv_div)
    		{
      			h->head_reduction(*inv_div->getPoly());
      			if (!h->isZero())
				inv_div = tSet.find(h->lm());
      			else
        			inv_div = NULL;
    		}
    		if (!h->isZero())
    		{
      			q->add(h->lm());
      			h->rid_of_lm();
    		}
  	}

  	delete h;
  	return q;
}

Poly64* GBasis64::findR(Poly64 *p, list<Poly64*> &Q)
{
  	if ( p->isZero() ) return NULL;
  	list<Poly64*>::const_iterator iq(Q.begin()), q_end(Q.end());
  	Monom64 *plm = (Monom64*)&p->lm();

  	while ( iq != q_end )
  	{
    		if ( plm->divisibility((**iq).lm()) )
      			return *iq;
    		iq++;
  	}

  	return NULL;
}

Poly64* GBasis64::Reduce(Poly64 *p, list<Poly64*> &Q)
{
  	Poly64 *r, *q;
  	Poly64 *red;
  	q = new Poly64();
  	r = new Poly64(*p);
  	list<Poly64*> rrq;
  	list<Poly64*>::iterator it;

  	while ( !r->isZero() )
	{
    		red = findR(r, Q);
    		while ( red )
    		{
      			r->reduction(*red);
      			red = findR(r, Q);
    		}
    		if ( !r->isZero() )
    		{
      			q->add(r->lm());
      			r->rid_of_lm();
    		}
  	}

  	delete r;
  	return q;
}

void GBasis64::ReduceSet()
{
  	list<Poly64*> R, P, Q;
  	list<Poly64*>::iterator ir(R.begin()), ip(P.begin()), iq(Q.begin());
  	list<Poly64*>::const_iterator j(gBasis.begin()), q_end, r_end, p_end;
  	Poly64 *h, *h1;
  	int num;

  	R = gBasis;

  	while (!R.empty())
  	{
    		ir = R.begin();
    		h = *ir;
    		ir = R.erase(ir);
    		h = Reduce(h, P);
    		if ( !h->isZero() )
		{
      			//Q - ? не помню старый комментарий
      			Monom64 *hlm=(Monom64*)&h->lm();
      			ip = P.begin();
      			p_end = P.end();
      			while ( ip != p_end )
      			{
        			if ((**ip).lm().divisibility(*hlm))
          				iq = Q.insert(iq,*ip);
				++ip;
      			}
      			//R = R U Q
      			iq = Q.begin();
      			q_end = Q.end();
      			while ( iq != q_end )
      			{
        			ir = R.begin();
        			r_end = R.end();
        			while ( ir!=r_end && (**ir)!=(**iq) )
	  				++ir;
        			if ( ir == r_end)
          				ir = R.insert(ir, *iq);
				++iq;
      			}
      			//P = (P-Q) U {h}
      			ip = P.begin();
      			while ( ip != P.end() )
      			{
        			iq = Q.begin();
        			q_end = Q.end();
        			while ( iq!=q_end && (**iq)!=(**ip) )
	  				++iq;
        			if ( iq != q_end )
          				ip = P.erase(ip);
				else
					++ip;
      			}
      			ip = P.insert(ip, h);
    		}
  	}

  	R.clear(); //не помню
  	Q.clear(); //вместо S из книги
  	ir = R.begin();
  	iq = Q.begin();
  	ip = P.begin();
  	p_end = P.end();
  	while ( ip != p_end )
  	{
    		iq = Q.insert(iq, *ip);
    		++ip;
  	}

  	ip = P.begin();
  	while ( ip != p_end )
  	{
    		h = *ip;
    		iq = Q.begin();
    		while ( (*h)!=(**iq) ) ++iq;
    		iq = Q.erase(iq);
    		h1 = Reduce(h, Q);
    		iq = Q.insert(iq, h);
    		if ( !h1->isZero() )
      			ir = R.insert(ir, h1);
    		++ip;
  	}
  	gBasis.clear();
  	gBasis = R;
}

void GBasis64::InvolutiveBasis()
{
static long counter = 0;
  	TSET::iterator tit(tSet.begin());
  	Poly64* h;
	Triple64* current_trpl;
  	bool lm_changed;

  	while (!qSet.empty())
  	{
/*
std::cout << counter++ << " ==========================================================================" << std::endl;
std::cout << "qSet: "; int i = 0;
for (list<Triple64*>::const_iterator it = qSet.trpl_list.begin(); it != qSet.trpl_list.end(); ++it)
{
    std::cout << "\t\t[" << i++ << "] " << *(**it).getPoly() << std::endl;
}
std::cout << std::endl << "tSet: "; i = 0;
for (TSET::const_iterator it = tSet.begin(); it != tSet.end(); ++it)
{
    std::cout << "\t\t[" << i++ << "] " << *(**it).getPoly() << std::endl;
}
*/
		current_trpl = qSet.get();

//std::cout << std::endl << "Calculate NF of: " << *current_trpl->getPoly() << std::endl;

    		h = NormalForm(current_trpl);

//std::cout << "         Result: " << *h << std::endl << std::endl;

		if (!h->isZero() && h->lm()==current_trpl->getPolyLm())
      			lm_changed = false;
    		else
      			lm_changed = true;

		bitset<64> n = current_trpl->getNmp();
    		const Triple64* qanc = current_trpl->getAnc();
		if ( qanc == current_trpl ) qanc = NULL;

		delete current_trpl;

    		if ( !h->isZero() )
    		{
      			list<Triple64*> add_to_qSet;

      			tit = tSet.begin();
      			while ( tit != tSet.end() )
			{
        			if ( (*tit)->getPolyLm().divisibilityTrue(h->lm()) )
        			{
					qSet.delete_Descendant(*tit);
	  				add_to_qSet.push_back(*tit);
          				tit = tSet.erase(tit);
        			}
        			else
				{
          				tit++;
				}
			}

      			if ( lm_changed )
        			tSet.push_back(new Triple64(h, NULL, NULL, 0, -1));
      			else
        			tSet.push_back(new Triple64(h, qanc, NULL, n, -1));

			qSet.update(tSet.back(), add_to_qSet);
			qSet.insert(add_to_qSet);
    		}
    		else
      			delete h;
  	}
}

GBasis64::GBasis64(): gBasis(), qSet(), tSet() {}

GBasis64::GBasis64(list<Poly64*> set): gBasis(), qSet(), tSet()
{
  	list<Poly64*>::const_iterator i1(set.begin());
  	list<Poly64*>::iterator i2(gBasis.begin());
  	int i;

  	Dim = (**i1).lm().dimIndepend();
  	while (i1!=set.end())
  	{
    		i2=gBasis.insert(i2, new Poly64(**i1));
/*
    		for (i = 0; i < Dim; i++)
    		{
      			i2=gBasis.insert(i2, new Poly64(**i1));
      			(**i2).mult(i);
    		}
*/
    		++i1;
  	}
//  	ReduceSet();

	qSet.insert(gBasis);
  	gBasis.clear();

  	InvolutiveBasis();

  	TSET::const_iterator i3(tSet.begin());
  	while( i3 != tSet.end() )
  	{
    		gBasis.push_back( (**i3).getPoly() );
    		i3++;
  	}
  	tSet.clear();

  	ReduceSet();

#ifdef MK_STAT
  	long int all_c = c1 + c2 + c3 + c4;
  	cout<<"All criteria: "<<all_c<<endl;
  	cout<<"Criterion 1: "<<c1<<" ("<<(double(c1)/all_c)*100<<"%)"<<endl;
  	cout<<"Criterion 2: "<<c2<<" ("<<(double(c2)/all_c)*100<<"%)"<<endl;
  	cout<<"Criterion 3: "<<c3<<" ("<<(double(c3)/all_c)*100<<"%)"<<endl;
  	cout<<"Criterion 4: "<<c4<<" ("<<(double(c4)/all_c)*100<<"%)"<<endl<<endl;
#endif
}

Poly64* GBasis64::operator[](int num)
{
  	list<Poly64*>::const_iterator it(gBasis.begin());
  	for (register int i=length()-1-num; i>0; i--) it++;
  	return *it;
}

int GBasis64::length()
{
  	return gBasis.size();
}

std::ostream& operator<<(std::ostream& out, GBasis64& GBasis)
{
  	int i=0;
  	for (i=0;i<GBasis.length();i++)
    		out<<'['<<i<<"] = "<<*GBasis[i]<<'\n';

  	return out;
}
