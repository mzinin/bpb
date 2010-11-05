#ifndef POLYNOM_H
#define POLYNOM_H

#include <iostream>

#include "monom.h"
#include "fast_allocator.h"


class Polynom
{
private:
    static FastAllocator Allocator;
    Monom* MonomListHead;

public:
    Polynom();
    Polynom(const Polynom& anotherPolynom);
    ~Polynom();

    void SetOne();
    void SetZero();
    bool IsZero() const;
    unsigned long Length() const;
    Monom::Integer Degree() const;
    const Monom& Lm() const;
    void RidOfLm();

    void Reduction(const Polynom& anotherPolynom);
    void HeadReduction(const Polynom& anotherPolynom);
    void MergeWith(Polynom& anotherPolynom);

    void* operator new(std::size_t);
    void operator delete(void *ptr);

    const Polynom& operator=(const Polynom& anotherPolynom);
    const Polynom& operator+=(const Monom& newMonom);
    const Polynom& operator+=(const Polynom& anotherPolynom);

    const Polynom& operator*=(Monom::Integer var);
    const Polynom& operator*=(const Monom& anotherMonom);
    const Polynom& operator*=(const Polynom& anotherPolynom);

    bool operator==(const Polynom &anotherPolynom) const;
    bool operator!=(const Polynom &anotherPolynom) const;

    friend std::ostream& operator<<(std::ostream& out, const Polynom& polynom);
    friend std::istream& operator>>(std::istream& in, Polynom& polynom);

    bool operator<(const Polynom& anotherPolynom) const;
    bool operator>(const Polynom& anotherPolynom) const;
    static int Compare(const Polynom& polynomA, const Polynom& polynomB);

    std::string ToString() const;

private:
    void Additive(std::istream& in);
    void Multiplicative(std::istream& in);
    void Unary(std::istream& in);
    void Bracket(std::istream& in);
    const Monom * const * Find(const Monom& monom) const;
};

inline Polynom::Polynom()
    : MonomListHead(0)
{
}

inline Polynom::Polynom(const Polynom& anotherPolynom)
    : MonomListHead(0)
{
    if (!anotherPolynom.MonomListHead)
    {
        return;
    }
    else
    {
        Monom **iterator = &MonomListHead,
              *iteratorAnother = anotherPolynom.MonomListHead;
        while (iteratorAnother)
        {
            *iterator = new Monom(*iteratorAnother);

            iterator = &((*iterator)->mNext);
            iteratorAnother = iteratorAnother->mNext;
        }
    }
}

inline Polynom::~Polynom()
{
    SetZero();
}

inline const Monom * const * Polynom::Find(const Monom& monom) const
{
    if (!MonomListHead || *MonomListHead < monom)
    {
        return 0;
    }

    Monom * const *previousPointer = &MonomListHead,
          * const *currentPointer;
    unsigned long range(Length()), middle;

    while ((middle = range >> 1) > 0)
    {
        currentPointer = previousPointer;
        for (register unsigned long i = 0; i < middle; ++i)
        {
            currentPointer = &((*currentPointer)->mNext);
        }

        switch (Monom::Compare(**currentPointer, monom))
        {
        case 1:
            previousPointer = currentPointer;
            range -= middle;
            break;
        case -1:
            range = middle;
            break;
        case 0:
            return currentPointer;
        }
    }
    //return &((*previousPointer)->mNext);
    return previousPointer;
}

inline void Polynom::SetOne()
{
    SetZero();
    MonomListHead = new Monom();
}

inline void Polynom::SetZero()
{
    if (MonomListHead)
    {
        Monom* tmpMonom;
        while (MonomListHead)
        {
            tmpMonom = MonomListHead;
            MonomListHead = MonomListHead->mNext;
            delete tmpMonom;
        }
    }
}

inline bool Polynom::IsZero() const
{
    return !MonomListHead;
}

inline unsigned long Polynom::Length() const
{
    unsigned long length = 0;
    Monom* iterator(MonomListHead);
    while (iterator)
    {
        iterator = iterator->mNext;
        ++length;
    }
    return length;
}

inline Monom::Integer Polynom::Degree() const
{
    if (!MonomListHead)
    {
        return 0;
    }
    else
    {
        return MonomListHead->Degree();
    }
}

