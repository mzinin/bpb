#include <iostream>
#include "igroebner64.h"
#include "timer.h"

using namespace std;

int Compare_ref_to_Pair(Pair* a,  Pair* b){
  if (a->degree!=b->degree)
    if (a->degree<b->degree)
      return 0;
    else
      return 1;
  else if(a->lcm!=b->lcm)
    if (a->lcm>b->lcm)
      return 0;
    else
      return 1;
  else if (a->i<b->i)
         return 0;
       else
         return 1;
}

Poly64* IGBasis64::S(int i, int j){
  if (i<Dim){
    Poly64 *r1 = new Poly64(*(*this)[j-Dim]);
    r1->mult(i);
    return r1;
  }
  else{
    Monom64 *w = new Monom64();
    Poly64 *f,*g;
    f = (*this)[i-Dim];
    g = (*this)[j-Dim];
    w->gcd(f->lm(),g->lm());
  
    Monom64 *q1 = new Monom64(), *q2 = new Monom64();
    q1->divide(f->lm(),*w);
    q2->divide(g->lm(),*w);
    delete w;
  
    Poly64 *r1 = new Poly64(*f),
           *r2 = new Poly64(*g);
    r1->mult(*q2); delete q2;
    r2->mult(*q1); delete q1;
    r1->add(*r2); delete r2;
  
    return r1;
  }
}

Poly64* findR(Poly64& p, vector<Poly64*> &Q){
  if (p.isZero()) return NULL;
  vector<Poly64*>::const_iterator iq(Q.begin()), q_end(Q.end());
  Monom64 *plm = (Monom64*)&p.lm();
    
  while (iq!=q_end){
    if ( plm->divisibility((**iq).lm()) ) 
      return *iq;
    iq++;
  }
  return NULL;
}

Poly64* Reduce(Poly64 &p, vector<Poly64*> &Q){
  Poly64 *r,*q;
  Poly64 *red;
  q = new Poly64();
  //q->setZero();
  r = new Poly64(p);
  if (Q.empty()) return r;
  vector<Poly64*> rrq;
  vector<Poly64*>::iterator it;

  while (!r->isZero()){
    red = findR(*r,Q);
    while (red){
      r->head_reduction(*red);
      red = findR(*r,Q);
    }
    if (!r->isZero()){
      q->add(r->lm());
      r->rid_of_lm();
    }
  }

  delete r;
  return q;
}

