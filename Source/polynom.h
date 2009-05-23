#include <iostream>
#include <set>
#include "monom.h"

#ifndef POLY_H
#define POLY_H

class Polynom
{
protected:
    struct monomPointerComparator
    {
        bool operator()(const Monom* leftOperand, const Monom* rightOperand) const
        {
            return (*leftOperand) > (*rightOperand);
        }
    };
    typedef set<Monom*, monomPointerComparator> MonomInnerSet;

    MonomInnerSet monomSet;

    void additive(std::istream& in);
    void multiplicative(std::istream& in);
    void unary(std::istream& in);
    void bracket(std::istream& in);

public:
    Polynom();
    Polynom(const Polynom& anotherPolynom);
    ~Polynom();

    void setOne();
    void setZero();
    bool isZero() const;
    unsigned int length() const;
    Monom::Integer degree() const;
    const Monom& lm() const;
    void ridOfLm();

    void reduction(const Polynom& anotherPolynom);
    void headReduction(const Polynom& anotherPolynom);

    const Polynom& operator=(const Polynom& anotherPolynom);
    const Polynom& operator+=(const Monom& newMonom);
    const Polynom& operator+=(const Polynom& anotherPolynom);
    Polynom operator+(const Monom& newMonom) const;
    Polynom operator+(const Polynom& anotherPolynom) const;

    const Polynom& operator*=(Monom::Integer var);
    const Polynom& operator*=(const Monom& anotherMonom);
    const Polynom& operator*=(const Polynom& anotherPolynom);
    Polynom operator*(Monom::Integer var) const;
    Polynom operator*(const Monom& anotherMonom) const;
    Polynom operator*(const Polynom& anotherPolynom) const;

    bool operator==(const Polynom &anotherPolynom) const;
    bool operator!=(const Polynom &anotherPolynom) const;


    friend std::ostream& operator<<(std::ostream& out, const Polynom& a);
    friend std::istream& operator>>(std::istream& in, Polynom& a);
};

inline Polynom::Polynom(): monomSet()
{
}

inline Polynom::Polynom(const Polynom& anotherPolynom):
        monomSet()
{
    MonomInnerSet::iterator it(monomSet.begin());
    MonomInnerSet::const_iterator anotherIt(anotherPolynom.monomSet.begin()),
                                  anotherEnd(anotherPolynom.monomSet.end());
    while (anotherIt != anotherEnd)
    {
        monomSet.insert(it, new Monom(**anotherIt));
        it++;
        anotherIt++;
    }
}

inline Polynom::~Polynom()
{
    for (MonomInnerSet::iterator it = monomSet.begin(); it  != monomSet.end(); ++it)
    {
        delete *it;
    }
    monomSet.clear();
}

inline void Polynom::setOne()
{
    for (MonomInnerSet::iterator it = monomSet.begin(); it  != monomSet.end(); ++it)
    {
        delete *it;
    }
    monomSet.clear();
    monomSet.insert(new Monom());
}

inline void Polynom::setZero()
{
    for (MonomInnerSet::iterator it = monomSet.begin(); it  != monomSet.end(); ++it)
    {
        delete *it;
    }
    monomSet.clear();
}

inline bool Polynom::isZero() const
{
    return monomSet.empty();
}

inline unsigned int Polynom::length() const
{
    return monomSet.size();
}

inline Monom::Integer Polynom::degree() const
{
    if (monomSet.empty())
    {
        return 0;
    }
    else
    {
        return (**monomSet.begin()).degree();
    }
}

inline const Monom& Polynom::lm() const
{
    return **monomSet.begin();
}

inline void Polynom::ridOfLm()
{
    monomSet.erase(monomSet.begin());
}

inline const Polynom& Polynom::operator=(const Polynom& anotherPolynom)
{
    MonomInnerSet::iterator it;
    for (it = monomSet.begin(); it  != monomSet.end(); ++it)
    {
        delete *it;
    }
    monomSet.clear();

    it = monomSet.begin();
    MonomInnerSet::const_iterator anotherIt(anotherPolynom.monomSet.begin()),
                                            anotherEnd(anotherPolynom.monomSet.end());
    while (anotherIt != anotherEnd)
    {
        monomSet.insert(it, new Monom(**anotherIt));
        it++;
        anotherIt++;
    }

    return *this;
}

inline bool Polynom::operator==(const Polynom &anotherPolynom) const
{
    if (monomSet.size() != anotherPolynom.monomSet.size())
    {
        return false;
    }

    MonomInnerSet::const_iterator it(monomSet.begin()),
                                  anotherIt(anotherPolynom.monomSet.begin());
    while (it != monomSet.end() &&
           anotherIt != anotherPolynom.monomSet.end())
    {
        if (**it != **anotherIt)
        {
            return false;
        }
        it++;
        anotherIt++;
    }

    if (it != monomSet.end() ||
        anotherIt != anotherPolynom.monomSet.end())
    {
        return false;
    }
    else
    {
        return true;
    }
}

inline bool Polynom::operator!=(const Polynom &anotherPolynom) const
{
    return !(*this == anotherPolynom);
}

#endif // POLY_H
