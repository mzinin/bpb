#ifndef MONOMOLD_H
#define MONOMOLD_H

#include <iostream>
#include <cstring>
#include <bitset>
#include "variables.h"
#include "allocator.h"

using namespace std;

class MonomOld
{
public:
    typedef short int Integer;

protected:
  	Integer mTotalDegree;
  	unsigned long exp;

  	static Integer mDimIndepend;
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
  	MonomOld* mNext;
  	static Variables* mIndepend;

public:
    static void addVariable(const char *var);

  	MonomOld() { memset(this, 0, sizeof(MonomOld)); }
  	MonomOld(const MonomOld& a) { memcpy(this, &a, sizeof(MonomOld)); }
  	~MonomOld() { mNext = NULL; };

  	void* operator new(size_t) { return sAllocator.allocate(); }
  	void operator delete(void *ptr) { sAllocator.deallocate(ptr); }

  	Integer dimIndepend() const { return mDimIndepend; }
  	Integer degree() const;

    Integer operator[](short var) const;
    const MonomOld& operator=(const MonomOld& anotherMonom);
    const MonomOld& operator*=(short var);
    const MonomOld& operator*=(const MonomOld& anotherMonom);
    void setProductOf(const MonomOld& monomA, short var);
    void setProductOf(const MonomOld& monomA, const MonomOld& monomB);
    const MonomOld& operator/=(const MonomOld& anotherMonom);
    void setQuotientOf(const MonomOld& monomA, const MonomOld& monomB);

    bool operator==(const MonomOld& anotherMonom) const;
    bool operator!=(const MonomOld& anotherMonom) const;
    bool operator<(const MonomOld& anotherMonom) const;
    bool operator>(const MonomOld& anotherMonom) const;
    static int compare(const MonomOld& monomA, const MonomOld& monomB);

  	void setOne();

    bool isDivisibleBy(const MonomOld& anotherMonom) const;
    bool isTrueDivisibleBy(const MonomOld& anotherMonom) const;
    bool isPommaretDivisibleBy(const MonomOld& anotherMonom) const;

    static short gcdDegree(const MonomOld& monomA, const MonomOld& monomB);
    static short lcmDegree(const MonomOld& monomA, const MonomOld& monomB);
    void setGcdOf(const MonomOld& monomA, const MonomOld& monomB);
    void setLcmOf(const MonomOld& monomA, const MonomOld& monomB);

  	friend std::istream& operator>>(std::istream& in, MonomOld& a);
  	friend std::ostream& operator<<(std::ostream& out, const MonomOld& a);

    Integer firstMultiVar() const;
};

inline const MonomOld& MonomOld::operator=(const MonomOld& anotherMonom)
{
  	memcpy(this, &anotherMonom, sizeof(MonomOld));
}

inline MonomOld::Integer MonomOld::operator[](short var) const
{
        return (exp & One[var]) != 0;
}

inline MonomOld::Integer MonomOld::degree() const
{
  	return mTotalDegree;
}

inline void MonomOld::setOne()
{
  	mTotalDegree = 0;
  	exp = 0;
}

inline const MonomOld& MonomOld::operator*=(short var)
{
  	if ( !(exp & One[var]) )
	{
    		exp |= One[var];
    		mTotalDegree++;
  	}
}

inline const MonomOld& MonomOld::operator/=(const MonomOld& anotherMonom)
{
        exp ^= anotherMonom.exp;
  	unsigned short *s = (unsigned short*)&exp;
  	mTotalDegree = Data[*s][DEGREE];
  	for (register int i=1; i<4; i++)
	{
    		s++;
    		mTotalDegree += Data[*s][DEGREE];
  	}
}

inline const MonomOld& MonomOld::operator*=(const MonomOld& anotherMonom)
{
        exp |= anotherMonom.exp;
  	unsigned short *s = (unsigned short*)&exp;
  	mTotalDegree = Data[*s][DEGREE];
  	for (int i=1; i<4; i++)
	{
    		s++;
    		mTotalDegree += Data[*s][DEGREE];
  	}
}

inline void MonomOld::setProductOf(const MonomOld& monomA, short var)
{
    exp = monomA.exp;
    exp |= One[var];
    unsigned short *s = (unsigned short*)&exp;
    mTotalDegree = Data[*s][DEGREE];
    for (int i=1; i<4; i++)
    {
        s++;
        mTotalDegree += Data[*s][DEGREE];
    }
}

inline void MonomOld::setProductOf(const MonomOld& monomA, const MonomOld& monomB)
{
        exp = monomA.exp | monomB.exp;
  	unsigned short *s = (unsigned short*)&exp;
  	mTotalDegree = Data[*s][DEGREE];
  	for (int i=1; i<4; i++)
	{
    		s++;
    		mTotalDegree += Data[*s][DEGREE];
  	}
}

