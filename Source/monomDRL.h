#ifndef MONOMDRL_H
#define MONOMDRL_H

#include <iostream>
#include <set>

#include "fast_allocator.h"
#include "variables.h"

class MonomDRL
{
public:
    typedef short int Integer;

protected:
    static Integer mDimIndepend;
    static FastAllocator Allocator;
    static Variables* mIndepend;

    struct VarsListNode
    {
        Integer value;
        VarsListNode *next;
        static FastAllocator Allocator;

        void* operator new(size_t) { return Allocator.Allocate(); }
        void operator delete(void *ptr) { Allocator.Free(ptr); }

        VarsListNode(): value(0), next(0) {};
        VarsListNode(Integer newValue, VarsListNode*& newNext):
                value(newValue), next(newNext) {};
        ~VarsListNode() {};
    };
    VarsListNode* mListHead;
    Integer mDegree;

protected:
    VarsListNode* Find(const Integer var) const;

public:
    MonomDRL* mNext;

    static void AddVariable(const char *var);
    static const char* GetVariable(Integer var);
    static Integer DimIndepend();

    MonomDRL();
    MonomDRL(const MonomDRL& anotherMonom);
    ~MonomDRL();

    Integer Degree() const;

    void* operator new(std::size_t);
    void operator delete(void *ptr);
    Integer operator[](Integer var) const;

    const MonomDRL& operator=(const MonomDRL& anotherMonom);
    const MonomDRL& operator*=(Integer var);
    const MonomDRL& operator*=(const MonomDRL& anotherMonom);
    void SetProductOf(const MonomDRL& monomA, Integer var);
    void SetProductOf(const MonomDRL& monomA, const MonomDRL& monomB);
    const MonomDRL& operator/=(const MonomDRL& anotherMonom);
    void SetQuotientOf(const MonomDRL& monomA, const MonomDRL& monomB);

    bool operator==(const MonomDRL& anotherMonom) const;
    bool operator!=(const MonomDRL& anotherMonom) const;
    bool operator<(const MonomDRL& anotherMonom) const;
    bool operator>(const MonomDRL& anotherMonom) const;
    static int Compare(const MonomDRL& monomA, const MonomDRL& monomB);

    void SetOne();

    bool IsDivisibleBy(const MonomDRL& anotherMonom) const;
    bool IsTrueDivisibleBy(const MonomDRL& anotherMonom) const;
    bool IsPommaretDivisibleBy(const MonomDRL& anotherMonom) const;

    friend std::istream& operator>>(std::istream& in, MonomDRL& a);
    friend std::ostream& operator<<(std::ostream& out, const MonomDRL& a);

    static Integer GcdDegree(const MonomDRL& monomA, const MonomDRL& monomB);
    static Integer LcmDegree(const MonomDRL& monomA, const MonomDRL& monomB);
    void SetGcdOf(const MonomDRL& monomA, const MonomDRL& monomB);
    void SetLcmOf(const MonomDRL& monomA, const MonomDRL& monomB);

    Integer FirstMultiVar() const;
    std::set<Integer> GetVariablesSet() const;
};


inline MonomDRL::VarsListNode* MonomDRL::Find(const MonomDRL::Integer var) const
{
    if (!mListHead || mListHead->value < var)
    {
        return 0;
    }

    VarsListNode *previousPointer(mListHead), *currentPointer;
    Integer range(mDegree), middle;

    while ((middle = range >> 1) > 0)
    {
        currentPointer = previousPointer;
        for (register Integer i = 0; i < middle; ++i)
        {
            currentPointer = currentPointer->next;
        }

        if (currentPointer->value > var)
        {
            previousPointer = currentPointer;
            range -= middle;
        }
        else if (currentPointer->value < var)
        {
            range = middle;
        }
        else
        {
            return currentPointer;
        }
    }
    return previousPointer;
}

inline MonomDRL::MonomDRL(): mListHead(0), mDegree(0), mNext(0)
{
}

