#ifndef MONOMDL_H
#define MONOMDL_H

#include <iostream>

#include "variables.h"
#include "allocator.h"

using namespace std;

class MonomDL
{
public:
    typedef short int Integer;

protected:
    static Integer mDimIndepend;
    static Allocator mAllocator;
    static Variables* mIndepend;

    struct VarsListNode
    {
        Integer value;
        VarsListNode *next;
        static Allocator vlnAllocator;

        void* operator new(size_t) { return vlnAllocator.allocate(); }
        void operator delete(void *ptr) { vlnAllocator.deallocate(ptr); }

        VarsListNode(): value(0), next(NULL) {};
        VarsListNode(Integer newValue, VarsListNode*& newNext):
                value(newValue), next(newNext) {};
        ~VarsListNode() {};
    };
    VarsListNode* mListHead;
    Integer mDegree;

protected:
    VarsListNode* Find(const Integer var) const;

public:
    MonomDL* mNext;

    static void AddVariable(const char *var);
    static const char* GetVariable(Integer var);
    static Integer DimIndepend();

    MonomDL();
    MonomDL(const MonomDL& anotherMonom);
    ~MonomDL();

    Integer Degree() const;

    void* operator new(std::size_t);
    void operator delete(void *ptr);
    Integer operator[](Integer var) const;

    const MonomDL& operator=(const MonomDL& anotherMonom);
    const MonomDL& operator*=(Integer var);
    const MonomDL& operator*=(const MonomDL& anotherMonom);
    void SetProductOf(const MonomDL& monomA, Integer var);
    void SetProductOf(const MonomDL& monomA, const MonomDL& monomB);
    const MonomDL& operator/=(const MonomDL& anotherMonom);
    void SetQuotientOf(const MonomDL& monomA, const MonomDL& monomB);

    bool operator==(const MonomDL& anotherMonom) const;
    bool operator!=(const MonomDL& anotherMonom) const;
    bool operator<(const MonomDL& anotherMonom) const;
    bool operator>(const MonomDL& anotherMonom) const;
    static int Compare(const MonomDL& monomA, const MonomDL& monomB);

    void SetOne();

    bool IsDivisibleBy(const MonomDL& anotherMonom) const;
    bool IsTrueDivisibleBy(const MonomDL& anotherMonom) const;
    bool IsPommaretDivisibleBy(const MonomDL& anotherMonom) const;

    friend std::istream& operator>>(std::istream& in, MonomDL& a);
    friend std::ostream& operator<<(std::ostream& out, const MonomDL& a);

    static Integer GcdDegree(const MonomDL& monomA, const MonomDL& monomB);
    static Integer LcmDegree(const MonomDL& monomA, const MonomDL& monomB);
    void SetGcdOf(const MonomDL& monomA, const MonomDL& monomB);
    void SetLcmOf(const MonomDL& monomA, const MonomDL& monomB);

    Integer FirstMultiVar() const;
};


