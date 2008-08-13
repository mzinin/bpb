#include <list>
#include <algorithm>
#include "tset.h"
#include "qset.h"

class GBasis64
{
protected:
  	int Dim;
  	list<Poly64*> gBasis;
  	TSET tSet;
	QSET qSet;

  	Poly64* findR(Poly64 *p, list<Poly64*> &Q);
  	Poly64* Reduce(Poly64 *p, list<Poly64*> &Q);
  	void AutoReduce();

 	void InvolutiveBasis();

public:
  	GBasis64();
  	GBasis64(list<Poly64*> set);
  	~GBasis64() {}

  	Poly64* operator[](int num);
  	int length();
  	//Triple64* NormalForm(Triple64 *p);

  	friend std::ostream& operator<<(std::ostream& out, GBasis64& GBasis);
};
