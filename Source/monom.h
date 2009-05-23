#ifndef MONOM_H
#define MONOM_H

#include <iostream>
#include <set>
#include <algorithm>

#include "variables.h"
#include "allocator.h"

using namespace std;

class Monom
{
public:
    typedef unsigned short Integer;

protected:
    set<Integer> varsSet;
    static Integer mDimIndepend;
    static Allocator sAllocator;
    static Variables* mIndepend;

public:
    static void addVariable(const char *var);

    Monom();
    Monom(const Monom& anotherMonom);
    ~Monom();

    Integer dimIndepend() const;
    Integer degree() const;

    void* operator new(std::size_t);
    void operator delete(void *ptr);
    Integer operator[](Integer var) const;

    const Monom& operator=(const Monom& anotherMonom);
    const Monom& operator*=(const Monom& anotherMonom);
    const Monom& operator*=(Integer var);
    Monom operator*(const Monom& anotherMonom) const;
    Monom operator*(Integer var) const;
    const Monom& operator/=(const Monom& anotherMonom);
    Monom operator/(const Monom& anotherMonom) const;

    bool operator==(const Monom& anotherMonom) const;
    bool operator!=(const Monom& anotherMonom) const;
    bool operator<(const Monom& anotherMonom) const;
    bool operator>(const Monom& anotherMonom) const;

    void setOne();

    bool isDivisibleBy(const Monom& anotherMonom) const;
    bool isTrueDivisibleBy(const Monom& anotherMonom) const;
    bool isPommaretDivisibleBy(const Monom& anotherMonom) const;

    friend std::istream& operator>>(std::istream& in, Monom& a);
    friend std::ostream& operator<<(std::ostream& out, const Monom& a);

    static Integer GCD_degree(const Monom& a, const Monom& b);
    static Integer LCM_degree(const Monom& a, const Monom& b);
    static Monom GCD(const Monom& a, const Monom& b);
    static Monom LCM(const Monom& a, const Monom& b);

    Integer firstMultiVar() const;
};


inline Monom::Monom(): varsSet()
{
}

inline Monom::Monom(const Monom& anotherMonom):
        varsSet(anotherMonom.varsSet)
{
}

inline Monom::~Monom()
{
    varsSet.clear();
}

inline Monom::Integer Monom::dimIndepend() const
{
    return mDimIndepend;
}

inline Monom::Integer Monom::degree() const
{
    return varsSet.size();
}

inline void* Monom::operator new(std::size_t)
{
    return sAllocator.allocate();
}

inline void Monom::operator delete(void *ptr)
{
    sAllocator.deallocate(ptr);
}

inline Monom::Integer Monom::operator[](Monom::Integer var) const
{
    return varsSet.count(var);
}

inline const Monom& Monom::operator=(const Monom& anotherMonom)
{
    varsSet.clear();
    varsSet = anotherMonom.varsSet;
    return *this;
}

inline const Monom& Monom::operator*=(const Monom& anotherMonom)
{
    varsSet.insert(anotherMonom.varsSet.begin(), anotherMonom.varsSet.end());

    return *this;
}

inline const Monom& Monom::operator*=(Integer var)
{
    varsSet.insert(var);
    return *this;
}

inline Monom Monom::operator*(const Monom& anotherMonom) const
{
    Monom tmpMonom;
    set_union(varsSet.begin(), varsSet.end(),
              anotherMonom.varsSet.begin(), anotherMonom.varsSet.end(),
              inserter(tmpMonom.varsSet, tmpMonom.varsSet.begin()));

    return tmpMonom;
}

inline Monom Monom::operator*(Integer var) const
{
    Monom tmpMonom(*this);
    tmpMonom *= var;
    return tmpMonom;
}

inline const Monom& Monom::operator/=(const Monom& anotherMonom)
{
    set<Integer> tmpSet;
    set_difference(varsSet.begin(), varsSet.end(),
                   anotherMonom.varsSet.begin(), anotherMonom.varsSet.end(),
                   inserter(tmpSet, tmpSet.begin()));
    varsSet = tmpSet;;

    return *this;
}

inline Monom Monom::operator/(const Monom& anotherMonom) const
{
    Monom tmpMonom;
    set_difference(varsSet.begin(), varsSet.end(),
                   anotherMonom.varsSet.begin(), anotherMonom.varsSet.end(),
                   inserter(tmpMonom.varsSet, tmpMonom.varsSet.begin()));

    return tmpMonom;
}

inline void Monom::setOne()
{
    varsSet.clear();
}