inline MonomDRL::MonomDRL(const MonomDRL& anotherMonom):
        mListHead(0), mDegree(anotherMonom.mDegree), mNext(0)
{
    if (!anotherMonom.mListHead)
    {
        return;
    }
    else
    {
        VarsListNode **iterator = &mListHead,
                     *iteratorAnother = anotherMonom.mListHead;
        while (iteratorAnother)
        {
            *iterator = new VarsListNode();
            (*iterator)->value = iteratorAnother->value;

            iterator = &((*iterator)->next);
            iteratorAnother = iteratorAnother->next;
        }
    }
}

inline MonomDRL::~MonomDRL()
{
    SetOne();
}

inline MonomDRL::Integer MonomDRL::DimIndepend()
{
    return mDimIndepend;
}

inline MonomDRL::Integer MonomDRL::Degree() const
{
    return mDegree;
}

inline void* MonomDRL::operator new(std::size_t)
{
    return Allocator.Allocate();
}

inline void MonomDRL::operator delete(void *ptr)
{
    Allocator.Free(ptr);
}

inline MonomDRL::Integer MonomDRL::operator[](MonomDRL::Integer var) const
{
    if (!mListHead || mListHead->value < var)
    {
        return 0;
    }

    VarsListNode *previousPointer(mListHead), *currentPointer;
    Integer range(mDegree), middle;

    while (range > 0)
    {
        middle = range >> 1;
        currentPointer = previousPointer;
        for (register Integer i = 0; i < middle; ++i)
        {
            currentPointer = currentPointer->next;
        }

        if (currentPointer->value > var)
        {
            previousPointer = currentPointer->next;
            range -= middle + 1;
        }
        else if (currentPointer->value < var)
        {
            range = middle;
        }
        else
        {
            return 1;
        }
    }
    return previousPointer && previousPointer->value == var;
}

inline const MonomDRL& MonomDRL::operator=(const MonomDRL& anotherMonom)
{
    if (!anotherMonom.mListHead)
    {
        SetOne();
    }
    else
    {
        mDegree = anotherMonom.mDegree;

        VarsListNode *iteratorAnother = anotherMonom.mListHead,
                     **iterator = &mListHead;
        while (*iterator && iteratorAnother)
        {
            (*iterator)->value = iteratorAnother->value;
            iterator = &((*iterator)->next);
            iteratorAnother = iteratorAnother->next;
        }

        if (*iterator)
        {
            VarsListNode *nodeToDelete = (*iterator)->next;
            *iterator = 0;
            while (nodeToDelete)
            {
                iteratorAnother = nodeToDelete;
                nodeToDelete = nodeToDelete->next;
                delete iteratorAnother;
            }
        }

        if (iteratorAnother)
        {
            while (iteratorAnother)
            {
                *iterator = new VarsListNode();
                (*iterator)->value = iteratorAnother->value;

                iterator = &((*iterator)->next);
                iteratorAnother = iteratorAnother->next;
            }
        }
    }
    return *this;
}

inline const MonomDRL& MonomDRL::operator*=(Integer var)
{
    //inserted variable is the only one
    if (!mListHead)
    {
        mListHead = new VarsListNode();
        mListHead->value = var;
        ++mDegree;
    }
    else
    {
        VarsListNode* position = Find(var);
        //inserted variable is the eldest one
        if (!position)
        {
            position = new VarsListNode();
            position->value = var;
            position->next = mListHead;
            mListHead = position;
            ++mDegree;
        }
        //all other cases
        else if(position->value != var)
        {
            VarsListNode* newNode = new VarsListNode();
            newNode->value = var;
            newNode->next = position->next;
            position->next = newNode;
            ++mDegree;
        }
    }

    return *this;
}

