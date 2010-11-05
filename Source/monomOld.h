#ifndef MONOMOLD_H
#define MONOMOLD_H

#include <iostream>
#include <cstring>
#include <bitset>
#include <set>

#include "variables.h"
#include "fast_allocator.h"

class MonomOld
{
public:
    typedef short int Integer;

protected:
    Integer mTotalDegree;
    unsigned long exp;

    static Integer mDimIndepend;
    static FastAllocator Allocator;
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
    static void AddVariable(const char *var);
    static const char* GetVariable(Integer var);
    static Integer DimIndepend();

    MonomOld() { memset(this, 0, sizeof(MonomOld)); }
    MonomOld(const MonomOld& a) { memcpy(this, &a, sizeof(MonomOld)); }
    ~MonomOld() { mNext = 0; };

    void* operator new(size_t) { return Allocator.Allocate(); }
    void operator delete(void *ptr) { Allocator.Free(ptr); }

    Integer Degree() const;

    Integer operator[](short var) const;
    const MonomOld& operator=(const MonomOld& anotherMonom);
    const MonomOld& operator*=(short var);
    const MonomOld& operator*=(const MonomOld& anotherMonom);
    void SetProductOf(const MonomOld& monomA, short var);
    void SetProductOf(const MonomOld& monomA, const MonomOld& monomB);
    const MonomOld& operator/=(const MonomOld& anotherMonom);
    void SetQuotientOf(const MonomOld& monomA, const MonomOld& monomB);

    bool operator==(const MonomOld& anotherMonom) const;
    bool operator!=(const MonomOld& anotherMonom) const;
    bool operator<(const MonomOld& anotherMonom) const;
    bool operator>(const MonomOld& anotherMonom) const;
    static int Compare(const MonomOld& monomA, const MonomOld& monomB);

    void SetOne();

    bool IsDivisibleBy(const MonomOld& anotherMonom) const;
    bool IsTrueDivisibleBy(const MonomOld& anotherMonom) const;
    bool IsPommaretDivisibleBy(const MonomOld& anotherMonom) const;

    static short GcdDegree(const MonomOld& monomA, const MonomOld& monomB);
    static short LcmDegree(const MonomOld& monomA, const MonomOld& monomB);
    void SetGcdOf(const MonomOld& monomA, const MonomOld& monomB);
    void SetLcmOf(const MonomOld& monomA, const MonomOld& monomB);

    friend std::istream& operator>>(std::istream& in, MonomOld& a);
    friend std::ostream& operator<<(std::ostream& out, const MonomOld& a);

    Integer FirstMultiVar() const;
    std::set<Integer> GetVariablesSet() const;
};

inline const MonomOld& MonomOld::operator=(const MonomOld& anotherMonom)
{
    memcpy(this, &anotherMonom, sizeof(MonomOld));
    return *this;
}

inline MonomOld::Integer MonomOld::operator[](short var) const
{
    return (exp & One[var]) != 0;
}

inline MonomOld::Integer MonomOld::DimIndepend()
{
    return mDimIndepend;
}

inline MonomOld::Integer MonomOld::Degree() const
{
    return mTotalDegree;
}

inline void MonomOld::SetOne()
{
    mTotalDegree = 0;
    exp = 0;
}

inline const MonomOld& MonomOld::operator*=(short var)
{
    if (!(exp & One[var]))
    {
        exp |= One[var];
        ++mTotalDegree;
    }
    return *this;
}

inline const MonomOld& MonomOld::operator/=(const MonomOld& anotherMonom)
{
    exp ^= anotherMonom.exp;
    unsigned short *s = (unsigned short*)&exp;
    mTotalDegree = Data[*s][DEGREE];
    for (register int i=1; i<4; ++i)
    {
        ++s;
        mTotalDegree += Data[*s][DEGREE];
    }
    return *this;
}

inline const MonomOld& MonomOld::operator*=(const MonomOld& anotherMonom)
{
    exp |= anotherMonom.exp;
    unsigned short *s = (unsigned short*)&exp;
    mTotalDegree = Data[*s][DEGREE];
    for (int i=1; i<4; ++i)
    {
        ++s;
        mTotalDegree += Data[*s][DEGREE];
    }
    return *this;
}

inline void MonomOld::SetProductOf(const MonomOld& monomA, short var)
{
    exp = monomA.exp;
    exp |= One[var];
    unsigned short *s = (unsigned short*)&exp;
    mTotalDegree = Data[*s][DEGREE];
    for (int i=1; i<4; ++i)
    {
        ++s;
        mTotalDegree += Data[*s][DEGREE];
    }
}

