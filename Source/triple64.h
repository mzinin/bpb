#ifndef TRIPLE64_H
#define TRIPLE64_H

#include "poly64.h"

class Triple64
{
	Monom64 lm;
	Monom64 anc_lm;
	bitset<64> nmp;
  	Poly64*  poly;
  	const Triple64* anc;
  	const Triple64* wanc;
	int var;
  	static Allocator sAllocator;

public:
	Triple64(Poly64 *p);
  	Triple64(Poly64 *p, const Triple64* m, const Triple64* w, const bitset<64> &n, int mvar);
  	Triple64(Poly64 *p, const Triple64* m, const Triple64* w, int n, int mvar);
  	~Triple64() { delete poly; }

	Poly64* getPoly() const;
	const Monom64& getPolyLm() const { return lm; }
	const Triple64* getAnc() const { return anc; }
	const Monom64& getAncLm() const { return anc_lm; }
	const Triple64* getWanc() const { return wanc; }
	const bitset<64>& getNmp() const { return nmp; }
	int getVar() const { return var; };
	bool isCriteriaAppliable() const;

	void setNmp(bitset<64> new_nmp) { nmp = new_nmp; }
	void setNmp(int var) { nmp.set(var); }

  	void* operator new(size_t) { return sAllocator.allocate(); }
  	void operator delete(void *ptr) { sAllocator.deallocate(ptr); }
	static bool compare(Triple64* a, Triple64* b);
};

inline Poly64* Triple64::getPoly() const
{
	return poly;
}

inline bool Triple64::isCriteriaAppliable() const
{
	return var != -1;
}

#endif // TRIPLE64_H
