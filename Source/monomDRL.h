#ifndef MONOMDRL_H
#define MONOMDRL_H

#include <iostream>

#include "variables.h"
#include "allocator.h"

using namespace std;

class MonomDRL
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
    MonomDRL* mNext;

    static void addVariable(const char *var);

    MonomDRL();
    MonomDRL(const MonomDRL& anotherMonom);
    ~MonomDRL();

    Integer dimIndepend() const;
    Integer degree() const;

    void* operator new(std::size_t);
    void operator delete(void *ptr);
    Integer operator[](Integer var) const;

    const MonomDRL& operator=(const MonomDRL& anotherMonom);
    const MonomDRL& operator*=(Integer var);
    const MonomDRL& operator*=(const MonomDRL& anotherMonom);
    void setProductOf(const MonomDRL& monomA, Integer var);
    void setProductOf(const MonomDRL& monomA, const MonomDRL& monomB);
    const MonomDRL& operator/=(const MonomDRL& anotherMonom);
    void setQuotientOf(const MonomDRL& monomA, const MonomDRL& monomB);

    bool operator==(const MonomDRL& anotherMonom) const;
    bool operator!=(const MonomDRL& anotherMonom) const;
    bool operator<(const MonomDRL& anotherMonom) const;
    bool operator>(const MonomDRL& anotherMonom) const;
    static int compare(const MonomDRL& monomA, const MonomDRL& monomB);

    void setOne();

    bool isDivisibleBy(const MonomDRL& anotherMonom) const;
    bool isTrueDivisibleBy(const MonomDRL& anotherMonom) const;
    bool isPommaretDivisibleBy(const MonomDRL& anotherMonom) const;

    friend std::istream& operator>>(std::istream& in, MonomDRL& a);
    friend std::ostream& operator<<(std::ostream& out, const MonomDRL& a);

    static Integer gcdDegree(const MonomDRL& monomA, const MonomDRL& monomB);
    static Integer lcmDegree(const MonomDRL& monomA, const MonomDRL& monomB);
    void setGcdOf(const MonomDRL& monomA, const MonomDRL& monomB);
    void setLcmOf(const MonomDRL& monomA, const MonomDRL& monomB);

    Integer firstMultiVar() const;
};


inline MonomDRL::VarsListNode* MonomDRL::find(const MonomDRL::Integer var) const
{
    if (mListHead == NULL || mListHead->value < var)
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

inline MonomDRL::MonomDRL(): mListHead(NULL), mDegree(0), mNext(NULL)
{
}

inline MonomDRL::MonomDRL(const MonomDRL& anotherMonom):
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

inline MonomDRL::~MonomDRL()
{
    setOne();
}

inline MonomDRL::Integer MonomDRL::dimIndepend() const
{
    return mDimIndepend;
}

inline MonomDRL::Integer MonomDRL::degree() const
{
    return mDegree;
}

inline void* MonomDRL::operator new(std::size_t)
{
    return mAllocator.allocate();
}

inline void MonomDRL::operator delete(void *ptr)
{
    mAllocator.deallocate(ptr);
}

inline MonomDRL::Integer MonomDRL::operator[](MonomDRL::Integer var) const
{
    if (mListHead == NULL || mListHead->value < var)
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

inline const MonomDRL& MonomDRL::operator*=(Integer var)
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

inline const MonomDRL& MonomDRL::operator*=(const MonomDRL& anotherMonom)
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

inline void MonomDRL::setProductOf(const MonomDRL& monomA, MonomDRL::Integer var)
{
    *this = monomA;
    *this *= var;
}

inline void MonomDRL::setProductOf(const MonomDRL& monomA, const MonomDRL& monomB)
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

inline const MonomDRL& MonomDRL::operator/=(const MonomDRL& anotherMonom)
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
        else if ((*iterator)->value > anotherIterator->value)
        {
            iterator = &((*iterator)->next);
        }
    }

    return *this;
}

inline void MonomDRL::setQuotientOf(const MonomDRL& monomA, const MonomDRL& monomB)
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
            if (iteratorA->value > iteratorB->value)
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

inline void MonomDRL::setOne()
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

inline bool MonomDRL::isDivisibleBy(const MonomDRL& anotherMonom) const
{
    VarsListNode *iterator = mListHead,
                 *anotherIterator = anotherMonom.mListHead;
    while (iterator != NULL && anotherIterator != NULL)
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

    return anotherIterator == NULL;
}

inline bool MonomDRL::isTrueDivisibleBy(const MonomDRL& anotherMonom) const
{
    if (degree() <= anotherMonom.degree())
    {
        return false;
    }

    VarsListNode *iterator = mListHead,
                 *anotherIterator = anotherMonom.mListHead;
    while (iterator != NULL && anotherIterator != NULL)
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

    return anotherIterator == NULL;
}

inline bool MonomDRL::isPommaretDivisibleBy(const MonomDRL& anotherMonom) const
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
    while (iterator != NULL && anotherIterator != NULL)
    {
        if (iterator->value != anotherIterator->value)
        {
            break;
        }
        iterator = iterator->next;
        anotherIterator = anotherIterator->next;
    }

    return iterator == NULL && anotherIterator == NULL;
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

inline MonomDRL::Integer MonomDRL::gcdDegree(const MonomDRL& monomA, const MonomDRL& monomB)
{
    Integer gcd = 0;
    VarsListNode *iteratorA = monomA.mListHead,
                 *iteratorB = monomB.mListHead;

    while (iteratorA != NULL && iteratorB != NULL)
    {
        if (iteratorA->value == iteratorB->value)
        {
            gcd++;
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

inline MonomDRL::Integer MonomDRL::lcmDegree(const MonomDRL& monomA, const MonomDRL& monomB)
{
    Integer lcm = 0;
    VarsListNode *iteratorA = monomA.mListHead,
                 *iteratorB = monomB.mListHead;

    while (iteratorA != NULL && iteratorB != NULL)
    {
        lcm++;
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

inline void MonomDRL::setGcdOf(const MonomDRL& monomA, const MonomDRL& monomB)
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

inline void MonomDRL::setLcmOf(const MonomDRL& monomA, const MonomDRL& monomB)
{
    setProductOf(monomA, monomB);
}

inline MonomDRL::Integer MonomDRL::firstMultiVar() const
{
    if (mListHead == NULL)
    {
        return 0;
    }
    else
    {
        return mListHead->value;
    }
}

#endif // MONOMDRL_H
