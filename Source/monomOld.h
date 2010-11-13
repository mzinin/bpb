#ifndef MONOMOLD_H
#define MONOMOLD_H

#include <cstring>
#include <bitset>
#include <set>

#include "fast_allocator.h"
#include "monom.h"

class MonomOld : public Monom
{
private:
    unsigned long Exponent;

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

    friend class Monom;

private:
    MonomOld();
    MonomOld(const Monom& anotherMonom);
    const MonomOld* CastToMe(const Monom& monom) const;

public:
    ~MonomOld();

    Monom::Order GetOrder() const;

    void* operator new(std::size_t);
    void operator delete(void* ptr);

    Integer operator[](short var) const;

    const Monom& operator=(const Monom& anotherMonom);

    const Monom& operator*=(short var);
    const Monom& operator*=(const Monom& anotherMonom);
    void SetProductOf(const Monom& anotherMonom, short var);
    void SetProductOf(const Monom& monomA, const Monom& monomB);

    const Monom& operator/=(const Monom& anotherMonom);
    void SetQuotientOf(const Monom& monomA, const Monom& monomB);

    void SetOne();

    bool operator==(const Monom& anotherMonom) const;
    bool operator!=(const Monom& anotherMonom) const;
    bool operator<(const Monom& anotherMonom) const;
    bool operator>(const Monom& anotherMonom) const;

    bool IsDivisibleBy(const Monom& anotherMonom) const;
    bool IsTrueDivisibleBy(const Monom& anotherMonom) const;
    bool IsPommaretDivisibleBy(const Monom& anotherMonom) const;

    void SetGcdOf(const Monom& monomA, const Monom& monomB);
    void SetLcmOf(const Monom& monomA, const Monom& monomB);

    Integer FirstMultiVar() const;
    std::set<Integer> GetVariablesSet() const;

    int Compare(const Monom& anotherMonom);
    Integer GcdDegree(const Monom& anotherMonom);
    Integer LcmDegree(const Monom& anotherMonom);
};

inline MonomOld::MonomOld()
    : Monom()
    , Exponent(0)
{
}

inline MonomOld::MonomOld(const Monom& anotherMonom)
    : Monom()
    , Exponent(0)
{
    const MonomOld* castedAnotherMonom = CastToMe(anotherMonom);

    TotalDegree = castedAnotherMonom->TotalDegree;
    Exponent = castedAnotherMonom->Exponent;
}

inline const MonomOld* MonomOld::CastToMe(const Monom& monom) const
{
    if (monom.GetOrder() != GetOrder())
    {
        throw 1;
    }
    return static_cast<const MonomOld*>(&monom);
}

inline MonomOld::~MonomOld()
{
    SetOne();
}

inline Monom::Order MonomOld::GetOrder() const
{
    return Monom::OldDRL;
}

inline void* MonomOld::operator new(std::size_t)
{
    return Allocator.Allocate();
}

inline void MonomOld::operator delete(void* ptr)
{
    Allocator.Free(ptr);
}

inline MonomOld::Integer MonomOld::operator[](short var) const
{
    return (Exponent & One[var]) != 0;
}

inline const Monom& MonomOld::operator=(const Monom& anotherMonom)
{
    const MonomOld* castedAnotherMonom = CastToMe(anotherMonom);

    TotalDegree = castedAnotherMonom->TotalDegree;
    Exponent = castedAnotherMonom->Exponent;
    return *this;
}

inline const Monom& MonomOld::operator*=(short var)
{
    if (!(Exponent & One[var]))
    {
        Exponent |= One[var];
        ++TotalDegree;
    }
    return *this;
}

inline const Monom& MonomOld::operator*=(const Monom& anotherMonom)
{
    const MonomOld* castedAnotherMonom = CastToMe(anotherMonom);

    Exponent |= castedAnotherMonom->Exponent;
    unsigned short *s = (unsigned short*)&Exponent;
    TotalDegree = Data[*s][DEGREE];
    for (register int i = 1; i < 4; ++i)
    {
        ++s;
        TotalDegree += Data[*s][DEGREE];
    }
    return *this;
}

inline void MonomOld::SetProductOf(const Monom& anotherMonom, short var)
{
    const MonomOld* castedAnotherMonom = CastToMe(anotherMonom);

    Exponent = castedAnotherMonom->Exponent;
    Exponent |= One[var];
    unsigned short *s = (unsigned short*)&Exponent;
    TotalDegree = Data[*s][DEGREE];
    for (register int i = 1; i < 4; ++i)
    {
        ++s;
        TotalDegree += Data[*s][DEGREE];
    }
}

inline void MonomOld::SetProductOf(const Monom& monomA, const Monom& monomB)
{
    const MonomOld* castedMonomA = CastToMe(monomA);
    const MonomOld* castedMonomB = CastToMe(monomB);

    Exponent = castedMonomA->Exponent | castedMonomB->Exponent;
    unsigned short *s = (unsigned short*)&Exponent;
    TotalDegree = Data[*s][DEGREE];
    for (register int i = 1; i < 4; ++i)
    {
        ++s;
        TotalDegree += Data[*s][DEGREE];
    }
}

