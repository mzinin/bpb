#include <iostream>
#include "involutive64.h"
#include "timer.h"

using namespace std;

//#define MK_STAT

#ifdef MK_STAT
long int c1=0, c2=0, c3=0, c4=0;
#endif

void showlm(list<Triple64*> set, const char *msg)
{
  list<Triple64*>::const_iterator i(set.begin());
  cout<<msg<<" {";
  while (i!=set.end())
  {
    //cout<<'('<<(*i)->poly->lm()<<','<<(*i)->anc<<")  ";
    cout<<*(*i)->poly<<','<<endl;
    i++;
  }
  cout<<"}"<<endl;
}

bool GBasis64::Criteria1(Triple64 &p, Triple64 &g)
{
  Monom64 tmp = p.anc;
  tmp.mult1(g.anc);

  if ( p.poly->lm()==tmp && !p.anc.gcd(g.anc))
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

bool GBasis64::Criteria2(Triple64 &p, Triple64 &g)
{
  Monom64 tmp = p.anc;
  tmp.mult1(g.anc);

  if ( p.poly->lm().divisibilityTrue(tmp) )
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

bool GBasis64::Criteria3(Triple64 &p, Triple64 &g)
{
  Monom64  m = p.poly->lm(), mp, mg; m.mult1(g.poly->lm());
  //Monom64  m = p.anc, mp, mg; m.mult1(g.anc);

  list<Triple64*>::const_iterator ctit(tSet.begin());
  while(ctit!=tSet.end())
  {
    mp = p.anc; mp.mult1((**ctit).poly->lm());
    mg = g.anc; mg.mult1((**ctit).poly->lm());
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

bool GBasis64::Criteria4(Triple64 &p, Triple64 &g)
{
  list<Triple64*>::const_iterator ctit(tSet.begin());
  int dim = p.anc.dimIndepend();
  bitset<64> nm;

  while (p.wanc!=*ctit && ctit!=tSet.end())
    if ((**ctit).poly->degree() != p.poly->degree()-1)
      ctit++;
    else
    {
      Monom64 tmp1 = p.anc;
      tmp1.mult((**ctit).anc);
      nm = (**ctit).poly->Pnmv();
      for (int i=0; i<dim; i++)
        if (nm.test(i))
        {
          Monom64 tmp2 = (**ctit).poly->lm();
          tmp2.prolong(i);
          if (tmp2==p.poly->lm())
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

Poly64* GBasis64::NormalForm(Triple64 &p)
{
  Poly64 *h,*q;
  Triple64  *inv_div;
  q = new Poly64();
  h = new Poly64(*p.poly);

  inv_div = jTree.find(h->lm());
  if (p.prolong && inv_div)
  {
    //bool c = Criteria1(p, *inv_div) || Criteria2(p, *inv_div) || Criteria3(p, *inv_div) || Criteria4(p, *inv_div);
    bool c = Criteria3(p, *inv_div);// || Criteria2(p, *inv_div);
    if (c)
    {
      delete h;
      return q;
    }
  }

  while (!h->isZero())
  {
    inv_div = jTree.find(h->lm());
    while (inv_div)
    {
      h->head_reduction(*inv_div->poly);
      if (!h->isZero())
        inv_div = jTree.find(h->lm());
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

Poly64* GBasis64::findR(Poly64& p, list<Poly64*> &Q)
{
  if (p.isZero()) return NULL;
  list<Poly64*>::const_iterator iq(Q.begin()), q_end(Q.end());
  Monom64 *plm = (Monom64*)&p.lm();

  while (iq!=q_end)
  {
    if ( plm->divisibility((**iq).lm()) )
      return *iq;
    iq++;
  }

  return NULL;
}

Poly64* GBasis64::Reduce(Poly64 &p, list<Poly64*> &Q)
{
  Poly64 *r,*q;
  Poly64 *red;
  q = new Poly64();
  r = new Poly64(p);
  list<Poly64*> rrq;
  list<Poly64*>::iterator it;

  while (!r->isZero()){
    red = findR(*r,Q);
    while (red)
    {
      r->reduction(*red);
      red = findR(*r,Q);
    }
    if (!r->isZero())
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
  list<Poly64*> R,P,Q;
  list<Poly64*>::iterator ir(R.begin()), ip(P.begin()), iq(Q.begin());
  list<Poly64*>::const_iterator j(gBasis.begin()), q_end, r_end, p_end;
  Poly64 *h,*h1;
  int num;

  R = gBasis;

  while (!R.empty())
  {
    ir = R.begin();
    h = *ir;
    ir = R.erase(ir);
    h = Reduce(*h,P);
    if (!h->isZero()){
      //Q - ? не помню старый комментарий
      Monom64 *hlm=(Monom64*)&h->lm();
      ip = P.begin();
      p_end = P.end();
      while (ip!=p_end)
      {
        if ((**ip).lm().divisibility(*hlm))
          iq = Q.insert(iq,*ip);
	++ip;
      }
      //R = R U Q
      iq = Q.begin();
      q_end = Q.end();
      while (iq!=q_end)
      {
        ir = R.begin();
        r_end = R.end();
        while (ir!=r_end && (**ir)!=(**iq))
	  ++ir;
        if (ir==r_end)
          ir=R.insert(ir,*iq);
	++iq;
      }
      //P = (P-Q) U {h}
      ip = P.begin();
      while (ip!=P.end())
      {
        iq = Q.begin();
        q_end = Q.end();
        while (iq!=q_end && (**iq)!=(**ip))
	  ++iq;
        if (iq!=q_end)
          ip = P.erase(ip);
	else ++ip;
      }
      ip = P.insert(ip,h);
    }
  }

  R.clear(); //не помню
  Q.clear(); //вместо S из книги
  ir = R.begin();
  iq = Q.begin();
  ip = P.begin();
  p_end = P.end();
  while (ip!=p_end)
  {
    iq = Q.insert(iq,*ip);
    ++ip;
  }

  ip = P.begin();
  while (ip!=p_end)
  {
    h = *ip;
    iq = Q.begin();
    while ((*h)!=(**iq)) ++iq;
    iq = Q.erase(iq);
    h1 = Reduce(*h,Q);
    iq = Q.insert(iq,h);
    if (!h1->isZero())
      ir = R.insert(ir,h1);
    ++ip;
  }
  gBasis.clear();
  gBasis = R;
}

void GBasis64::InvolutiveBasisI()
{
  list<Triple64*>::iterator qit(qSet.begin()), tit(tSet.begin());
  Poly64* h;
  bool lm_changed;

  while (!qSet.empty())
  {
    qit = qSet.end(); qit--;
    h = NormalForm(**qit);

    Monom64 qanc = (**qit).anc;

    delete *qit;
    qSet.pop_back();

    if (!h->isZero())
    {
      list<Triple64*> add_to_qSet;
      list<Triple64*>::iterator mid, add_end, add_begin;

      tit = tSet.begin();
      while (tit!=tSet.end())
        if ((*tit)->poly->lm().divisibilityTrue(h->lm()))
        //if ((*tit)->poly->lm().divisibilityPommaret(h->lm()))
        {
          qit = qSet.begin();
          Monom64 tlm = (**tit).poly->lm();
          while (qit!=qSet.end())
            if ((**qit).anc == tlm){
              delete *qit;
              qit = qSet.erase(qit);
            }
            else
              qit++;
	  add_to_qSet.push_back(*tit);
          jTree.del(*tit);
          tit = tSet.erase(tit);
        }
        else
          tit++;

      tSet.push_back(new Triple64(h,h->lm(),NULL,false));

      tit = tSet.end();
      tit--;
      jTree.insert(*tit);
      jTree.update(*tit, add_to_qSet);

      if (!add_to_qSet.empty())
      {
	add_to_qSet.sort(Compare_Triple);
        mid = qSet.end(); add_end = add_to_qSet.end(); add_begin = add_to_qSet.begin();
        do{
          add_end--;
          mid = qSet.insert(mid, *add_end);
        } while (add_end!=add_begin);
        inplace_merge(qSet.begin(), mid, qSet.end(), Compare_Triple);
        add_to_qSet.clear();
      }
    }
    else
      delete h;
  }

  jTree.clear();
}

GBasis64::GBasis64(): gBasis(), qSet(), tSet(), jTree() {}

GBasis64::GBasis64(list<Poly64*> set): gBasis(), qSet(), tSet(), jTree()
{
  list<Poly64*>::const_iterator i1(set.begin());
  list<Poly64*>::iterator i2(gBasis.begin());
  int i;

  Dim = (**i1).lm().dimIndepend();
  while (i1!=set.end())
  {
    i2=gBasis.insert(i2, new Poly64(**i1));
    /*for (i = 0; i < Dim; i++)
    {
      i2=gBasis.insert(i2, new Poly64(**i1));
      (**i2).mult(i);
    }*/
    ++i1;
  }

  ReduceSet();

  i2 = gBasis.begin();
  while (i2!=gBasis.end())
  {
    qSet.push_back(new Triple64(*i2,(*i2)->lm(),NULL,false));
    i2++;
  }
  gBasis.clear();
  qSet.sort(Compare_Triple);

  InvolutiveBasisI();

  list<Triple64*>::const_iterator i3(tSet.begin());
  while(i3!=tSet.end())
  {
    gBasis.push_back((*i3)->poly);
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


Triple64* GBasis64::find_Pdiv(const Monom64& m)
{
	Triple64* trpl = NULL;
	list<Triple64*>::iterator tit(tSet.begin());
	while (tit != tSet.end())
	{
		if (m.divisibilityPommaret((**tit).poly->lm()))
		{
			trpl = *tit;
			break;
		}
		tit++;
	}
	return trpl;
}

void GBasis64::updateQ(Triple64 *trpl)
{
  list<Triple64*> add_to_qSet;
  list<Triple64*>::iterator mid, add_end, add_begin;
  bitset<64> nonmulti = trpl->poly->Pnmv();

  for (register int var = 0; var< trpl->poly->lm().dimIndepend(); var++)
    if (nonmulti.test(var))
      {
        Poly64* tmp = new Poly64(*trpl->poly);
        tmp->mult(var);
        if (!tmp->isZero())
          add_to_qSet.push_back(new Triple64(tmp, trpl->anc, trpl, true));
	  //qSet.push_back(new Triple64(tmp, trpl->anc, trpl, true));
      }

  if (!add_to_qSet.empty())
  {
    add_to_qSet.sort(Compare_Triple);
    mid = qSet.end(); add_end = add_to_qSet.end(); add_begin = add_to_qSet.begin();
    do{
      add_end--;
      mid = qSet.insert(mid, *add_end);
    } while (add_end!=add_begin);
    inplace_merge(qSet.begin(), mid, qSet.end(), Compare_Triple);
  }
}