inline bool MonomOld::isDivisibleBy(const MonomOld& anotherMonom) const
{
        unsigned long d(exp ^ anotherMonom.exp);
        d &= anotherMonom.exp;
  	return d == 0;
}

inline bool MonomOld::isTrueDivisibleBy(const MonomOld& anotherMonom) const
{
        unsigned long d(exp ^ anotherMonom.exp);
  	if (d==0)
    		return false;
  	else
	{
                d &= anotherMonom.exp;
                return d == 0;
  	}
}

inline bool MonomOld::isPommaretDivisibleBy(const MonomOld& anotherMonom) const
{
        if (!exp && anotherMonom.exp)
   		return false;
  	//эта проверка идентична if(!d)
  	//if (exp == a.exp)
  	//	return true;

        unsigned long d(exp ^ anotherMonom.exp);
        unsigned short *iterD = (unsigned short*)&d, *iterA = (unsigned short*)&anotherMonom.exp + 3;
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

inline void MonomOld::setQuotientOf(const MonomOld& monomA, const MonomOld& monomB)
{
    mTotalDegree = monomA.mTotalDegree - monomB.mTotalDegree;
    exp = monomA.exp ^ monomB.exp;
}

inline short MonomOld::gcdDegree(const MonomOld& monomA, const MonomOld& monomB)
{
        unsigned long d(monomA.exp & monomB.exp);
  	unsigned short *s = (unsigned short*)&d;
  	short r = Data[*s][DEGREE];
  	for (register int i=1; i<4; i++)
	{
    		s++;
    		r += Data[*s][DEGREE];
  	}
  	return r;
}

inline short MonomOld::lcmDegree(const MonomOld& monomA, const MonomOld& monomB)
{
        unsigned long d(monomA.exp | monomB.exp);
  	unsigned short *s = (unsigned short*)&d;
  	short r = Data[*s][DEGREE];
  	for (register int i=1; i<4; i++)
	{
    		s++;
    		r += Data[*s][DEGREE];
  	}
  	return r;
}

inline void MonomOld::setGcdOf(const MonomOld& monomA, const MonomOld& monomB)
{
        exp = monomA.exp & monomB.exp;
  	unsigned short *s = (unsigned short*)&exp;
  	mTotalDegree = Data[*s][DEGREE];
  	for (register int i=1; i<4; i++)
	{
    		s++;
    		mTotalDegree += Data[*s][DEGREE];
  	}
}

inline void MonomOld::setLcmOf(const MonomOld& monomA, const MonomOld& monomB)
{
        exp = monomA.exp | monomB.exp;
  	unsigned short *s = (unsigned short*)&exp;
  	mTotalDegree = Data[*s][DEGREE];
  	for (register int i=1; i<4; i++)
	{
    		s++;
    		mTotalDegree += Data[*s][DEGREE];
  	}
}

inline int MonomOld::compare(const MonomOld& monomA, const MonomOld& monomB)
{
        if (monomA.mTotalDegree < monomB.mTotalDegree)
    		return -1;
        else if (monomA.mTotalDegree > monomB.mTotalDegree)
    		return 1;
  	else
	{
                if (monomA.exp < monomB.exp)
      			return 1;
                else if (monomA.exp > monomB.exp)
      			return -1;
    		else
      			return 0;
  	}
}

inline bool MonomOld::operator<(const MonomOld& anotherMonom) const
{
    if (mTotalDegree < anotherMonom.mTotalDegree)
        return true;
    else if (mTotalDegree > anotherMonom.mTotalDegree)
        return false;
    else
    {
        if (exp > anotherMonom.exp)
            return true;
        else
            return false;
    }
}

inline bool MonomOld::operator>(const MonomOld& anotherMonom) const
{
    if (mTotalDegree < anotherMonom.mTotalDegree)
        return false;
    else if (mTotalDegree > anotherMonom.mTotalDegree)
        return true;
    else
    {
        if (exp < anotherMonom.exp)
            return true;
        else
            return false;
    }
}

inline bool MonomOld::operator==(const MonomOld& anotherMonom) const
{
    return exp == anotherMonom.exp;
}

inline bool MonomOld::operator!=(const MonomOld& anotherMonom) const
{
    return exp != anotherMonom.exp;
}

inline short MonomOld::firstMultiVar() const
{
    if (exp == 0)
    {
        return 0;
    }
    else
    {
        unsigned long tmp = exp;
        short result = -1;
        while (tmp > 0)
        {
            tmp = tmp >> 1;
            result++;
        }
        return result;
    }
}

#endif // MONOMOLD_H
