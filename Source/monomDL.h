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
    VarsListNode* find(const Integer var) const;

public:
    MonomDL* mNext;

    static void addVariable(const char *var);

    MonomDL();
    MonomDL(const MonomDL& anotherMonom);
    ~MonomDL();

    Integer dimIndepend() const;
    Integer degree() const;

    void* operator new(std::size_t);
    void operator delete(void *ptr);
    Integer operator[](Integer var) const;

    const MonomDL& operator=(const MonomDL& anotherMonom);
    const MonomDL& operator*=(Integer var);
    const MonomDL& operator*=(const MonomDL& anotherMonom);
    void setProductOf(const MonomDL& monomA, Integer var);
    void setProductOf(const MonomDL& monomA, const MonomDL& monomB);
    const MonomDL& operator/=(const MonomDL& anotherMonom);
    void setQuotientOf(const MonomDL& monomA, const MonomDL& monomB);

    bool operator==(const MonomDL& anotherMonom) const;
    bool operator!=(const MonomDL& anotherMonom) const;
    bool operator<(const MonomDL& anotherMonom) const;
    bool operator>(const MonomDL& anotherMonom) const;
    static int compare(const MonomDL& monomA, const MonomDL& monomB);

    void setOne();

    bool isDivisibleBy(const MonomDL& anotherMonom) const;
    bool isTrueDivisibleBy(const MonomDL& anotherMonom) const;
    bool isPommaretDivisibleBy(const MonomDL& anotherMonom) const;

    friend std::istream& operator>>(std::istream& in, MonomDL& a);
    friend std::ostream& operator<<(std::ostream& out, const MonomDL& a);

    static Integer gcdDegree(const MonomDL& monomA, const MonomDL& monomB);
    static Integer lcmDegree(const MonomDL& monomA, const MonomDL& monomB);
    void setGcdOf(const MonomDL& monomA, const MonomDL& monomB);
    void setLcmOf(const MonomDL& monomA, const MonomDL& monomB);

    Integer firstMultiVar() const;
};


inline MonomDL::VarsListNode* MonomDL::find(const MonomDL::Integer var) const
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
    setOne();
}

inline MonomDL::Integer MonomDL::dimIndepend() const
{
    return mDimIndepend;
}

inline MonomDL::Integer MonomDL::degree() const
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
        setOne();
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
        VarsListNode* position = find(var);
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

inline void MonomDL::setProductOf(const MonomDL& monomA, MonomDL::Integer var)
{
    *this = monomA;
    *this *= var;
}

inline void MonomDL::setProductOf(const MonomDL& monomA, const MonomDL& monomB)
{
    setOne();
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

inline void MonomDL::setQuotientOf(const MonomDL& monomA, const MonomDL& monomB)
{
    setOne();
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

inline void MonomDL::setOne()
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

inline bool MonomDL::isDivisibleBy(const MonomDL& anotherMonom) const
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

inline bool MonomDL::isTrueDivisibleBy(const MonomDL& anotherMonom) const
{
    if (degree() <= anotherMonom.degree())
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

inline bool MonomDL::isPommaretDivisibleBy(const MonomDL& anotherMonom) const
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

inline MonomDL::Integer MonomDL::gcdDegree(const MonomDL& monomA, const MonomDL& monomB)
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

inline MonomDL::Integer MonomDL::lcmDegree(const MonomDL& monomA, const MonomDL& monomB)
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

inline void MonomDL::setGcdOf(const MonomDL& monomA, const MonomDL& monomB)
{
    setOne();
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

inline void MonomDL::setLcmOf(const MonomDL& monomA, const MonomDL& monomB)
{
    setProductOf(monomA, monomB);
}

inline MonomDL::Integer MonomDL::firstMultiVar() const
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
