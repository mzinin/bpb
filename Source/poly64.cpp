#include <cstdarg>
#include <cstring>
#include "poly64.h"

Poly64::Poly64(const Poly64& a): mHead(), len(a.len)
{
  ConstIterator ia(a.mHead);
  Iterator i(mHead);
  while(ia)
  {
    i.insert(*ia);
    ia++;
    i++;
  }
}

Poly64::Poly64(const Poly64& a, int var): mHead(), len(a.len)
{
  ConstIterator ia(a.mHead);
  Iterator i(mHead);
  while(ia)
  {
    i.insert(*ia);
    ia++;
    i++;
  }
  mult(var);
}

Poly64::Poly64(const Poly64& a, const Monom64& m): mHead(), len(a.len)
{
  ConstIterator ia(a.mHead);
  Iterator i(mHead);
  while(ia)
  {
    i.insert(*ia);
    ia++;
    i++;
  }
  mult(m);
}

void Poly64::setOne()
{
  Iterator i(mHead);
  i.clear();
  mHead = new Monom64();
  len = 1;
}

void Poly64::setZero()
{
  Iterator i(mHead);
  i.clear();
  mHead = NULL;
  len = 0;
}

void Poly64::set(const Poly64& a)
{
  Iterator i(mHead);
  i.clear();
  ConstIterator ia(a.mHead);
  while(ia)
  {
    i.insert(*ia);
    ++i;
    ++ia;
  }
  len = a.len;
}

void Poly64::swap(Poly64 &a)
{
  Monom64 *tmp;
  tmp = mHead;
  mHead = a.mHead;
  a.mHead = tmp;

  int itmp;
  itmp = len;
  len = a.len;
  a.len = itmp;
}

int Poly64::degree() const
{
  if (mHead)
    return mHead->degree();
  else
    return -100;
}

int Poly64::degree_of_monom(int i) const
{
   ConstIterator cit(mHead);
   for (int j=0; j<i; j++)
     cit++;
   return cit->degree();
}

int Poly64::deg(int var)
{
  ConstIterator i(mHead);
  int output = 0;
  while (i && !output)
  {
    if (output < i->deg(var))
      output = i->deg(var);
    ++i;
  }
  return output;
}

void Poly64::rid_of_lm()
{
  Iterator i(mHead);
  i.del();
  len--;
}

void Poly64::add(const Monom64& m)
{
  Iterator i(mHead);
  bool placed=false;
  while (i && !placed)
    switch (i->compare(m))
    {
      case 1:
        i++;
	break;
      case -1:
        i.insert(m);
	placed = true;
	len++;
	break;
      case 0:
        i.del();
	placed = true;
	len--;
	break;
    }

  if (!placed)
  {
    i.insert(m);
    len++;
  }
}