inline const MonomDRL& MonomDRL::operator*=(const MonomDRL& anotherMonom)
{
    if (!mListHead)
    {
        *this = anotherMonom;
    }
    else if (anotherMonom.mListHead)
    {
        VarsListNode **iterator = &mListHead,
                     *anotherIterator = anotherMonom.mListHead;

        while (*iterator && anotherIterator)
        {
            if ((*iterator)->value == anotherIterator->value)
            {
                iterator = &((*iterator)->next);
                anotherIterator = anotherIterator->next;
            }
            else if ((*iterator)->value > anotherIterator->value)
            {
                iterator = &((*iterator)->next);
            }
            else
            {
                VarsListNode* newNode = new VarsListNode();
                newNode->value = anotherIterator->value;
                newNode->next = *iterator;
                *iterator = newNode;
                ++mDegree;

                iterator = &(newNode->next);
                anotherIterator = anotherIterator->next;
            }
        }

        while (anotherIterator)
        {
            *iterator = new VarsListNode();
            (*iterator)->value = anotherIterator->value;
            ++mDegree;

            iterator = &((*iterator)->next);
            anotherIterator = anotherIterator->next;
        }
    }

    return *this;
}

inline void MonomDRL::SetProductOf(const MonomDRL& monomA, MonomDRL::Integer var)
{
    *this = monomA;
    *this *= var;
}

inline void MonomDRL::SetProductOf(const MonomDRL& monomA, const MonomDRL& monomB)
{
    SetOne();
    VarsListNode **iterator = &mListHead,
                 *iteratorA = monomA.mListHead,
                 *iteratorB = monomB.mListHead;

    while (iteratorA && iteratorB)
    {
        ++mDegree;
        *iterator = new VarsListNode();
        if (iteratorA->value == iteratorB->value)
        {
            (*iterator)->value = iteratorA->value;
            iteratorA = iteratorA->next;
            iteratorB = iteratorB->next;
        }
        else if (iteratorA->value > iteratorB->value)
        {
            (*iterator)->value = iteratorA->value;
            iteratorA = iteratorA->next;
        }
        else
        {
            (*iterator)->value = iteratorB->value;
            iteratorB = iteratorB->next;
        }
        iterator = &((*iterator)->next);
    }

    while (iteratorA)
    {
        ++mDegree;
        *iterator = new VarsListNode();
        (*iterator)->value = iteratorA->value;
        iterator = &((*iterator)->next);
        iteratorA = iteratorA->next;
    }

    while (iteratorB)
    {
        ++mDegree;
        *iterator = new VarsListNode();
        (*iterator)->value = iteratorB->value;
        iterator = &((*iterator)->next);
        iteratorB = iteratorB->next;
    }
}

inline const MonomDRL& MonomDRL::operator/=(const MonomDRL& anotherMonom)
{
    VarsListNode **iterator = &mListHead,
                 *anotherIterator = anotherMonom.mListHead;

    while (*iterator && anotherIterator)
    {
        if ((*iterator)->value == anotherIterator->value)
        {
            VarsListNode* nodeToDelete = *iterator;
            *iterator = (*iterator)->next;
            delete nodeToDelete;
            mDegree--;
            anotherIterator = anotherIterator->next;
        }
        else if ((*iterator)->value > anotherIterator->value)
        {
            iterator = &((*iterator)->next);
        }
    }

    return *this;
}

inline void MonomDRL::SetQuotientOf(const MonomDRL& monomA, const MonomDRL& monomB)
{
    SetOne();
    VarsListNode **iterator = &mListHead,
                 *iteratorA = monomA.mListHead,
                 *iteratorB = monomB.mListHead;

    while (iteratorA && iteratorB)
    {
        if (iteratorA->value == iteratorB->value)
        {
            iteratorA = iteratorA->next;
            iteratorB = iteratorB->next;
        }
        else
        {
            ++mDegree;
            *iterator = new VarsListNode();
            (*iterator)->value = iteratorA->value;
            iterator = &((*iterator)->next);
            if (iteratorA->value > iteratorB->value)
            {
                iteratorA = iteratorA->next;
            }
        }
    }

    while (iteratorA)
    {
        ++mDegree;
        *iterator = new VarsListNode();
        (*iterator)->value = iteratorA->value;
        iterator = &((*iterator)->next);
        iteratorA = iteratorA->next;
    }
}