inline void MonomOld::SetProductOf(const MonomOld& monomA, const MonomOld& monomB)
{
    exp = monomA.exp | monomB.exp;
    unsigned short *s = (unsigned short*)&exp;
    mTotalDegree = Data[*s][DEGREE];
    for (int i=1; i<4; ++i)
    {
        ++s;
        mTotalDegree += Data[*s][DEGREE];
    }
}

inline bool MonomOld::IsDivisibleBy(const MonomOld& anotherMonom) const
{
    unsigned long d(exp ^ anotherMonom.exp);
    d &= anotherMonom.exp;
    return d == 0;
}

inline bool MonomOld::IsTrueDivisibleBy(const MonomOld& anotherMonom) const
{
    unsigned long d(exp ^ anotherMonom.exp);
    if (d==0)
    {
        return false;
    }
    else
    {
        d &= anotherMonom.exp;
        return d == 0;
    }
}

inline bool MonomOld::IsPommaretDivisibleBy(const MonomOld& anotherMonom) const
{
    if (!exp && anotherMonom.exp)
    {
        return false;
    }
    //эта проверка идентична if(!d)
    //if (exp == a.exp)
    //	return true;

    unsigned long d(exp ^ anotherMonom.exp);
    unsigned short *iterD = (unsigned short*)&d, *iterA = (unsigned short*)&anotherMonom.exp + 3;
    //эта глупая проверка нужна лишь для того, чтобы вычислилось наконец d.
    //при уровне оптимизации O2 и выше значение переменной d не вычисляется
    //до первого непосредственного обращения.
    //или собирать с флагом компилятора -fno-schedule-insns2
    if (!d)
    {
        return true;
    }

    int i = 0;
    while (i < 4)
    {
        if (*iterD) break;
        ++iterD;
        ++i;
    }

    int j = 3;
    while (j >= 0)
    {
        if (*iterA) break;
        iterA--;
        j--;
    }

    if (i < j) return false;
    if (i > j) return true;
    if (i == j)
    {
        if (Data[*iterD][FIRSTONE]>Data[*iterA][LASTONE])
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

inline void MonomOld::SetQuotientOf(const MonomOld& monomA, const MonomOld& monomB)
{
    mTotalDegree = monomA.mTotalDegree - monomB.mTotalDegree;
    exp = monomA.exp ^ monomB.exp;
}

inline short MonomOld::GcdDegree(const MonomOld& monomA, const MonomOld& monomB)
{
    unsigned long d(monomA.exp & monomB.exp);
    unsigned short *s = (unsigned short*)&d;
    short r = Data[*s][DEGREE];
    for (register int i=1; i<4; ++i)
    {
        ++s;
        r += Data[*s][DEGREE];
    }
    return r;
}

inline short MonomOld::LcmDegree(const MonomOld& monomA, const MonomOld& monomB)
{
    unsigned long d(monomA.exp | monomB.exp);
    unsigned short *s = (unsigned short*)&d;
    short r = Data[*s][DEGREE];
    for (register int i=1; i<4; ++i)
    {
        ++s;
        r += Data[*s][DEGREE];
    }
    return r;
}

inline void MonomOld::SetGcdOf(const MonomOld& monomA, const MonomOld& monomB)
{
    exp = monomA.exp & monomB.exp;
    unsigned short *s = (unsigned short*)&exp;
    mTotalDegree = Data[*s][DEGREE];
    for (register int i=1; i<4; ++i)
    {
        ++s;
        mTotalDegree += Data[*s][DEGREE];
    }
}

inline void MonomOld::SetLcmOf(const MonomOld& monomA, const MonomOld& monomB)
{
    exp = monomA.exp | monomB.exp;
    unsigned short *s = (unsigned short*)&exp;
    mTotalDegree = Data[*s][DEGREE];
    for (register int i=1; i<4; ++i)
    {
        ++s;
        mTotalDegree += Data[*s][DEGREE];
    }
}

inline int MonomOld::Compare(const MonomOld& monomA, const MonomOld& monomB)
{
    if (monomA.mTotalDegree < monomB.mTotalDegree)
    {
        return -1;
    }
    else if (monomA.mTotalDegree > monomB.mTotalDegree)
    {
        return 1;
    }
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
    {
        return true;
    }
    else if (mTotalDegree > anotherMonom.mTotalDegree)
    {
        return false;
    }
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
    {
        return false;
    }
    else if (mTotalDegree > anotherMonom.mTotalDegree)
    {
        return true;
    }
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

inline short MonomOld::FirstMultiVar() const
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
            ++result;
        }
        return result;
    }
}

inline std::set<MonomOld::Integer> MonomOld::GetVariablesSet() const
{
    std::set<Integer> result;
    for (register Integer i = 0; i < DimIndepend(); ++i)
    {
        if((exp & One[i]))
        {
            result.insert(i);
        }
    }
}

#endif // MONOMOLD_H