inline const Monom& MonomOld::operator/=(const Monom& anotherMonom)
{
    const MonomOld* castedAnotherMonom = CastToMe(anotherMonom);

    Exponent ^= castedAnotherMonom->Exponent;
    unsigned short *s = (unsigned short*)&Exponent;
    TotalDegree = Data[*s][DEGREE];
    for (register int i = 1; i < 4; ++i)
    {
        ++s;
        TotalDegree += Data[*s][DEGREE];
    }
    return *this;
}

inline void MonomOld::SetQuotientOf(const Monom& monomA, const Monom& monomB)
{
    const MonomOld* castedMonomA = CastToMe(monomA);
    const MonomOld* castedMonomB = CastToMe(monomB);

    TotalDegree = castedMonomA->TotalDegree - castedMonomB->TotalDegree;
    Exponent = castedMonomA->Exponent ^ castedMonomB->Exponent;
}

inline void MonomOld::SetOne()
{
    TotalDegree = 0;
    Exponent = 0;
}

inline bool MonomOld::operator==(const Monom& anotherMonom) const
{
    const MonomOld* castedAnotherMonom = CastToMe(anotherMonom);

    return Exponent == castedAnotherMonom->Exponent;
}

inline bool MonomOld::operator!=(const Monom& anotherMonom) const
{
    const MonomOld* castedAnotherMonom = CastToMe(anotherMonom);

    return Exponent != castedAnotherMonom->Exponent;
}

inline bool MonomOld::operator<(const Monom& anotherMonom) const
{
    const MonomOld* castedAnotherMonom = CastToMe(anotherMonom);

    if (TotalDegree < castedAnotherMonom->TotalDegree)
    {
        return true;
    }
    else if (TotalDegree > castedAnotherMonom->TotalDegree)
    {
        return false;
    }
    else
    {
        if (Exponent > castedAnotherMonom->Exponent)
            return true;
        else
            return false;
    }
}

inline bool MonomOld::operator>(const Monom& anotherMonom) const
{
    const MonomOld* castedAnotherMonom = CastToMe(anotherMonom);

    if (TotalDegree < castedAnotherMonom->TotalDegree)
    {
        return false;
    }
    else if (TotalDegree > castedAnotherMonom->TotalDegree)
    {
        return true;
    }
    else
    {
        if (Exponent < castedAnotherMonom->Exponent)
            return true;
        else
            return false;
    }
}

inline bool MonomOld::IsDivisibleBy(const Monom& anotherMonom) const
{
    const MonomOld* castedAnotherMonom = CastToMe(anotherMonom);

    unsigned long d(Exponent ^ castedAnotherMonom->Exponent);
    d &= castedAnotherMonom->Exponent;
    return !d;
}

inline bool MonomOld::IsTrueDivisibleBy(const Monom& anotherMonom) const
{
    const MonomOld* castedAnotherMonom = CastToMe(anotherMonom);

    unsigned long d(Exponent ^ castedAnotherMonom->Exponent);
    if (!d)
    {
        return false;
    }
    else
    {
        d &= castedAnotherMonom->Exponent;
        return !d;
    }
}

inline bool MonomOld::IsPommaretDivisibleBy(const Monom& anotherMonom) const
{
    const MonomOld* castedAnotherMonom = CastToMe(anotherMonom);

    if (!Exponent && castedAnotherMonom->Exponent)
    {
        return false;
    }

    unsigned long d(Exponent ^ castedAnotherMonom->Exponent);
    unsigned short *iterD = (unsigned short*)&d, *iterA = (unsigned short*)&castedAnotherMonom->Exponent + 3;
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
        --iterA;
        --j;
    }

    if (i < j)
    {
        return false;
    }
    if (i > j)
    {
        return true;
    }
    if (i == j && Data[*iterD][FIRSTONE]>Data[*iterA][LASTONE])
    {
        return true;
    }

    return false;
}

inline void MonomOld::SetGcdOf(const Monom& monomA, const Monom& monomB)
{
    const MonomOld* castedMonomA = CastToMe(monomA);
    const MonomOld* castedMonomB = CastToMe(monomB);

    Exponent = castedMonomA->Exponent & castedMonomB->Exponent;
    unsigned short *s = (unsigned short*)&Exponent;
    TotalDegree = Data[*s][DEGREE];
    for (register int i = 1; i < 4; ++i)
    {
        ++s;
        TotalDegree += Data[*s][DEGREE];
    }
}

inline void MonomOld::SetLcmOf(const Monom& monomA, const Monom& monomB)
{
    const MonomOld* castedMonomA = CastToMe(monomA);
    const MonomOld* castedMonomB = CastToMe(monomB);

    Exponent = castedMonomA->Exponent | castedMonomB->Exponent;
    unsigned short *s = (unsigned short*)&Exponent;
    TotalDegree = Data[*s][DEGREE];
    for (register int i = 1; i < 4; ++i)
    {
        ++s;
        TotalDegree += Data[*s][DEGREE];
    }
}

inline short MonomOld::FirstMultiVar() const
{
    if (!Exponent)
    {
        return 0;
    }

    unsigned long tmp = Exponent;
    short result = -1;
    while (tmp > 0)
    {
        tmp = tmp >> 1;
        ++result;
    }
    return result;
}

inline std::set<MonomOld::Integer> MonomOld::GetVariablesSet() const
{
    std::set<Integer> result;
    for (register Integer i = 0; i < DimIndepend; ++i)
    {
        if((Exponent & One[i]))
        {
            result.insert(i);
        }
    }
    return result;
}

#endif // MONOMOLD_H