void IGBasis64::ReduceSet(int i) {
  vector<Poly64*> R,P,Q;
  vector<Poly64*>::iterator ir(R.begin()), ip(P.begin()), iq(Q.begin());
  vector<Poly64*>::const_iterator j(basis.begin()), q_end, r_end, p_end;
  Poly64 *h,*h1;
  if (i)
    while (j!=basis.end()){
      ir=R.insert(ir,*j);
      ++j;
    }
  else
    R = basis;

  int num;
  
  while (!R.empty()){
    ir = R.begin();
    h = *ir;
    ir = R.erase(ir);
    h = Reduce(*h,P);
    if (!h->isZero()){
      Monom64 *hlm=(Monom64*)&h->lm();
      ip = P.begin();
      p_end = P.end(); 
      while (ip!=p_end){//P.end()){
        if ((**ip).lm().divisibility(*hlm))
          iq=Q.insert(iq,*ip);
	++ip;
      }
      //R = R U Q
      iq = Q.begin();
      q_end = Q.end();
      while (iq!=q_end){
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
      while (ip!=P.end()) {
        iq = Q.begin();
        q_end = Q.end();
        while (iq!=q_end && (**iq)!=(**ip))
	  ++iq;
        if (iq!=q_end) ip=P.erase(ip);
	else ++ip;
      }
      ip=P.insert(ip,h);
    }
  }
  
  R.clear(); 
  Q.clear(); 
  ir = R.begin();
  iq = Q.begin();
  ip = P.begin();
  p_end = P.end();
  while (ip!=p_end){
    iq=Q.insert(iq,*ip);
    ++ip;
  }
  ip = P.begin();
  while (ip!=p_end){
    h = *ip;
    iq = Q.begin();
    while ((*h)!=(**iq)) ++iq;
    iq=Q.erase(iq);
    h1 = Reduce(*h,Q);
    iq=Q.insert(iq,h);
    if (!h1->isZero())
      ir=R.insert(ir,h1);
    ++ip;
  }
  basis.clear();
  basis = R;
}

bool IGBasis64::criterion1(int i, int j, unsigned long &lcm, int &degree){
  Poly64 *f,*g;
  if (i<Dim)
    if (j<Dim)
      return false;
    else{
      g = (*this)[j-Dim];
      if (!g->lm().deg(i))
        return false;
      //lcm = g->lm().rank();
      lcm = 1; lcm = lcm << i;
      lcm |= g->lm().rank();
      degree = g->lm().degree() + 1;
      return true;
    }
  else{
    f = (*this)[i-Dim];
    g = (*this)[j-Dim];

    if ( !f->lm().gcd(g->lm()) ){
      return false;
    }  
    else{
      Monom64 *lcm_monom = new Monom64();
      lcm_monom->lcm(f->lm(),g->lm());
      lcm = lcm_monom->rank();
      degree = lcm_monom->degree();
      delete lcm_monom;
      return true;
    }
  }
}

bool IGBasis64::criterion2(int i, int j){
  vector<bool> *ilist(&all_pairs[i]), *jlist=(&all_pairs[j]);
  vector<bool>::const_iterator iit((*ilist).end()), jit((*jlist).end());
  int k,len=length();
  Poly64 *tmp;
  Monom64 *lcm_monom = new Monom64( (*this)[j-Dim]->lm() );
  if (i>=Dim)
    lcm_monom->mult((*this)[i-Dim]->lm());
  
  for (k=len+Dim-1; k>=Dim; k--){
    iit--;
    jit--;
    if (!(*iit) && !(*jit) && k!=i && k!=j){
      tmp = (*this)[k-Dim];
      if (lcm_monom->divisibility(tmp->lm()))
	return false;
    }  
  }
  //delete lcm_monom;
  return true; 
}

vector<Pair*>::iterator p_iterator;
vector<Pair*>::const_iterator p_end;

void ShowPairs(vector<Pair*>& plist){
  p_iterator = plist.begin();
  while (p_iterator!=plist.end()){
    cout<<'('<<(*p_iterator)->i<<','<<(*p_iterator)->j<<") ";
    p_iterator++;
  }
  cout<<endl<<endl;
}

void IGBasis64::push_poly(Poly64* p, int flag){
  int inum, jnum, k = length() + Dim, degree;
  unsigned long lcm;
  vector<Poly64*>::iterator basisIt(basis.begin());
  vector<Pair*>::iterator mid, add_end, add_begin;

  basisIt=basis.insert(basisIt, p);

  vector<bool> add_to_all_pairs;
  vector<Pair*> add_to_pairs;
  all_pairs.push_back(add_to_all_pairs);

  for (inum=0;inum<k;inum++)
    if (criterion1(inum,k,lcm,degree)){
      Pair *tmpPair = new Pair(inum,k,lcm,degree);
      add_to_pairs.push_back(tmpPair);
      all_pairs[inum].push_back(true);
      all_pairs[k].push_back(true);
    }  
    else{
      all_pairs[inum].push_back(false);
      all_pairs[k].push_back(false);
    }

  all_pairs[k].push_back(false);

  if (!add_to_pairs.empty()){
    mid = ref_to_pairs.end(); add_end = add_to_pairs.end(); add_begin = add_to_pairs.begin();
    sort(add_begin,add_end,Compare_ref_to_Pair);
    add_end--;
    do{
      mid = ref_to_pairs.insert(mid, *add_end);
      add_end--;
    } while (add_end!=add_begin);
    inplace_merge(ref_to_pairs.begin(), mid, ref_to_pairs.end(), Compare_ref_to_Pair);
  }
}

void IGBasis64::CalculateGB(){
  int k = length() + Dim, inum, jnum, degree;
  unsigned long lcm;
  Poly64 *h, *spoly;
  
  for (inum=0; inum<k; inum++){
    vector<bool> k1;
    all_pairs.push_back(k1);
    for (jnum=0; jnum<k; jnum++)
      all_pairs[inum].push_back(false);
  }  

  for (inum=0; inum<k; inum++)
  for (jnum=inum+1; jnum<k; jnum++)
      if (criterion1(inum,jnum,lcm,degree)){
	Pair *tmpPair = new Pair(inum, jnum, lcm, degree);
	ref_to_pairs.push_back(tmpPair);
	all_pairs[inum][jnum]=true;
	all_pairs[jnum][inum]=true;
      }

  sort(ref_to_pairs.begin(),ref_to_pairs.end(),Compare_ref_to_Pair);

  while (!ref_to_pairs.empty()){
    SelectPair(inum,jnum);
    all_pairs[inum][jnum]=false;
    all_pairs[jnum][inum]=false;

    if (criterion2(inum,jnum)){
      spoly = S(inum,jnum); 
      h = Reduce(*spoly,basis);
      delete spoly;

      if (!h->isZero()) 
        push_poly(h,1);
      else
        delete h;
    }
  }
}

IGBasis64::IGBasis64(vector<Poly64*> &set): basis()  {
  vector<Poly64*>::const_iterator i1(set.begin());
  vector<Poly64*>::iterator i2(basis.begin());

  Dim = (**i1).lm().dimIndepend();
  int i, j;

  while (i1!=set.end()){
    i2=basis.insert(i2, new Poly64(**i1));
    for (i = 0; i < Dim; i++){
      i2=basis.insert(i2, new Poly64(**i1));
      (**i2).mult(i);
    }
    ++i1;
  }

  ReduceSet(0);
  CalculateGB();
  ReduceSet(0);
}

std::ostream& operator<<(std::ostream& out, IGBasis64& GBasis) {
  int i=0;
  for (i=0;i<GBasis.length();i++)
    out<<'['<<i<<"] = "<<*GBasis[i]<<'\n';
  
  return out;
} 

IAllocator Pair::sAllocator(sizeof(Pair));
