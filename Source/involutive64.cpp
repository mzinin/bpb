#include <iostream>
#include "involutive64.h"
#include "timer.h"

using namespace std;

//#define MK_STAT

#ifdef MK_STAT
long int c1=0, c2=0, c3=0, c4=0;
#endif

/*
Triple64* GBasis64::NormalForm(Triple64 *p)
{
  	Poly64 *h,*q;
  	Triple64  *inv_div;
  	q = new Poly64();
	h = new Poly64(*p->getPoly());

  	inv_div = tSet.find(h->lm());
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
  	//return q;
	if (q->lm() == p->getPolyLm())
		return new Triple64(q, p->getNmp());
	else
		return new Triple64(q);
}
*/

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

void GBasis64::AutoReduce()
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
  	Triple64* h;
	Triple64* current_trpl;

	do
	{
		tSet.update(qSet);
		if (qSet.empty()) break;
		tSet.insert(qSet);
		tSet.PAutoReduce();
	} while (true);

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
  	AutoReduce();

	tSet.insert(gBasis);
  	gBasis.clear();

  	InvolutiveBasis();

  	TSET::const_iterator i3(tSet.begin());
  	while( i3 != tSet.end() )
  	{
    		gBasis.push_back( (**i3).getPoly() );
    		i3++;
  	}
  	tSet.clear();

  	AutoReduce();

	//cout<<*this<<endl;

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