inline void MonomDRL::SetOne()
{
    mDegree = 0;
    if (mListHead)
    {
        VarsListNode* tmpNode;
        while (mListHead)
        {
            tmpNode = mListHead;
            mListHead = mListHead->next;
            delete tmpNode;
        }
    }
}

inline bool MonomDRL::IsDivisibleBy(const MonomDRL& anotherMonom) const
{
    VarsListNode *iterator = mListHead,
                 *anotherIterator = anotherMonom.mListHead;
    while (iterator && anotherIterator)
    {
        if (iterator->value == anotherIterator->value)
        {
            iterator = iterator->next;
            anotherIterator = anotherIterator->next;
        }
        else if (iterator->value > anotherIterator->value)
        {
            iterator = iterator->next;
        }
        else
        {
            break;
        }
    }

    return !anotherIterator;
}

inline bool MonomDRL::IsTrueDivisibleBy(const MonomDRL& anotherMonom) const
{
    if (Degree() <= anotherMonom.Degree())
    {
        return false;
    }

    VarsListNode *iterator = mListHead,
                 *anotherIterator = anotherMonom.mListHead;
    while (iterator && anotherIterator)
    {
        if (iterator->value == anotherIterator->value)
        {
            iterator = iterator->next;
            anotherIterator = anotherIterator->next;
        }
        else if (iterator->value > anotherIterator->value)
        {
            iterator = iterator->next;
        }
        else
        {
            break;
        }
    }

    return !anotherIterator;
}

inline bool MonomDRL::IsPommaretDivisibleBy(const MonomDRL& anotherMonom) const
{
    if (mDegree < anotherMonom.mDegree)
    {
        return false;
    }
    if (anotherMonom.mDegree == 0)
    {
        return true;
    }

    VarsListNode *iterator = mListHead,
                 *anotherIterator = anotherMonom.mListHead;
    while (iterator->value != anotherIterator->value)
    {
        iterator = iterator->next;
    }
    while (iterator && anotherIterator)
    {
        if (iterator->value != anotherIterator->value)
        {
            break;
        }
        iterator = iterator->next;
        anotherIterator = anotherIterator->next;
    }

    return !iterator && !anotherIterator;
}

inline bool MonomDRL::operator==(const MonomDRL& anotherMonom) const
{
    if (mDegree != anotherMonom.mDegree)
    {
        return false;
    }
    else
    {
        VarsListNode *iterator = mListHead,
                     *anotherIterator = anotherMonom.mListHead;
        while (anotherIterator)
        {
            if (iterator->value != anotherIterator->value)
            {
                break;
            }
            iterator = iterator->next;
            anotherIterator = anotherIterator->next;
        }
        return !anotherIterator;
    }
}

inline bool MonomDRL::operator!=(const MonomDRL& anotherMonom) const
{
    if (mDegree != anotherMonom.mDegree)
    {
        return true;
    }
    else
    {
        VarsListNode *iterator = mListHead,
                     *anotherIterator = anotherMonom.mListHead;
        while (anotherIterator)
        {
            if (iterator->value != anotherIterator->value)
            {
                break;
            }
            iterator = iterator->next;
            anotherIterator = anotherIterator->next;
        }
        return anotherIterator;
    }
}

inline bool MonomDRL::operator<(const MonomDRL& anotherMonom) const
{
    if (mDegree < anotherMonom.mDegree)
    {
        return true;
    }
    else if (mDegree > anotherMonom.mDegree)
    {
        return false;
    }
    else
    {
        VarsListNode *iterator = mListHead,
                     *anotherIterator = anotherMonom.mListHead;
        while (anotherIterator)
        {
            if (iterator->value < anotherIterator->value)
            {
                return false;
            }
            if (iterator->value > anotherIterator->value)
            {
                return true;
            }
            iterator = iterator->next;
            anotherIterator = anotherIterator->next;
        }
        return false;
    }
}

