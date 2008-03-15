#include <cstdarg>
//#include <cmath>
#include "util.h"
#include "monom64.h"

void Monom64::Init()
{
  mDimIndepend = mIndepend->dim();
}

int Monom64::compare(const Monom64& a, const Monom64& b) const
{
  Monom64 tmp(a);
  tmp.mult(b);
  return compare(tmp);
}

std::istream& operator>>(std::istream& in, Monom64& a)
{
  std::streampos posbeg = in.tellg();
  int var = a.independ()->read(in);
  if (var < 0)
  {
    in.clear();
    in.setstate(std::ios::failbit);
  }
  else
  {
    a.setZero();
    int deg;
    do
    {
      deg = 1;
      std::streampos posbeg = in.tellg();
      if ((in >> std::ws).peek() == '^')
      {
        in.get();
        in >> std::ws >> deg;
        if (in.fail() || deg < 0)
        {
          in.setstate(std::ios::failbit);
          IMESSAGE("expected 'degree >= 0'");
        }
      }
      a.prolong(var,deg);

      posbeg = in.tellg();
      if (in.peek() != '*')
        var = -1;
      else
      {
        in.get();
        var = a.independ()->read(in);
        if (var < 0)
        {
          in.clear();
          in.seekg(posbeg);
        }
      }
    } while(var >= 0);
    if (in.eof() &&
        deg >= 0)
      in.clear();
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const Monom64& a)
{
  if (a.degree() == 0)
    out << '1';
  else
  {
    int i = 0;
    Variables::ConstIterator j(a.independ()->begin());
    while(a.deg(i) == 0)
    {
      ++i;
      ++j;
    }
    out << *j;
    if (a.deg(i) > 1)
      out << '^' << a[i];
    ++i;
    ++j;
    while(j!=a.independ()->end())
    {
      if (a.deg(i))
      {
        out << '*' << *j;
        if (a.deg(i) > 1)
          out << '^' << a[i];
      }
      ++i;
      ++j;
    }
  }
  return out;
}

Variables* Monom64::mIndepend = new Variables();
Allocator Monom64::sAllocator(sizeof(Monom64));
int Monom64::mDimIndepend;