inline bool Monom::isDivisibleBy(const Monom& anotherMonom) const
{
    if (degree() < anotherMonom.degree())
    {
        return false;
    }

    set<Integer> tmpSet;
    set_difference(anotherMonom.varsSet.begin(), anotherMonom.varsSet.end(),
                   varsSet.begin(), varsSet.end(),
                   inserter(tmpSet, tmpSet.begin()));

    return tmpSet.empty();
}

inline bool Monom::isTrueDivisibleBy(const Monom& anotherMonom) const
{
    if (degree() <= anotherMonom.degree())
    {
        return false;
    }

    set<Integer> tmpSet;
    set_difference(anotherMonom.varsSet.begin(), anotherMonom.varsSet.end(),
                   varsSet.begin(), varsSet.end(),
                   inserter(tmpSet, tmpSet.begin()));

    return tmpSet.empty();
}

inline bool Monom::isPommaretDivisibleBy(const Monom& anotherMonom) const
{
    if (degree() < anotherMonom.degree())
    {
        return false;
    }
    if (anotherMonom.degree() == 0)
    {
        return true;
    }

    set<Integer> tmpSet;
    set_symmetric_difference(anotherMonom.varsSet.begin(), anotherMonom.varsSet.end(),
                             varsSet.begin(), varsSet.end(),
                             inserter(tmpSet, tmpSet.begin()));

    return tmpSet.empty() || *anotherMonom.varsSet.rbegin() <= *tmpSet.begin();
}

inline bool Monom::operator==(const Monom& anotherMonom) const
{
    return varsSet == anotherMonom.varsSet;
}

inline bool Monom::operator!=(const Monom& anotherMonom) const
{
    return varsSet != anotherMonom.varsSet;
}

inline bool Monom::operator<(const Monom& anotherMonom) const
{
    int diff = varsSet.size() - anotherMonom.varsSet.size();
    if (diff < 0)
    {
        return true;
    }
    else if (diff > 0)
    {
        return false;
    }
    else
    {
        set<Integer>::const_iterator it(varsSet.begin()),
                                     ait(anotherMonom.varsSet.begin());
        diff = varsSet.size();
        for (register int i = 0; i < diff; ++i)
        {
            if (*it < *ait)
            {
                return false;
            }
            else if (*it > *ait)
            {
                return true;
            }
            else
            {
                it++;
                ait++;
            }
        }
        return false;
    }
}

inline bool Monom::operator>(const Monom& anotherMonom) const
{
    int diff = varsSet.size() - anotherMonom.varsSet.size();
    if (diff < 0)
    {
        return false;
    }
    else if (diff > 0)
    {
        return true;
    }
    else
    {
        set<Integer>::const_iterator it(varsSet.begin()),
                                     ait(anotherMonom.varsSet.begin());
        diff = varsSet.size();
        for (register int i = 0; i < diff; ++i)
        {
            if (*it < *ait)
            {
                return true;
            }
            else if (*it > *ait)
            {
                return false;
            }
            else
            {
               it++;
               ait++;
            }
        }
        return false;
    }
}

inline Monom::Integer Monom::GCD_degree(const Monom& a, const Monom& b)
{
    set<Integer> tmpSet;
    set_intersection(a.varsSet.begin(), a.varsSet.end(),
                     b.varsSet.begin(), b.varsSet.end(),
                     inserter(tmpSet, tmpSet.begin()));

    return tmpSet.size();
}

inline Monom::Integer Monom::LCM_degree(const Monom& a, const Monom& b)
{
    set<Integer> tmpSet;
    set_union(a.varsSet.begin(), a.varsSet.end(),
              b.varsSet.begin(), b.varsSet.end(),
              inserter(tmpSet, tmpSet.begin()));

    return tmpSet.size();
}

inline Monom Monom::GCD(const Monom& a, const Monom& b)
{
    Monom tmpMonom;
    set_intersection(a.varsSet.begin(), a.varsSet.end(),
                     b.varsSet.begin(), b.varsSet.end(),
                     inserter(tmpMonom.varsSet, tmpMonom.varsSet.begin()));

    return tmpMonom;
}

inline Monom Monom::LCM(const Monom& a, const Monom& b)
{
    Monom tmpMonom;
    set_union(a.varsSet.begin(), a.varsSet.end(),
              b.varsSet.begin(), b.varsSet.end(),
              inserter(tmpMonom.varsSet, tmpMonom.varsSet.begin()));

    return tmpMonom;
}

inline Monom::Integer Monom::firstMultiVar() const
{
    Monom::Integer multiVar = 0;
    if (!varsSet.empty())
    {
        multiVar = *varsSet.rbegin();
    }
    return multiVar;
}

#endif // MONOM_H