inline bool MonomDRL::operator>(const MonomDRL& anotherMonom) const
{
    if (mDegree < anotherMonom.mDegree)
    {
        return false;
    }
    else if (mDegree > anotherMonom.mDegree)
    {
        return true;
    }
    else
    {
        VarsListNode *iterator = mListHead,
                     *anotherIterator = anotherMonom.mListHead;
        while (anotherIterator)
        {
            if (iterator->value < anotherIterator->value)
            {
                return true;
            }
            if (iterator->value > anotherIterator->value)
            {
                return false;
            }
            iterator = iterator->next;
            anotherIterator = anotherIterator->next;
        }
        return false;
    }
}

inline MonomDRL::Integer MonomDRL::GcdDegree(const MonomDRL& monomA, const MonomDRL& monomB)
{
    Integer gcd = 0;
    VarsListNode *iteratorA = monomA.mListHead,
                 *iteratorB = monomB.mListHead;

    while (iteratorA && iteratorB)
    {
        if (iteratorA->value == iteratorB->value)
        {
            ++gcd;
            iteratorA = iteratorA->next;
            iteratorB = iteratorB->next;
        }
        else if (iteratorA->value > iteratorB->value)
        {
            iteratorA = iteratorA->next;
        }
        else
        {
            iteratorB = iteratorB->next;
        }
    }
    return gcd;
}

inline MonomDRL::Integer MonomDRL::LcmDegree(const MonomDRL& monomA, const MonomDRL& monomB)
{
    Integer lcm = 0;
    VarsListNode *iteratorA = monomA.mListHead,
                 *iteratorB = monomB.mListHead;

    while (iteratorA && iteratorB)
    {
        ++lcm;
        if (iteratorA->value == iteratorB->value)
        {
            iteratorA = iteratorA->next;
            iteratorB = iteratorB->next;
        }
        else if (iteratorA->value > iteratorB->value)
        {
            iteratorA = iteratorA->next;
        }
        else
        {
            iteratorB = iteratorB->next;
        }
    }

    while (iteratorA)
    {
        ++lcm;
        iteratorA = iteratorA->next;
    }

    while (iteratorB)
    {
        ++lcm;
        iteratorB = iteratorB->next;
    }

    return lcm;
}

inline void MonomDRL::SetGcdOf(const MonomDRL& monomA, const MonomDRL& monomB)
{
    SetOne();
    VarsListNode **iterator = &mListHead,
                 *iteratorA = monomA.mListHead,
                 *iteratorB = monomB.mListHead;

    while (iteratorA && iteratorB)
    {
        if (iteratorA->value == iteratorB->value)
        {
            ++mDegree;
            *iterator = new VarsListNode();
            (*iterator)->value = iteratorA->value;
            iterator = &((*iterator)->next);

            iteratorA = iteratorA->next;
            iteratorB = iteratorB->next;
        }
        else if (iteratorA->value > iteratorB->value)
        {
            iteratorA = iteratorA->next;
        }
        else
        {
            iteratorB = iteratorB->next;
        }
    }
}

inline void MonomDRL::SetLcmOf(const MonomDRL& monomA, const MonomDRL& monomB)
{
    SetProductOf(monomA, monomB);
}

inline MonomDRL::Integer MonomDRL::FirstMultiVar() const
{
    if (!mListHead)
    {
        return 0;
    }
    else
    {
        return mListHead->value;
    }
}

inline std::set<MonomDRL::Integer> MonomDRL::GetVariablesSet() const
{
    std::set<Integer> result;
    VarsListNode *iterator = mListHead;
    while (iterator)
    {
        result.insert(iterator->value);
        iterator = iterator->next;
    }
    return result;
}

#endif // MONOMDRL_H
