#include <cstdarg>
#include <cstring>
#include "imypoly64.h"

IMyPolyInterface64::IMyPolyInterface64():
    mMonomInterface(NULL){
}

IMyPolyInterface64* IMyPolyInterface64::create(IMyMonomInterface64* monomInterface) {
  if (monomInterface == NULL)
    IERROR("error in IPolyInterface: monomInterface == NULL");
  IMyPolyInterface64* r = new IMyPolyInterface64;
  if (r) 
    r->mMonomInterface = monomInterface;
  return r;
}

IMyPoly64* IMyPolyInterface64::create() {
  return new IMyPoly64(this);
}

IMyPoly64* IMyPolyInterface64::copy(const IMyPoly64& a) {
  //IASSERT(this == a.polyInterface());
  return new IMyPoly64(a);
}

IMyPoly64* IMyPolyInterface64::copy(const IMyPoly64& a, int var) {
  //IASSERT(this == a.polyInterface());
  return new IMyPoly64(a, var);
}

IMyPoly64::IMyPoly64(IMyPolyInterface64* r):
   mRealization(r),
   mHead() {
   len=0;
  //IASSERT(mRealization);
  }

IMyPoly64::IMyPoly64(const IMyPoly64& a):
    mRealization(a.mRealization),
    mHead() {
  //IASSERT(mRealization);
  ConstIterator ia(a.mHead);
  Iterator i(mHead);
  while(ia) {
    i.insert(*monomInterface()->copy(*ia));
    ia++;
    i++;
  }
  len = a.len;
  //IASSERTVALID(*this);
} 
  
IMyPoly64::IMyPoly64(const IMyPoly64& a, int var):
    mRealization(a.mRealization),
    mHead() {
  //IASSERT(mRealization);
  ConstIterator ia(a.mHead);
  Iterator i(mHead);
  while(ia) {
    i.insert(*monomInterface()->copy(*ia));
    ia++;
    i++;
  }
  len =a.len;
  mult(var);
  //IASSERTVALID(*this);
}

IMyPoly64::IMyPoly64(const IMyPoly64& a, const IMyMonom64& m):
    mRealization(a.mRealization),
    mHead() {
  //IASSERT(mRealization);
  ConstIterator ia(a.mHead);
  Iterator i(mHead);
  while(ia) {
    i.insert(*monomInterface()->copy(*ia));
    ia++;
    i++;
  }
  len = a.len;
  mult(m);
  //IASSERTVALID(*this);
} 

void IMyPoly64::setOne() {
  Iterator i(mHead);
  i.clear();
  mHead = monomInterface()->create();
  mHead->setZero();
  mHead->Next = NULL;
  len =1;
}

void IMyPoly64::setZero() {
  Iterator i(mHead);
  i.clear();
  mHead = NULL;
  len = 0;
}

void IMyPoly64::set(const IMyPoly64& a) {
  //IASSERT(polyInterface() == a.polyInterface());
  Iterator i(mHead);
  i.clear();
  ConstIterator ia(a.mHead);
  while(ia) {
    i.insert(*monomInterface()->copy(*ia));
    ++i;
    ++ia;
  }
  len = a.len;
  //IASSERTVALID(*this);
}

void IMyPoly64::swap(IMyPoly64 &a) {
  //IASSERT(polyInterface() == a.polyInterface());
  IMyMonom64 *tmp;
  tmp = mHead;
  mHead = a.mHead;
  a.mHead = tmp;
  
  int itmp;
  itmp = len;
  len = a.len;
  a.len = itmp;
}

int IMyPoly64::degree() const {
  if (mHead)
    return mHead->degree();
  else
    return -100;
}

int IMyPoly64::degree_of_monom(int i) const {
   ConstIterator cit(mHead);
   for (int j=0; j<i; j++)
     cit++;
   return cit->degree();
}

int IMyPoly64::deg(int var){
  //IASSERT(0 <= var && var < monomInterface()->dimIndepend());
  ConstIterator i(mHead);
  int output = 0;
  while (i && !output){
    if (output < i->deg(var)) output = i->deg(var);
    ++i;
  }
  return output;
}

void IMyPoly64::rid_of_lm(){
  Iterator i(mHead);
  i.del();
  len--;
}

void IMyPoly64::add(const IMyMonom64& m){
  Iterator i(mHead);
  bool placed=false;
  while (i && !placed)
    switch (i->compare(m)) {
      case 1:
        i++;
	break;
      case -1:
        i.insert(*monomInterface()->copy(m));
	placed = true;
	len++;
	break;
      case 0:
        i.del();
	placed = true;
	len--;
	break;
    }
  
  if (!placed){
    i.insert(*monomInterface()->copy(m));
    len++;
  }  
}