void Poly64::add(Poly64& a)
{
  Iterator i1(mHead);
  ConstIterator i2(a.mHead);
  while(i1 && i2)
    switch(i1->compare(*i2))
    {
      case 1:
        i1++;
        break;
      case -1:
        i1.insert(*i2);
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

  while(i2)
  {
    i1.insert(*i2);
    i1++;
    i2++;
    len++;
  }
}

void Poly64::add_no_copy(Poly64& a)
{
  Iterator i1(mHead);
  Iterator i2(a.mHead);
  while(i1 && i2)
    switch(i1->compare(*i2))
    {
      case 1:
        i1++;
        break;
     case -1:
        i1.insert_no_copy(i2);
        i1++;
        len++;
        break;
      case 0:
        i1.del();
        i2++;
        len--;
        break;
    }

  while(i2)
  {
    i1.insert_no_copy(i2);
    i1++;
    len++;
  }
}

void Poly64::mult(int var)
{
  if (isZero()) return; //ноль ни на что не умножаем
  Poly64 *tmp_no_x = new Poly64();
  Iterator i(mHead), i_no_x(tmp_no_x->mHead);

  while (i)
  {
    if (!i->deg(var))
    {
      i.move_to(i_no_x);
      i_no_x++;
      len--;
    }
    else
      i++;
  }

  i_no_x = tmp_no_x->begin();
  while (i_no_x)
  {
    i_no_x->prolong(var);
    i_no_x++;
  }

  add_no_copy(*tmp_no_x);
  delete tmp_no_x;
}

void Poly64::mult(int var, unsigned deg)
{
  if (var>0) mult(var);
}

void Poly64::mult(const Monom64& m)
{
  if (isZero()) return;
  for (int i=0; i<m.dimIndepend(); i++)
    if (m.deg(i))
      mult(i);
}

void Poly64::mult(const Poly64 &a)
{
  Poly64 *p = new Poly64();
  ConstIterator ia(a.mHead);
  while(ia)
  {
    Poly64 *tmp = new Poly64(*this, *ia);
    p->add_no_copy(*tmp);
    delete tmp;
    ia++;
  }
  swap(*p);
  delete p;
}

void Poly64::pow(unsigned deg)
{
//степеней-то нет
}

void Poly64::reduction(const Poly64 &a)
{
  Monom64 *m2 = new Monom64();
  Poly64 *p;

  ConstIterator j(mHead);
  while (j)
    if (j->divisibility(a.lm()))
    {
      m2->divide(*j, a.lm());
      p = new Poly64(a);
      p->mult(*m2);
      add_no_copy(*p);
      delete p;
      j.mConstIt=mHead;
    }
    else
      break;

  if (isZero())
    return;
  ConstIterator i(j);
  i++;

  while (i)
    if (i->divisibility(a.lm()))
    {
      m2->divide1(*i, a.lm());
      p = new Poly64(a);
      p->mult(*m2);
      add_no_copy(*p);
      delete p;
      i=j;
      i++;
    }
    else
    {
      i++;
      j++;
    }
}

void Poly64::Preduction(const Poly64 &a)
{
  	Monom64 *m2 = new Monom64();
  	Poly64 *p;

  	ConstIterator j(mHead);
  	while (j)
    		if (j->divisibilityPommaret(a.lm()))
    		{
      			m2->divide(*j, a.lm());
      			p = new Poly64(a);
      			p->mult(*m2);
      			add_no_copy(*p);
      			delete p;
      			j.mConstIt=mHead;
    		}
    		else
      			break;

  	if (isZero())
    		return;
  	ConstIterator i(j);
  	i++;

  	while (i)
    		if (i->divisibilityPommaret(a.lm()))
    		{
      			m2->divide1(*i, a.lm());
      			p = new Poly64(a);
      			p->mult(*m2);
      			add_no_copy(*p);
      			delete p;
      			i = j;
      			i++;
    		}
    		else
    		{
      			i++;
      			j++;
    		}
}

void Poly64::head_reduction(const Poly64 &a)
{
  	Monom64 *m2 = new Monom64();
  	Poly64 *p;

  	ConstIterator j(mHead);
  	while (j)
    		if (j->divisibility(a.lm()))
    		{
      			m2->divide(*j, a.lm());
      			p = new Poly64(a);
      			p->mult(*m2);
      			add_no_copy(*p);
      			delete p;
      			j.mConstIt = mHead;
    		}
    		else
      			break;
}

void Poly64::Phead_reduction(const Poly64 &a)
{
  	Monom64 *m2 = new Monom64();
  	Poly64 *p;

  	ConstIterator j(mHead);
  	while (j)
    		if (j->divisibilityPommaret(a.lm()))
    		{
      			m2->divide(*j, a.lm());
      			p = new Poly64(a);
      			p->mult(*m2);
      			add_no_copy(*p);
      			delete p;
      			j.mConstIt = mHead;
    		}
    		else
      			break;
}

std::ostream& operator<<(std::ostream& out, const Poly64& a)
{
  if (a.isZero())
    out << '0';
  else
  {
    Poly64::ConstIterator i(a.begin());
    if ((*i).degree())
      out << *i;
    else
      out << '1';
    ++i;
    while(i)
    {
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

void Poly64::additive(std::istream& in)
{
  multiplicative(in);
  int op = (in >> std::ws).peek();
  Poly64 tmp;
  while(op == '+' || op == '-')
  {
    in.get();
    tmp.multiplicative(in);
    add(tmp);
    op = in.peek();
  }
}

void Poly64::multiplicative(std::istream& in)
{
  unary(in);
  int op = (in >> std::ws).peek();
  Poly64 tmp;
  while(op == '*')
  {
    in.get();
    tmp.unary(in);
    mult(tmp);
    op = in.peek();
  }
}

void Poly64::unary(std::istream& in) {
  int ch = (in >> std::ws).peek();
  if (ch != '+' && ch != '-')
    power(in);
  else
  {
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

void Poly64::power(std::istream& in)
{
  bracket(in);
  int op = (in >> std::ws).peek();
  if (op == '^')
  {
    in.get();
    int deg=0;
    in >> std::ws >> deg;
    if (in.fail() || deg <= 0)
      IMESSAGE("expected 'degree > 0'");
    pow(deg);
  }
}

void Poly64::bracket(std::istream& in)
{
  int op = (in >> std::ws).peek();
  if (op == '(')
  {
    in.get();
    additive(in);
    if (in.get() != ')')
      IMESSAGE("expected ')'");
  }
  else
  {
    setOne();
    Monom64 m;
    in >> m;
    if (!in.fail())
      mult(m);
    else
    {
      in.clear();
      if (in.get() != '1')
        IMESSAGE("expected 'monomial'");
    }
  }
}

std::istream& operator>>(std::istream& in, Poly64& a)
{
  a.additive(in);
  return in;
}

bool operator==(const Poly64 &a, const Poly64 &b)
{
  if (a.len!=b.len)
    return false;

  Poly64::ConstIterator ia(a.mHead), ib(b.mHead);
  while (ia && ib)
  {
    if ( *ia != *ib )
      return false;
    ++ia;
    ++ib;
  }
  if (ia||ib)
    return false;
  return true;
}

void Poly64::assertValid(const char* fileName, int fileLine) const
{
  if (mHead)
  {
    ConstIterator i(mHead);
    IASSERT2(fileName, fileLine, i);
    ConstIterator prev(i);
    ++i;
    while(i)
    {
      IASSERT2(fileName, fileLine, i);
      IASSERT2(fileName, fileLine, (*prev).compare(*i) > 0);
      prev = i;
      ++i;
    }
  }
}
