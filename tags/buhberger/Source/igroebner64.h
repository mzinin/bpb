#include <vector>
#include <algorithm>
#include "poly64.h"

struct Pair {
  short int i, j, degree;
  unsigned long lcm;
  static IAllocator sAllocator;
  
  Pair() {}
  Pair(int i_new, int j_new, unsigned lcm_new, int deg_new){
    i = i_new; j = j_new; lcm = lcm_new; degree = deg_new;
  }
  ~Pair() {}

  void* operator new(size_t) { return sAllocator.allocate(); }
  void operator delete(void *ptr) { sAllocator.deallocate(ptr); }
};

Poly64* findR(Poly64& p, vector<Poly64*> &Q);
Poly64* Reduce(Poly64& p, vector<Poly64*> &Q);

class IGBasis64{
protected:
  vector<Poly64*> basis;
  int Dim;
  vector< vector<bool> > all_pairs;
  vector<Pair*> ref_to_pairs;

  bool criterion1(int i, int j, unsigned long &lcm, int &degree);
  bool criterion2(int i, int j);
  void push_poly(Poly64* p, int flag);
  void CalculateGB();

public:
  IGBasis64(): basis() {};
  IGBasis64(vector<Poly64*> &set);
  ~IGBasis64() {}
  
  Poly64* operator[](int num);
  Poly64* S(int i,int j);
  void SelectPair(int& i, int& j);
  int length();
  void ReduceSet(int i);

  friend std::ostream& operator<<(std::ostream& out, IGBasis64& GBasis);
};

inline Poly64* IGBasis64::operator[](int num){
  vector<Poly64*>::const_iterator it(basis.begin());
  it+=length()-1-num;
  return *it;
}

inline void IGBasis64::SelectPair(int& i, int& j){
  vector<Pair*>::iterator p_iterator = ref_to_pairs.end();
  p_iterator--;
  i = (*p_iterator)->i;
  j = (*p_iterator)->j;
  ref_to_pairs.pop_back();
  return;
}

inline int IGBasis64::length(){
  return basis.size();
} 
