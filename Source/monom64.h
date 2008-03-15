#include <iostream>
#include <bitset>
#include "variables.h"
#include "allocator.h"

#ifndef MONOM64_H
#define MONOM64_H

using namespace std;

class Monom64 {
protected:
  unsigned mTotalDegree;
  bitset<64> exp;

  static int mDimIndepend;
  static Allocator sAllocator;

public:
  static Variables* mIndepend;
  Monom64 *Next;
  static void Init();

  Monom64() { memset(this, 0, sizeof(Monom64)); }
  Monom64(const Monom64& a) { memcpy(this, &a, sizeof(Monom64)); }
  ~Monom64() { Next = NULL; };
  void* operator new(size_t) { return sAllocator.allocate(); }
  void operator delete(void *ptr) { sAllocator.deallocate(ptr); }

  int dimIndepend() const { return mDimIndepend; }
  const Variables* independ() const { return mIndepend; }
  unsigned deg(int var) const;
  unsigned operator[](int var) const { return deg(var); }
  unsigned degree() const;

  void set(const Monom64& a);
  void operator=(const Monom64& a) { set(a); }

  void setZero();
  void prolong(int var);
  void prolong(int var, unsigned deg);
  void div(int var);
  void div(const Monom64& a);

  void mult(const Monom64& a);
  void mult1(const Monom64& a);
  void mult(const Monom64& a, const Monom64& b);

  bool divisibility(const Monom64& a) const;
  bool divisibilityTrue(const Monom64& a) const;
  void divide(const Monom64& a, const Monom64& b);
  void divide1(const Monom64& a, const Monom64& b);

  unsigned gcd(const Monom64& a) const;
  unsigned lcm(const Monom64& a) const;
  void gcd(const Monom64& a, const Monom64& b);
  void lcm(const Monom64& a, const Monom64& b);

  bool equality(const Monom64& a, int var, unsigned degree=1) const;
  int compare(const Monom64& a) const;
  int compare(const Monom64& a, const Monom64& b) const;

  friend std::istream& operator>>(std::istream& in, Monom64& a);
  friend std::ostream& operator<<(std::ostream& out, const Monom64& a);
  friend bool operator==(const Monom64 &a, const Monom64 &b);
  friend bool operator!=(const Monom64 &a, const Monom64 &b) { return !(a==b); };

  bitset<64> Pnmv() const;
};

inline void Monom64::set(const Monom64& a)
{
  memcpy(this, &a, sizeof(Monom64));
}

inline unsigned Monom64::deg(int var) const
{
  return exp.test(var);
}

inline unsigned Monom64::degree() const
{
  return mTotalDegree;
}

inline void Monom64::setZero()
{
  mTotalDegree=0;
  exp = 0;
}

inline void Monom64::prolong(int var)
{
  if ( !exp.test(var) )
  {
    exp.set(var);
    mTotalDegree++;
  };
}

inline void Monom64::prolong(int var, unsigned deg)
{
  if (deg>0) prolong(var);
}

inline void Monom64::div(int var)
{
  if ( exp.test(var) )
  {
    exp.reset(var);
    mTotalDegree--;
  }
  else
   IERROR("Monom can't be divided by variable");
}

inline void Monom64::div(const Monom64& a)
{
  exp ^= a.exp;
  mTotalDegree += exp.count();
}

inline void Monom64::mult(const Monom64& a)
{
  exp |= a.exp;
  mTotalDegree = exp.count();
}

inline void Monom64::mult1(const Monom64& a)
{
  exp |= a.exp;
}

inline void Monom64::mult(const Monom64& a, const Monom64& b)
{
  exp = a.exp | b.exp;
  mTotalDegree = exp.count();
}

inline bool Monom64::divisibility(const Monom64& a) const
{
  bitset<64> d(exp ^ a.exp);
  d &= a.exp;
  if(d!=0)
    return false;
  else
    return true;
}

inline bool Monom64::divisibilityTrue(const Monom64& a) const
{
  bitset<64> d(exp ^ a.exp);
  if (d==0)
    return false;
  else
  {
    d &= a.exp;
    if(d!=0)
      return false;
    else
      return true;
  }
}

inline void Monom64::divide(const Monom64& a, const Monom64& b)
{
  mTotalDegree = a.mTotalDegree - b.mTotalDegree;
  exp = a.exp ^ b.exp;
}

inline void Monom64::divide1(const Monom64& a, const Monom64& b)
{
  exp = a.exp ^ b.exp;
}

inline unsigned Monom64::gcd(const Monom64& a) const
{
  bitset<64> d(exp & a.exp);
  //d = exp & a.exp;
  return d.count();
}

inline unsigned Monom64::lcm(const Monom64& a) const
{
  bitset<64> d(exp | a.exp);
  //d = exp | a.exp;
  return d.count();
}

inline void Monom64::gcd(const Monom64& a, const Monom64& b)
{
  exp = a.exp & b.exp;
  mTotalDegree = exp.count();
}

inline void Monom64::lcm(const Monom64& a, const Monom64& b)
{
  exp = a.exp | b.exp;
  mTotalDegree = exp.count();
}

inline bool Monom64::equality(const Monom64& a, int var, unsigned degree) const
{
  bitset<64> d(1);
  d = d<<var;
  d |= a.exp;
  return exp==d;
}

inline int Monom64::compare(const Monom64& a) const
{
  if (mTotalDegree < a.mTotalDegree)
    return -1;
  else if (mTotalDegree > a.mTotalDegree)
    return 1;
  else
  {
    unsigned long *exp_int = (unsigned long*)&exp;
    unsigned long *exp_int_a = (unsigned long*)&a.exp;
    if (*exp_int < *exp_int_a)
      return 1;
    else if (*exp_int > *exp_int_a)
      return -1;
    else
      return 0;
  }
}

inline bool operator==(const Monom64 &a, const Monom64 &b)
{
  return a.exp == b.exp;
}

inline bitset<64> Monom64::Pnmv() const
{
  bitset<64> out = 0;
  int i = mDimIndepend - 1;
  //while (!exp.test(i) && i-- > 0);
  //for (register int j=0; j<i; j++) out.set(j);
  while (i>=0 && !exp.test(i)) i--;
  for (int j=0; j<i; j++) out.set(j);
  return out;
}

#endif // MONOM64_H
