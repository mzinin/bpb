#include <list>
#include <algorithm>
#include "janettree64.h"

class GBasis64{
protected:
  int Dim;
  list<Poly64*> gBasis;
  list<Triple64*> qSet, tSet;
  JanetTree64 jTree;

  bool Criteria1(Triple64 &p, Triple64 &g);
  bool Criteria2(Triple64 &p, Triple64 &g);
  bool Criteria3(Triple64 &p, Triple64 &g);
  bool Criteria4(Triple64 &p, Triple64 &g);

  Poly64* findR(Poly64& p, list<Poly64*> &Q);
  Poly64* Reduce(Poly64 &p, list<Poly64*> &Q);
  void ReduceSet();
  void InvolutiveBasisI();

public:
  GBasis64();
  GBasis64(list<Poly64*> set);
  ~GBasis64() {}

  Poly64* operator[](int num);
  int length();
  Poly64* NormalForm(Triple64 &p);

  friend std::ostream& operator<<(std::ostream& out, GBasis64& GBasis);

  Triple64* find_Pdiv(const Monom64& m);
  void updateQ(Triple64* trpl);
};
