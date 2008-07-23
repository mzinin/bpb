#include "triple64.h"

Triple64::Triple64(Poly64 *p)
{
	poly = p;
	lm = poly->lm();
	anc = this;
	anc_lm = lm;
	wanc = NULL;
	nmp = 0;
	var = -1;
}

Triple64::Triple64(Poly64 *p, const Triple64* m, const Triple64* w, const bitset<64> &n, int mvar)
{
	poly = p;
	lm = poly->lm();
	if (m)
	{
		anc = m;
		anc_lm = anc->getPolyLm();
	}
	else
	{
		anc = this;
		anc_lm = lm;
	}
	wanc = w;
	nmp = n;
	var = mvar;
	if (var != -1) nmp.set(var);
}

Triple64::Triple64(Poly64 *p, const Triple64* m, const Triple64* w, int n, int mvar)
{
	poly = p;
	lm = poly->lm();
	if (m)
	{
		anc = m;
		anc_lm = anc->getPolyLm();
	}
	else
	{
		anc = this;
		anc_lm = lm;
	}
	wanc = w;
	nmp = n;
	var = mvar;
	if (var != -1) nmp.set(var);
}

bool Triple64::compare(Triple64* a, Triple64* b)
{
  	if ( a->lm.compare(b->lm)==1 )
    		return true;
  	else
    		return false;
}

Allocator Triple64::sAllocator(sizeof(Triple64));
