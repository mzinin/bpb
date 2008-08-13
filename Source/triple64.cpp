#include "triple64.h"

Triple64::Triple64(Poly64 *p)
{
	poly = p;
	nmp = 0;
}

Triple64::Triple64(Poly64 *p, const bitset<64> &n)
{
	poly = p;
	nmp = n;
}

Triple64::Triple64(Poly64 *p, int n)
{
	poly = p;
	nmp = n;
}

bool Triple64::compare(Triple64* a, Triple64* b)
{
  	if ( a->poly->lm().compare(b->poly->lm())==1 )
    		return true;
  	else
    		return false;
}

Allocator Triple64::sAllocator(sizeof(Triple64));
