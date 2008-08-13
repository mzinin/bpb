#include "tset.h"

TSET::TSET(): trpl_list()//, jTree()
{
}

TSET::~TSET()
{
	//jTree.clear();

	list<Triple64*>::iterator it(trpl_list.begin());
	while( it != trpl_list.end() )
	{
		delete *it;
		it++;
	}
	trpl_list.clear();
}

void TSET::clear()
{
	//jTree.clear();
	trpl_list.clear();
}

TSET::iterator TSET::erase(TSET::iterator it)
{
	//jTree.del(*it);
	return trpl_list.erase(it);
}

void TSET::push_back(Triple64* new_trpl)
{
	trpl_list.push_back(new_trpl);
	//jTree.insert(new_trpl);
}

Triple64* TSET::PfindR(Triple64 *t, list<Triple64*> &Q)
{
  	if ( t->getPoly()->isZero() ) return NULL;
  	list<Triple64*>::const_iterator iq(Q.begin()), q_end(Q.end());
  	Monom64 *plm = (Monom64*)&t->getPolyLm();

  	while ( iq != q_end )
  	{
    		if ( plm->divisibilityPommaret((**iq).getPolyLm()) )
      			return *iq;
    		iq++;
  	}

  	return NULL;
}

Triple64* TSET::PReduce(Triple64 *t, list<Triple64*> &Q)
{
  	Poly64 *q;
  	Triple64 *red, *r;
  	q = new Poly64();
  	r = new Triple64( new Poly64(*t->getPoly()) );

  	list<Triple64*> rrq;
  	list<Triple64*>::iterator it;

  	while ( !r->getPoly()->isZero() )
	{
    		red = PfindR(r, Q);
    		while ( red )
    		{
      			r->getPoly()->Phead_reduction(*red->getPoly());
      			red = PfindR(r, Q);
    		}
    		if ( !r->getPoly()->isZero() )
    		{
      			q->add(r->getPolyLm());
      			r->getPoly()->rid_of_lm();
    		}
  	}

  	delete r;

	Triple64 *qt;
	if ( !q->isZero() && q->lm() == t->getPolyLm() )
		qt = new Triple64(q, t->getNmp());
	else
		qt = new Triple64(q);
  	return qt;
}

void TSET::PAutoReduce()
{
  	list<Triple64*> R, P, Q;
  	list<Triple64*>::iterator ir(R.begin()), ip(P.begin()), iq(Q.begin());
  	list<Triple64*>::const_iterator j(trpl_list.begin()), q_end, r_end, p_end;
  	Triple64 *h, *h1;
  	int num;

  	R = trpl_list;

  	while (!R.empty())
  	{
    		ir = R.begin();
    		h = *ir;
    		ir = R.erase(ir);
    		h = PReduce(h, P);

    		if ( !h->getPoly()->isZero() )
		{
      			Monom64 *hlm=(Monom64*)&h->getPolyLm();
      			ip = P.begin();
      			p_end = P.end();
      			while ( ip != p_end )
      			{
        			if ( (**ip).getPolyLm().divisibilityPommaret(*hlm) )
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
        			while ( ir!=r_end && *(**ir).getPoly()!=*(**iq).getPoly() )
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
        			while ( iq!=q_end && *(**iq).getPoly()!=*(**ip).getPoly() )
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
    		while ( *(*h).getPoly()!=*(**iq).getPoly() ) ++iq;
    		iq = Q.erase(iq);
    		h1 = PReduce(h, Q);
    		iq = Q.insert(iq, h);
    		if ( !h1->getPoly()->isZero() )
      			ir = R.insert(ir, h1);
    		++ip;
  	}
  	trpl_list.clear();
  	trpl_list = R;
}

void TSET::insert(list<Poly64*> &add_list)
{
	list<Poly64*>::const_iterator it_basis(add_list.begin());
  	while ( it_basis != add_list.end() )
  	{
    		trpl_list.push_back( new Triple64(*it_basis) );
		//jTree.insert( trpl_list.back() );
    		it_basis++;
  	}
}

void TSET::insert(list<Triple64*> &add_list)
{
	list<Triple64*>::const_iterator it_basis(add_list.begin());
  	while ( it_basis != add_list.end() )
  	{
    		trpl_list.push_back( *it_basis );
		//jTree.insert( trpl_list.back() );
    		it_basis++;
  	}
}

void TSET::insert(QSET &qSet)
{
	while (!qSet.empty())
	{
		trpl_list.push_back( qSet.get() );
		//jTree.insert( trpl_list.back() );
	}
}

void TSET::update(QSET &qSet)
{
  	bitset<64> nonmulti, current_nmp;
	const_iterator it(trpl_list.begin());
	int dim = (**it).getPolyLm().dimIndepend();

	while (it != trpl_list.end())
	{
		nonmulti = (**it).getPolyLm().Pnmv();
		current_nmp = (**it).getNmp();

	  	for (register int var = 0; var < dim; var++)
			if (nonmulti.test(var) && !current_nmp.test(var))
      			{
        			Poly64* tmp = new Poly64( *(**it).getPoly() );
        			tmp->mult(var);
        			if (!tmp->isZero())
				{
					qSet.insert(new Triple64(tmp));
				}
				(**it).setNmp(var);
      			}

		it++;
	}
}
