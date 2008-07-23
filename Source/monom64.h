#ifndef MONOM64_H
#define MONOM64_H

#include <iostream>
#include <cstring>
#include <bitset>
#include "variables.h"
#include "allocator.h"

using namespace std;

class Monom64
{
protected:
  	unsigned long mTotalDegree;
  	unsigned long exp;

  	static int mDimIndepend;
  	static Allocator sAllocator;
  	static unsigned long Zero[64], One[64];
  	static unsigned short Data[][4];

  	enum
  	{
    		DEGREE = 0,
    		FIRSTONE = 1,
    		LASTONE = 2,
    		POMMARETNM = 3
  	};

public:
  	Monom64* Next;
  	static Variables* mIndepend;
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
  	bool divisibilityPommaret(const Monom64& a) const;
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
  	if (exp & One[var]) return 1;
  	return 0;
}

inline unsigned Monom64::degree() const
{
  	return mTotalDegree;
}

inline void Monom64::setZero()
{
  	mTotalDegree = 0;
  	exp = 0;
}

inline void Monom64::prolong(int var)
{
  	if ( !(exp & One[var]) )
	{
    		exp = exp | One[var];
    		mTotalDegree++;
  	}
}

inline void Monom64::prolong(int var, unsigned deg)
{
  	if (deg>0) prolong(var);
}

inline void Monom64::div(int var)
{
  	if ( exp & One[var] )
	{
    		exp = exp & Zero[var];
    		mTotalDegree--;
  	}
  	else
   		IERROR("Monom can't be divided by variable");
}

inline void Monom64::div(const Monom64& a)
{
  	exp ^= a.exp;
  	unsigned short *s = (unsigned short*)&exp;
  	mTotalDegree = Data[*s][DEGREE];
  	for (register int i=1; i<4; i++)
	{
    		s++;
    		mTotalDegree += Data[*s][DEGREE];
  	}
}

inline void Monom64::mult(const Monom64& a)
{
  	exp |= a.exp;
  	unsigned short *s = (unsigned short*)&exp;
  	mTotalDegree = Data[*s][DEGREE];
  	for (int i=1; i<4; i++)
	{
    		s++;
    		mTotalDegree += Data[*s][DEGREE];
  	}
}

inline void Monom64::mult1(const Monom64& a)
{
  	exp|=a.exp;
}

inline void Monom64::mult(const Monom64& a, const Monom64& b)
{
  	exp = a.exp | b.exp;
  	unsigned short *s = (unsigned short*)&exp;
  	mTotalDegree = Data[*s][DEGREE];
  	for (int i=1; i<4; i++)
	{
    		s++;
    		mTotalDegree += Data[*s][DEGREE];
  	}
}

inline bool Monom64::divisibility(const Monom64& a) const
{
  	unsigned long d(exp ^ a.exp);
  	d &= a.exp;
  	if(d!=0)
    		return false;
  	else
    		return true;
}

inline bool Monom64::divisibilityTrue(const Monom64& a) const
{
  	unsigned long d(exp ^ a.exp);
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

inline bool Monom64::divisibilityPommaret(const Monom64& a) const
{
  	if (!exp && a.exp)
   		return false;
  	//эта проверка идентична if(!d)
  	//if (exp == a.exp)
  	//	return true;

  	unsigned long d(exp ^ a.exp);
  	unsigned short *iterD = (unsigned short*)&d, *iterA = (unsigned short*)&a.exp + 3;
  	//эта глупая проверка нужна лишь для того, чтобы вычислилось наконец d.
  	//при уровне оптимизации O2 и выше значение переменной d не вычисляется
  	//до первого непосредственного обращения.
  	//или собирать с флагом компилятора -fno-schedule-insns2
  	if (!d) return true;

  	int i = 0;
  	while (i<4)
  	{
    		if (*iterD) break;
    		iterD++;
    		i++;
  	}
  	int j = 3;
  	while (j>=0)
  	{
    		if (*iterA) break;
    		iterA--;
    		j--;
  	}

  	if (i<j) return false;
  	if (i>j) return true;
  	if (i==j)
  	{
    		if (Data[*iterD][FIRSTONE]>Data[*iterA][LASTONE]) return true;
    		else return false;
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
  	unsigned long d(exp & a.exp);
  	unsigned short *s = (unsigned short*)&d;
  	unsigned short r = Data[*s][DEGREE];
  	for (register int i=1; i<4; i++)
	{
    		s++;
    		r += Data[*s][DEGREE];
  	}
  	return r;
}

inline unsigned Monom64::lcm(const Monom64& a) const
{
  	unsigned long d(exp | a.exp);
  	unsigned short *s = (unsigned short*)&d;
  	unsigned short r = Data[*s][DEGREE];
  	for (register int i=1; i<4; i++)
	{
    		s++;
    		r += Data[*s][DEGREE];
  	}
  	return r;
}

inline void Monom64::gcd(const Monom64& a, const Monom64& b)
{
  	exp = a.exp & b.exp;
  	unsigned short *s = (unsigned short*)&exp;
  	mTotalDegree = Data[*s][DEGREE];
  	for (register int i=1; i<4; i++)
	{
    		s++;
    		mTotalDegree += Data[*s][DEGREE];
  	}
}

inline void Monom64::lcm(const Monom64& a, const Monom64& b)
{
  	exp = a.exp | b.exp;
  	unsigned short *s = (unsigned short*)&exp;
  	mTotalDegree = Data[*s][DEGREE];
  	for (register int i=1; i<4; i++)
	{
    		s++;
    		mTotalDegree += Data[*s][DEGREE];
  	}
}

inline bool Monom64::equality(const Monom64& a, int var, unsigned degree) const
{
  	unsigned long d(1);
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
    		if (exp < a.exp)
      			return 1;
    		else if (exp > a.exp)
      			return -1;
    		else
      			return 0;
  	}
}

inline bool operator==(const Monom64 &a, const Monom64 &b)
{
  	return a.exp==b.exp;
}

/*
inline bitset<64> Monom64::Pnmv() const
{
  	bitset<64> out = 0;
  	bool LastFound = false;
  	unsigned short *iterExp, *iterOut;
  	iterExp = (unsigned short*)&exp + 3;
  	iterOut = (unsigned short*)&out + 3;

  	for(register int i=0;i<4;i++)
  	{
    		if (LastFound)
    		{
      			*iterOut = 65535;
    		}
    		else if (*iterExp)
    		{
      			LastFound = true;
      			*iterOut = Data[*iterExp][POMMARETNM];
    		}
    		iterExp--;
    		iterOut--;
  	}

  	return out;
}*/


inline bitset<64> Monom64::Pnmv() const
{
  	bitset<64> out = 0;
  	bool LastFound = false;
  	unsigned short *iterExp, *iterOut;
  	iterExp = (unsigned short*)&exp + 3;
  	out.set();

  	for(register int i=3;i>=0;i--)
  	{
    		if (*iterExp)
    		{
      			int shift = 64 - Data[*iterExp][LASTONE] - 16*i;
      			out = out << shift;
      			out = out >> shift;
      			break;
    		}
    		iterExp--;
  	}

  	return out;
}

#endif // MONOM64_H
