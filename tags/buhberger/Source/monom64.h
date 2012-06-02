#ifndef MONOM64_H
#define MONOM64_H

#include <iostream>
#include <cstring>
#include "ivariables.h"
#include "iallocator.h"

using namespace std;

class Monom64 {
protected:
  unsigned long long mTotalDegree;
  unsigned long long exp;
  
  static int mDimIndepend;
  static IAllocator sAllocator;
  static unsigned long long Zero[64], One[64];
  static unsigned long long degrees[256]; 

public:
  Monom64* Next;
  static IVariables* mIndepend;
  static void Init();

  Monom64() { memset(this, 0, sizeof(Monom64)); }
  Monom64(const Monom64& a) { memcpy(this, &a, sizeof(Monom64)); }
  ~Monom64() { Next = NULL; };
  void* operator new(size_t) { return sAllocator.allocate(); }
  void operator delete(void *ptr) { sAllocator.deallocate(ptr); }

  int dimIndepend() const { return mDimIndepend; }
  unsigned deg(int var) const;
  unsigned operator[](int var) const { return deg(var); }
  unsigned degree() const;
  unsigned long long rank() const;

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
};

inline void Monom64::set(const Monom64& a) {
  memcpy(this, &a, sizeof(Monom64));
}

inline unsigned Monom64::deg(int var) const {
  if (exp & One[var]) return 1;
  return 0;
}

inline unsigned Monom64::degree() const {
  return mTotalDegree;
}

inline unsigned long long Monom64::rank() const {
    return exp;
}

inline void Monom64::setZero() {
  mTotalDegree = 0;
  exp = 0;
  //memset(this, 0, 16);
}

inline void Monom64::prolong(int var) {
  if ( !(exp & One[var]) ) {
    exp = exp | One[var];
    mTotalDegree++;
  };
}

inline void Monom64::prolong(int var, unsigned deg) {
  if (deg>0) prolong(var);
}

inline void Monom64::div(int var) {
  if ( exp & One[var] ){
    exp = exp & Zero[var];
    mTotalDegree--;
  }
  else 
   IERROR("Monom can't be divided by variable"); 
}

inline void Monom64::div(const Monom64& a) {
  exp ^= a.exp;
  unsigned char *c = (unsigned char*)&exp;
  mTotalDegree = degrees[*c];
  for (int i=0; i<7; i++){
    c++;
    mTotalDegree += degrees[*c];
  }
}

inline void Monom64::mult(const Monom64& a) {
  exp |= a.exp;
  unsigned char *c = (unsigned char*)&exp;
  mTotalDegree = degrees[*c];
  for (int i=0; i<7; i++){
    c++;
    mTotalDegree += degrees[*c];
  }
}

inline void Monom64::mult1(const Monom64& a) {
  exp|=a.exp;
}

inline void Monom64::mult(const Monom64& a, const Monom64& b) {
  exp = a.exp | b.exp;
  unsigned char *c = (unsigned char*)&exp;
  mTotalDegree = degrees[*c];
  for (int i=0; i<7; i++){
    c++;
    mTotalDegree += degrees[*c];
  }
}

inline bool Monom64::divisibility(const Monom64& a) const{
  unsigned long long d(exp ^ a.exp);
  d &= a.exp;
  if(d!=0)
    return false;
  else
    return true;
}

inline bool Monom64::divisibilityTrue(const Monom64& a) const {
  unsigned long long d(exp ^ a.exp);
  if (d==0)
    return false;
  else{
    d &= a.exp;
    if(d!=0)
      return false;
    else
      return true;
  }
}

inline void Monom64::divide(const Monom64& a, const Monom64& b) {
  mTotalDegree = a.mTotalDegree - b.mTotalDegree;
  exp = a.exp ^ b.exp;
}

inline void Monom64::divide1(const Monom64& a, const Monom64& b) {
  exp = a.exp ^ b.exp;
}

inline unsigned Monom64::gcd(const Monom64& a) const {
  unsigned long long d(exp & a.exp);
  unsigned char *c = (unsigned char*)&d;
  unsigned r = degrees[*c];
  for (int i=0; i<7; i++){
    c++;
    r += degrees[*c];
  }
  return r;
}

inline unsigned Monom64::lcm(const Monom64& a) const {
  unsigned long long d(exp | a.exp);
  unsigned char *c = (unsigned char*)&d;
  unsigned r = degrees[*c];
  for (int i=0; i<7; i++){
    c++;
    r += degrees[*c];
  }
  return r;
}

inline void Monom64::gcd(const Monom64& a, const Monom64& b) {
  exp = a.exp & b.exp;
  unsigned char *c = (unsigned char*)&exp;
  mTotalDegree = degrees[*c];
  for (int i=0; i<7; i++){
    c++;
    mTotalDegree += degrees[*c];
  }
}

inline void Monom64::lcm(const Monom64& a, const Monom64& b) {
  exp = a.exp | b.exp;
  unsigned char *c = (unsigned char*)&exp;
  mTotalDegree = degrees[*c];
  for (int i=0; i<7; i++){
    c++;
    mTotalDegree += degrees[*c];
  }
}

inline bool Monom64::equality(const Monom64& a, int var, unsigned degree) const {
  unsigned long long d(1);
  d = d<<var;
  d |= a.exp;
  return exp==d; 
}

inline int Monom64::compare(const Monom64& a) const {
  if (mTotalDegree < a.mTotalDegree)
    return -1;
  else if (mTotalDegree > a.mTotalDegree)
    return 1;
  else {
    if (exp < a.exp)
      return 1;
    else if (exp > a.exp)
      return -1;
    else
      return 0;
  }
}

inline bool operator==(const Monom64 &a, const Monom64 &b){
  return a.exp==b.exp;
}

#endif // MONOM64_H