void IMyPoly64::add(IMyPoly64& a) {
  //IASSERT(polyInterface() == a.polyInterface());
  Iterator i1(mHead);
  ConstIterator i2(a.mHead);
  while(i1 && i2)
    switch(i1->compare(*i2)) {
    case 1:
      i1++;
      break;
    case -1:
      i1.insert(*monomInterface()->copy(*i2));
      i2++;
      i1++;
      len++;
      break;
    case 0:
      i1.del();
      i2++;
      len--;
      break;
    }

  while(i2){ 
    i1.insert(*monomInterface()->copy(*i2));
    i1++;
    i2++;
    len++;
  }
  //IASSERTVALID(*this); 
}

void IMyPoly64::mult(int var){
  if (isZero()) return;
  IMyPoly64 *tmp_no_x;
  tmp_no_x = mRealization->create();
  Iterator i(mHead), i_no_x(tmp_no_x->mHead);

  while (i){
    if (!i->deg(var)){
      i.move_to(i_no_x);
      i_no_x++;
      len--;
    }
    else
      i++;
  }

  i_no_x = tmp_no_x->begin();
  while (i_no_x){
    i_no_x->prolong(var);
    i_no_x++;
  }

  add(*tmp_no_x);
  delete tmp_no_x;
}

void IMyPoly64::mult(int var, unsigned deg) {
  if (var>0) mult(var);
  //IASSERTVALID(*this);
}

void IMyPoly64::mult(const IMyMonom64& m) { 
  if (isZero()) return;
  for (int i=0; i<m.dimIndepend(); i++)
    if (m.deg(i))
      mult(i);
}
/*
void IMyPoly64::mult(const IMyMonom64& m) {
  if (isZero()) return; //�� �����0, ���� ����  
  Iterator i(mHead), itmp, i_minus;
  i->mult(m); //���������� ����� � ���  
  i++;
  bool moved;
  i_minus = begin();
  
  while (i) {
    i->mult(m);
    if (i!=i_minus)
      switch (i->compare(*i_minus)){
      case -1:
        i++;
	i_minus++;
	break;
      case 0:
        i.del();
	i_minus.del();
	len-=2;
	i = i_minus;
	if (*i.mIt!=mHead){
	  i_minus=begin();
	  while (i_minus->Next!=*i.mIt)
	    i_minus++;
	}
        break;
	
      case 1:
      moved = false;
      itmp = begin(); //��� ���� �� ����� ����      
      while (itmp!=i && !moved) {
        moved = false;
	switch(itmp->compare(*i)) {
        case 1:  //�� ������� ������ ��������
          itmp++;
	  break;
        case -1: //�� ������� ������ ��������
	  if (itmp!=i_minus)
            itmp.insert(i.get());
	  else{
	    i_minus.insert(i.get());
	    i_minus++;
	  }
	  moved = true;
	  break;
        case 0:  //�� �������� ������
          i.del();
	  len-=2;
	  if (itmp->Next!=*i_minus.mIt)
            itmp.del();
          else{
            itmp.del();
            i_minus = itmp;
          }  
	  moved = true;
	  break;
        }
      }
      if (!moved) i++;
      break;    
    }
    else
     i++;
  }
}
*/
void IMyPoly64::mult(const IMyPoly64 &a) {
  //IASSERT(polyInterface() == a.polyInterface());
  IMyPoly64 *p = new IMyPoly64(polyInterface());
  ConstIt ia(a.mHead);
  while(ia) {
    IMyPoly64 *tmp = new IMyPoly64(*this, *ia);
    p->add(*tmp);
    delete tmp;
    ia++;
    //IASSERTVALID(*p);
  }
  swap(*p);
  delete p;
  //IASSERTVALID(*this); 
}

void IMyPoly64::pow(unsigned deg) {
//����-� �� ��������� � ���
}

void IMyPoly64::reduction(const IMyPoly64 &a) {
  //IASSERT(polyInterface() == a.polyInterface());
  IMyMonom64 *m2(monomInterface()->create());
  IMyPoly64 *p;
  
  ConstIterator j(mHead);
  while (j)
    if (j->divisibility(a.lm())){
      m2->divide(*j, a.lm());
      p = new IMyPoly64(a);
      p->mult(*m2); 
      add(*p); delete p;
      j.mConstIt=mHead;
    }
    else
      break;
  
  if (isZero())    
    return;
  ConstIterator i(j);
  i++;
  
  while (i) 
    if (i->divisibility(a.lm())){
      m2->divide1(*i, a.lm());
      p = new IMyPoly64(a);
      p->mult(*m2); 
      add(*p); delete p;
      i=j;
      i++;
    }
    else{
      i++;
      j++;
    }  
}

void IMyPoly64::reduction1(const IMyPoly64 &a) {
  IMyMonom64 *m2(monomInterface()->create());
  IMyPoly64 *p;
  
  ConstIterator j(mHead);
  while (j)
    if (j->divisibility(a.lm())){
      m2->divide(*j, a.lm());
      p = new IMyPoly64(a);
      p->mult(*m2); 
      add(*p); delete p;
      j.mConstIt=mHead;
    }
    else
      break;
}

