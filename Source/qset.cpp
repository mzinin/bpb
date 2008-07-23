#include "qset.h"

QSET::QSET(): trpl_list()
{
}

QSET::QSET(list<Poly64*> &basis): trpl_list()
{
	list<Poly64*>::const_iterator it_basis(basis.begin());
  	while ( it_basis != basis.end() )
  	{
    		trpl_list.push_back( new Triple64(*it_basis) );
    		it_basis++;
  	}
  	trpl_list.sort(Triple64::compare);
}

QSET::~QSET()
{
	list<Triple64*>::iterator it(trpl_list.begin());
	while( it != trpl_list.end() )
	{
		delete *it;
		it++;
	}
	trpl_list.clear();
}

void QSET::insert(list<Poly64*> &add_list)
{
	list<Poly64*>::const_iterator it_basis(add_list.begin());
  	while ( it_basis != add_list.end() )
  	{
    		trpl_list.push_back( new Triple64(*it_basis) );
    		it_basis++;
  	}
  	trpl_list.sort(Triple64::compare);
}

void QSET::insert(list<Triple64*> &add_list)
{
	add_list.sort(Triple64::compare);
	trpl_list.merge(add_list, Triple64::compare);
}


void QSET::update(Triple64* new_trpl, list<Triple64*> &set)
{
  	bitset<64> nonmulti = new_trpl->getPolyLm().Pnmv();
	Monom64 tmpm;

  	for (register int var = 0; var < new_trpl->getPolyLm().dimIndepend(); var++)
        {
    		if (nonmulti.test(var) && !new_trpl->getNmp().test(var))
		//if (nonmulti.test(var))
      		{
        		Poly64* tmp = new Poly64(*new_trpl->getPoly());
        		tmp->mult(var);
        		if (!tmp->isZero())
			{
				tmpm = new_trpl->getPolyLm();
				tmpm.prolong(var);
				if ( tmpm == tmp->lm() )
		  			//set.push_back(new Triple64(tmp, new_trpl->getAnc(), new_trpl, 0, var));
					set.push_back(new Triple64(tmp, new_trpl->getAnc(), new_trpl, new_trpl->getNmp(), var));
				else
					set.push_back(new Triple64(tmp));
			}
			new_trpl->setNmp(var);
      		}
        }
}

Triple64* QSET::get()
{
	Triple64* result = trpl_list.back();
	trpl_list.pop_back();
	return result;
}

void QSET::delete_Descendant(Triple64* ancestor)
{
	list<Triple64*>::iterator it(trpl_list.begin());
	while ( it != trpl_list.end() )
		if ( (**it).getAnc() == ancestor )
		{
              		delete *it;
              		it = trpl_list.erase(it);
            	}
            	else
              		it++;
}