inline const Monom& Polynom::Lm() const
{
    if (MonomListHead)
    {
        return *MonomListHead;
    }
    else
    {
        static Monom nullMonom = Monom();
        return nullMonom;
    }
}

inline void Polynom::RidOfLm()
{
    if (MonomListHead)
    {
        Monom* tmpMonom(MonomListHead);
        MonomListHead = MonomListHead->mNext;
        delete tmpMonom;
    }
}

inline void* Polynom::operator new(std::size_t)
{
    return Allocator.Allocate();
}

inline void Polynom::operator delete(void *ptr)
{
    Allocator.Free(ptr);
}

inline const Polynom& Polynom::operator=(const Polynom& anotherPolynom)
{
    if (!anotherPolynom.MonomListHead)
    {
        SetZero();
    }
    else
    {
        Monom *iteratorAnother = anotherPolynom.MonomListHead,
              **iterator = &MonomListHead;
        while (*iterator && iteratorAnother)
        {
            **iterator = *iteratorAnother;
            iterator = &((*iterator)->mNext);
            iteratorAnother = iteratorAnother->mNext;
        }

        if (*iterator)
        {
            Monom* monomToDelete = (*iterator)->mNext;
            *iterator = 0;
            while (monomToDelete)
            {
                iteratorAnother = monomToDelete;
                monomToDelete = monomToDelete->mNext;
                delete iteratorAnother;
            }
        }

        while (iteratorAnother)
        {
            *iterator = new Monom(*iteratorAnother);
            iterator = &((*iterator)->mNext);
            iteratorAnother = iteratorAnother->mNext;
        }
    }
    return *this;
}

inline bool Polynom::operator==(const Polynom &anotherPolynom) const
{
    Monom *iterator(MonomListHead),
          *anotherIterator(anotherPolynom.MonomListHead);
    while (iterator && anotherIterator)
    {
        if (*iterator != *anotherIterator)
        {
            break;
        }
        iterator = iterator->mNext;
        anotherIterator = anotherIterator->mNext;
    }
    return !iterator && !anotherIterator;
}

inline bool Polynom::operator!=(const Polynom &anotherPolynom) const
{
    Monom *iterator(MonomListHead),
          *anotherIterator(anotherPolynom.MonomListHead);
    while (iterator && anotherIterator)
    {
        if (*iterator != *anotherIterator)
        {
            break;
        }
        iterator = iterator->mNext;
        anotherIterator = anotherIterator->mNext;
    }
    return iterator || anotherIterator;
}

inline bool Polynom::operator<(const Polynom& anotherPolynom) const
{
    Monom *iterator(MonomListHead),
          *anotherIterator(anotherPolynom.MonomListHead);
    while (iterator && anotherIterator)
    {
        switch (Monom::Compare(*iterator, *anotherIterator))
        {
            case -1:
                return true;
                break;
            case 1:
                return false;
                break;
            case 0:
                iterator = iterator->mNext;
                anotherIterator = anotherIterator->mNext;
                break;
        }
    }
    return !iterator && !anotherIterator;
}

inline bool Polynom::operator>(const Polynom& anotherPolynom) const
{
    Monom *iterator(MonomListHead),
          *anotherIterator(anotherPolynom.MonomListHead);
    while (iterator && anotherIterator)
    {
        switch (Monom::Compare(*iterator, *anotherIterator))
        {
            case -1:
                return false;
                break;
            case 1:
                return true;
                break;
            case 0:
                iterator = iterator->mNext;
                anotherIterator = anotherIterator->mNext;
                break;
        }
    }
    return iterator && !anotherIterator;
}

inline int Polynom::Compare(const Polynom& polynomA, const Polynom& polynomB)
{
    Monom *iteratorA(polynomA.MonomListHead),
          *iteratorB(polynomB.MonomListHead);
    while (iteratorA && iteratorB)
    {
        switch (Monom::Compare(*iteratorA, *iteratorB))
        {
            case -1:
                return -1;
                break;
            case 1:
                return 1;
                break;
            case 0:
                iteratorA = iteratorA->mNext;
                iteratorB = iteratorB->mNext;
                break;
        }
    }

    if (iteratorA)
    {
        return 1;
    }
    else if (iteratorB)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

#endif // POLYNOM_H