IMyPoly64::ConstIterator IMyPoly64::begin() const {
  //return ConstIterator(mHead);
  return mHead;
}

IMyPoly64::Iterator IMyPoly64::begin() {
  //return Iterator(mHead);
  return mHead;
}

std::ostream& operator<<(std::ostream& out, const IMyPoly64& a) {
  if (a.isZero())
    out << '0';
  else {
    IMyPoly64::ConstIterator i(a.begin());
    if ((*i).degree())
      out << *i;
    else
      out << '1';
    ++i;
    while(i) {
      out << " + ";
      if ((*i).degree())
        out << *i;
      else
        out << '1';
      ++i;
    }
  }
  return out;
}

void IMyPoly64::additive(std::istream& in) {
  multiplicative(in);
  int op = (in >> std::ws).peek();
  IMyPoly64 tmp(polyInterface());
  while(op == '+' || op == '-') {
    in.get();
    tmp.multiplicative(in);
    add(tmp);
    op = in.peek();
  }
}

void IMyPoly64::multiplicative(std::istream& in) {
  unary(in);
  int op = (in >> std::ws).peek();
  IMyPoly64 tmp(polyInterface());
  while(op == '*') {
    in.get();
    tmp.unary(in);
    mult(tmp);
    op = in.peek();
  }
}

void IMyPoly64::unary(std::istream& in) {
  int ch = (in >> std::ws).peek();
  if (ch != '+' && ch != '-') 
    power(in);
  else {
    int k = 1;  
    do {
      ch = in.get();
      if (ch == '-')
        k *= -1;
      ch = (in >> std::ws).peek();
    } while (ch == '+' || ch == '-');
    power(in);
  }  
}

void IMyPoly64::power(std::istream& in) {
  bracket(in);
  int op = (in >> std::ws).peek();
  if (op == '^') {
    in.get();
    int deg=0;
    in >> std::ws >> deg;
    if (in.fail() || deg <= 0)
      IMESSAGE("expected 'degree > 0'");
    pow(deg);
  }
}

void IMyPoly64::bracket(std::istream& in) {
  int op = (in >> std::ws).peek();
  if (op == '(') {
    in.get();
    additive(in);
    if (in.get() != ')') {
      IMESSAGE("expected ')'");
    }
  }
  else {
    setOne();
    IMyMonom64 *m(monomInterface()->create());
    in >> (*m);
    if (!in.fail())
      mult(*m);
    else {
      in.clear();
      if (in.get() != '1') { IMESSAGE("expected 'monomial'"); };
    }
    delete m;
    //IASSERTVALID(*this);
  }
}

std::istream& operator>>(std::istream& in, IMyPoly64& a) {
  a.additive(in);
  return in;
}

bool operator==(const IMyPoly64 &a, const IMyPoly64 &b){
  if (a.polyInterface() != b.polyInterface())
    return false;
  if (a.len!=b.len)
    return false;
    
  IMyPoly64::ConstIterator ia(a.mHead), ib(b.mHead);
  while (ia && ib){
    if ( *ia != *ib )
      return false;
    ++ia;
    ++ib;
  }
  if (ia||ib)
    return false;
  return true;
}

void IMyPoly64::RawCopy(IMyPoly64 &a){
  setZero();
  IMyPoly64 *tmp = polyInterface()->create();
  int dim = a.polyInterface()->monomInterface()->dimIndepend(),var,len=a.length(),j,k;

  for (j=len-1;j>=0;j--){
    ConstIterator i(a.mHead);
    tmp->setOne();
    for (k=0;k<j;k++) i++;
    
    for (var=0;var<dim;var++)
      if ((*i).deg(var)) 
        tmp->mult(var);
    
    add(*tmp);
  }
}

void IMyPoly64::assertValid(const char* fileName, int fileLine) const {
  if (mHead) {
    ConstIterator i(mHead);
    IASSERT2(fileName, fileLine, i);
    ConstIterator prev(i);
    ++i;
    while(i) {
      IASSERT2(fileName, fileLine, i);
      IASSERT2(fileName, fileLine, (*prev).compare(*i) > 0);
      prev = i;
      ++i;
    }
  }
}

IMyPoly64* IMyPoly64::deriv1(){
  Iterator i(mHead);
  i++;
  if (!lm().divisibility(*i))
    return NULL;
  else {
    IMyPoly64 *deriv = mRealization->copy(*this);
    IMyMonom64 *m(monomInterface()->create());
    m->divide(lm(), *i);
    deriv->mult(*m);
    delete m;
    return deriv;
  }
}

IMyPoly64* IMyPoly64::deriv2(){ 
  Iterator i(mHead);
  i++; i++;
  if (!lm().divisibility(*i))
    return NULL;
  else {
    IMyPoly64 *deriv = mRealization->copy(*this);
    IMyMonom64 *m(monomInterface()->create());
    m->divide(lm(), *i);
    deriv->mult(*m);
    delete m;
    return deriv;
  }
}
