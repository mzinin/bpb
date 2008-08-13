#ifndef TRIPLE64_H
#define TRIPLE64_H

#include "poly64.h"

class Triple64
{
	bitset<64> nmp;
  	Poly64*  poly;
  	static Allocator sAllocator;

public:
	Triple64(Poly64 *p);
  	Triple64(Poly64 *p, const bitset<64> &n);
  	Triple64(Poly64 *p, int n);
  	~Triple64() { delete poly; }

	Poly64* getPoly() const { return poly; };
	const Monom64& getPolyLm() const { return poly->lm(); }
	const bitset<64>& getNmp() const { return nmp; }

	void setNmp(bitset<64> new_nmp) { nmp = new_nmp; }
	void setNmp(int var) { nmp.set(var); }

  	void* operator new(size_t) { return sAllocator.allocate(); }
  	void operator delete(void *ptr) { sAllocator.deallocate(ptr); }
	static bool compare(Triple64* a, Triple64* b);

	void Phead_reduction(const Triple64& t) { poly->Phead_reduction( *t.poly ); };
};

#endif // TRIPLE64_H