inline MonomDL::VarsListNode* MonomDL::Find(const MonomDL::Integer var) const
{
    if (mListHead == NULL || mListHead->value > var)
    {
        return NULL;
    }

    VarsListNode *previousPointer(mListHead), *currentPointer;
    Integer range(mDegree), middle;

    while ((middle = range >> 1) > 0)
    {
        currentPointer = previousPointer;
        for (register Integer i = 0; i < middle; i++)
        {
            currentPointer = currentPointer->next;
        }

        if (currentPointer->value < var)
        {
            previousPointer = currentPointer;
            range -= middle;
        }
        else if (currentPointer->value > var)
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

inline MonomDL::MonomDL(): mListHead(NULL), mDegree(0), mNext(NULL)
{
}

inline MonomDL::MonomDL(const MonomDL& anotherMonom):
        mListHead(NULL), mDegree(anotherMonom.mDegree), mNext(NULL)
{
    if (anotherMonom.mListHead == NULL)
    {
        return;
    }
    else
    {
        VarsListNode **iterator = &mListHead,
                     *iteratorAnother = anotherMonom.mListHead;
        while (iteratorAnother != NULL)
        {
            *iterator = new VarsListNode();
            (*iterator)->value = iteratorAnother->value;

            iterator = &((*iterator)->next);
            iteratorAnother = iteratorAnother->next;
        }
    }
}

inline MonomDL::~MonomDL()
{
    SetOne();
}

inline MonomDL::Integer MonomDL::DimIndepend()
{
    return mDimIndepend;
}

inline MonomDL::Integer MonomDL::Degree() const
{
    return mDegree;
}

inline void* MonomDL::operator new(std::size_t)
{
    return mAllocator.allocate();
}

inline void MonomDL::operator delete(void *ptr)
{
    mAllocator.deallocate(ptr);
}

inline MonomDL::Integer MonomDL::operator[](MonomDL::Integer var) const
{
    if (mListHead == NULL || mListHead->value > var)
    {
        return 0;
    }

    VarsListNode *previousPointer(mListHead), *currentPointer;
    Integer range(mDegree), middle;

    while (range > 0)
    {
        middle = range >> 1;
        currentPointer = previousPointer;
        for (register Integer i = 0; i < middle; i++)
        {
            currentPointer = currentPointer->next;
        }

        if (currentPointer->value < var)
        {
            previousPointer = currentPointer->next;
            range -= middle + 1;
        }
        else if (currentPointer->value > var)
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

inline const MonomDL& MonomDL::operator=(const MonomDL& anotherMonom)
{
    if (anotherMonom.mListHead == NULL)
    {
        SetOne();
    }
    else
    {
        mDegree = anotherMonom.mDegree;

        VarsListNode *iteratorAnother = anotherMonom.mListHead,
                     **iterator = &mListHead;
        while (*iterator != NULL && iteratorAnother != NULL)
        {
            (*iterator)->value = iteratorAnother->value;
            iterator = &((*iterator)->next);
            iteratorAnother = iteratorAnother->next;
        }

        if (*iterator != NULL)
        {
            VarsListNode *nodeToDelete = (*iterator)->next;
            *iterator = NULL;
            while (nodeToDelete != NULL)
            {
                iteratorAnother = nodeToDelete;
                nodeToDelete = nodeToDelete->next;
                delete iteratorAnother;
            }
        }

        if (iteratorAnother != NULL)
        {
            while (iteratorAnother != NULL)
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

inline const MonomDL& MonomDL::operator*=(Integer var)
{
    //inserted variable is the only one
    if (mListHead == NULL)
    {
        mListHead = new VarsListNode();
        mListHead->value = var;
        mDegree++;
    }
    else
    {
        VarsListNode* position = Find(var);
        //inserted variable is the eldest one
        if (position == NULL)
        {
            position = new VarsListNode();
            position->value = var;
            position->next = mListHead;
            mListHead = position;
            mDegree++;
        }
        //all other cases
        else if(position->value != var)
        {
            VarsListNode* newNode = new VarsListNode();
            newNode->value = var;
            newNode->next = position->next;
            position->next = newNode;
            mDegree++;
        }
    }

    return *this;
}

inline const MonomDL& MonomDL::operator*=(const MonomDL& anotherMonom)
{
    if (mListHead == NULL)
    {
        *this = anotherMonom;
    }
    else if (anotherMonom.mListHead != NULL)
    {
        VarsListNode **iterator = &mListHead,
                     *anotherIterator = anotherMonom.mListHead;

        while (*iterator != NULL && anotherIterator != NULL)
        {
            if ((*iterator)->value == anotherIterator->value)
            {
                iterator = &((*iterator)->next);
                anotherIterator = anotherIterator->next;
            }
            else if ((*iterator)->value < anotherIterator->value)
            {
                iterator = &((*iterator)->next);
            }
            else
            {
                VarsListNode* newNode = new VarsListNode();
                newNode->value = anotherIterator->value;
                newNode->next = *iterator;
                *iterator = newNode;
                mDegree++;

                iterator = &(newNode->next);
                anotherIterator = anotherIterator->next;
            }
        }

        while (anotherIterator != NULL)
        {
            *iterator = new VarsListNode();
            (*iterator)->value = anotherIterator->value;
            mDegree++;

            iterator = &((*iterator)->next);
            anotherIterator = anotherIterator->next;
        }
    }

    return *this;
}

inline void MonomDL::SetProductOf(const MonomDL& monomA, MonomDL::Integer var)
{
    *this = monomA;
    *this *= var;
}

inline void MonomDL::SetProductOf(const MonomDL& monomA, const MonomDL& monomB)
{
    SetOne();
    VarsListNode **iterator = &mListHead,
                 *iteratorA = monomA.mListHead,
                 *iteratorB = monomB.mListHead;

    while (iteratorA != NULL && iteratorB != NULL)
    {
        mDegree++;
        *iterator = new VarsListNode();
        if (iteratorA->value == iteratorB->value)
        {
            (*iterator)->value = iteratorA->value;
            iteratorA = iteratorA->next;
            iteratorB = iteratorB->next;
        }
        else if (iteratorA->value < iteratorB->value)
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

    while (iteratorA != NULL)
    {
        mDegree++;
        *iterator = new VarsListNode();
        (*iterator)->value = iteratorA->value;
        iterator = &((*iterator)->next);
        iteratorA = iteratorA->next;
    }

    while (iteratorB != NULL)
    {
        mDegree++;
        *iterator = new VarsListNode();
        (*iterator)->value = iteratorB->value;
        iterator = &((*iterator)->next);
        iteratorB = iteratorB->next;
    }
}

inline const MonomDL& MonomDL::operator/=(const MonomDL& anotherMonom)
{
    VarsListNode **iterator = &mListHead,
                 *anotherIterator = anotherMonom.mListHead;

    while (*iterator != NULL && anotherIterator != NULL)
    {
        if ((*iterator)->value == anotherIterator->value)
        {
            VarsListNode* nodeToDelete = *iterator;
            *iterator = (*iterator)->next;
            delete nodeToDelete;
            mDegree--;
            anotherIterator = anotherIterator->next;
        }
        else if ((*iterator)->value < anotherIterator->value)
        {
            iterator = &((*iterator)->next);
        }
    }

    return *this;
}

inline void MonomDL::SetQuotientOf(const MonomDL& monomA, const MonomDL& monomB)
{
    SetOne();
    VarsListNode **iterator = &mListHead,
                 *iteratorA = monomA.mListHead,
                 *iteratorB = monomB.mListHead;

    while (iteratorA != NULL && iteratorB != NULL)
    {
        if (iteratorA->value == iteratorB->value)
        {
            iteratorA = iteratorA->next;
            iteratorB = iteratorB->next;
        }
        else
        {
            mDegree++;
            *iterator = new VarsListNode();
            (*iterator)->value = iteratorA->value;
            iterator = &((*iterator)->next);
            if (iteratorA->value < iteratorB->value)
            {
                iteratorA = iteratorA->next;
            }
        }
    }

    while (iteratorA != NULL)
    {
        mDegree++;
        *iterator = new VarsListNode();
        (*iterator)->value = iteratorA->value;
        iterator = &((*iterator)->next);
        iteratorA = iteratorA->next;
    }
}

inline void MonomDL::SetOne()
{
    mDegree = 0;
    if (mListHead != NULL)
    {
        VarsListNode* tmpNode;
        while (mListHead != NULL)
        {
            tmpNode = mListHead;
            mListHead = mListHead->next;
            delete tmpNode;
        }
    }
}

inline bool MonomDL::IsDivisibleBy(const MonomDL& anotherMonom) const
{
    VarsListNode *iterator(mListHead),
                 *anotherIterator(anotherMonom.mListHead);
    while (iterator != NULL && anotherIterator != NULL)
    {
        if (iterator->value == anotherIterator->value)
        {
            iterator = iterator->next;
            anotherIterator = anotherIterator->next;
        }
        else if (iterator->value < anotherIterator->value)
        {
            iterator = iterator->next;
        }
        else
        {
            break;
        }
    }

    return anotherIterator == NULL;
}

inline bool MonomDL::IsTrueDivisibleBy(const MonomDL& anotherMonom) const
{
    if (Degree() <= anotherMonom.Degree())
    {
        return false;
    }

    VarsListNode *iterator(mListHead),
                 *anotherIterator(anotherMonom.mListHead);
    while (iterator != NULL && anotherIterator != NULL)
    {
        if (iterator->value == anotherIterator->value)
        {
            iterator = iterator->next;
            anotherIterator = anotherIterator->next;
        }
        else if (iterator->value < anotherIterator->value)
        {
            iterator = iterator->next;
        }
        else
        {
            break;
        }
    }

    return anotherIterator == NULL;
}

inline bool MonomDL::IsPommaretDivisibleBy(const MonomDL& anotherMonom) const
{
    if (mDegree < anotherMonom.mDegree)
    {
        return false;
    }
    if (anotherMonom.mDegree == 0)
    {
        return true;
    }

    VarsListNode *iterator(mListHead),
                 *anotherIterator(anotherMonom.mListHead);
    while (iterator != NULL && anotherIterator != NULL)
    {
        if (iterator->value != anotherIterator->value)
        {
            break;
        }
        iterator = iterator->next;
        anotherIterator = anotherIterator->next;
    }

    return anotherIterator == NULL;
}

inline bool MonomDL::operator==(const MonomDL& anotherMonom) const
{
    if (mDegree != anotherMonom.mDegree)
    {
        return false;
    }
    else
    {
        VarsListNode *iterator(mListHead),
                     *anotherIterator(anotherMonom.mListHead);
        while (anotherIterator != NULL)
        {
            if (iterator->value != anotherIterator->value)
            {
                break;
            }
            iterator = iterator->next;
            anotherIterator = anotherIterator->next;
        }
        return anotherIterator == NULL;
    }
}

inline bool MonomDL::operator!=(const MonomDL& anotherMonom) const
{
    if (mDegree != anotherMonom.mDegree)
    {
        return true;
    }
    else
    {
        VarsListNode *iterator(mListHead),
                     *anotherIterator(anotherMonom.mListHead);
        while (anotherIterator != NULL)
        {
            if (iterator->value != anotherIterator->value)
            {
                break;
            }
            iterator = iterator->next;
            anotherIterator = anotherIterator->next;
        }
        return anotherIterator != NULL;
    }
}

inline bool MonomDL::operator<(const MonomDL& anotherMonom) const
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
        VarsListNode *iterator(mListHead),
                     *anotherIterator(anotherMonom.mListHead);
        while (anotherIterator != NULL)
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

inline bool MonomDL::operator>(const MonomDL& anotherMonom) const
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
        VarsListNode *iterator(mListHead),
                     *anotherIterator(anotherMonom.mListHead);
        while (anotherIterator != NULL)
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

inline MonomDL::Integer MonomDL::GcdDegree(const MonomDL& monomA, const MonomDL& monomB)
{
    Integer gcd = 0;
    VarsListNode *iteratorA(monomA.mListHead),
                 *iteratorB(monomB.mListHead);

    while (iteratorA != NULL && iteratorB != NULL)
    {
        if (iteratorA->value == iteratorB->value)
        {
            gcd++;
            iteratorA = iteratorA->next;
            iteratorB = iteratorB->next;
        }
        else if (iteratorA->value < iteratorB->value)
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

inline MonomDL::Integer MonomDL::LcmDegree(const MonomDL& monomA, const MonomDL& monomB)
{
    Integer lcm = 0;
    VarsListNode *iteratorA(monomA.mListHead),
                 *iteratorB(monomB.mListHead);

    while (iteratorA != NULL && iteratorB != NULL)
    {
        lcm++;
        if (iteratorA->value == iteratorB->value)
        {
            iteratorA = iteratorA->next;
            iteratorB = iteratorB->next;
        }
        else if (iteratorA->value < iteratorB->value)
        {
            iteratorA = iteratorA->next;
        }
        else
        {
            iteratorB = iteratorB->next;
        }
    }

    while (iteratorA != NULL)
    {
        lcm++;
        iteratorA = iteratorA->next;
    }

    while (iteratorB != NULL)
    {
        lcm++;
        iteratorB = iteratorB->next;
    }

    return lcm;
}

inline void MonomDL::SetGcdOf(const MonomDL& monomA, const MonomDL& monomB)
{
    SetOne();
    VarsListNode **iterator = &mListHead,
                 *iteratorA = monomA.mListHead,
                 *iteratorB = monomB.mListHead;

    while (iteratorA != NULL && iteratorB != NULL)
    {
        if (iteratorA->value == iteratorB->value)
        {
            mDegree++;
            *iterator = new VarsListNode();
            (*iterator)->value = iteratorA->value;
            iterator = &((*iterator)->next);

            iteratorA = iteratorA->next;
            iteratorB = iteratorB->next;
        }
        else if (iteratorA->value < iteratorB->value)
        {
            iteratorA = iteratorA->next;
        }
        else
        {
            iteratorB = iteratorB->next;
        }
    }
}

inline void MonomDL::SetLcmOf(const MonomDL& monomA, const MonomDL& monomB)
{
    SetProductOf(monomA, monomB);
}

inline MonomDL::Integer MonomDL::FirstMultiVar() const
{
    if (mListHead == NULL)
    {
        return 0;
    }

    VarsListNode* iterator(mListHead);
    while (iterator->next != NULL)
    {
        iterator = iterator->next;
    }
    return iterator->value;
}

#endif // MONOMDRL_H
