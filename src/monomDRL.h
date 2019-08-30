#pragma once

#include "fast_allocator.h"
#include "monom.h"

#include <set>
#include <string>


class MonomDRL : public Monom
{
public:
    MonomDRL* next = nullptr;

public:
    MonomDRL() = default;
    MonomDRL(const MonomDRL& anotherMonom);
    MonomDRL(const std::string& str);
    ~MonomDRL();

    void* operator new(std::size_t);
    void operator delete(void* ptr);

    void setOne() override;
    Integer operator[](Integer var) const override;

    const MonomDRL& operator=(const MonomDRL& anotherMonom);
    const MonomDRL& operator*=(Integer var);
    const MonomDRL& operator*=(const MonomDRL& anotherMonom);
    const MonomDRL& operator/=(const MonomDRL& anotherMonom);

    void setQuotientOf(const MonomDRL& monomA, const MonomDRL& monomB);

    bool operator==(const MonomDRL& anotherMonom) const;
    bool operator!=(const MonomDRL& anotherMonom) const;

    bool operator<(const MonomDRL& anotherMonom) const;
    bool operator>(const MonomDRL& anotherMonom) const;
    int compare(const MonomDRL& anotherMonom);

    bool isDivisibleBy(const MonomDRL& anotherMonom) const;
    bool isTrueDivisibleBy(const MonomDRL& anotherMonom) const;
    bool isPommaretDivisibleBy(const MonomDRL& anotherMonom) const;

    Integer firstMultiVar() const override;
    std::set<Integer> variablesSet() const override;

private:
    void multiplyBy(Integer var) override;
    VarsListNode* find(const Integer var) const;

private:
    static FastAllocator allocator_;
};


inline MonomDRL::MonomDRL(const MonomDRL& anotherMonom)
{
    if (!anotherMonom.listHead_)
    {
        return;
    }

    totalDegree_ = anotherMonom.totalDegree_;
    VarsListNode **iterator = &listHead_,
                 *iteratorAnother = anotherMonom.listHead_;
    while (iteratorAnother)
    {
        *iterator = new VarsListNode();
        (*iterator)->value = iteratorAnother->value;

        iterator = &((*iterator)->next);
        iteratorAnother = iteratorAnother->next;
    }
}

inline MonomDRL::~MonomDRL()
{
    setOne();
}

inline void* MonomDRL::operator new(std::size_t)
{
    return allocator_.allocate();
}

inline void MonomDRL::operator delete(void* ptr)
{
    allocator_.free(ptr);
}

inline MonomDRL::VarsListNode* MonomDRL::find(Integer var) const
{
    if (!listHead_ || listHead_->value < var)
    {
        return nullptr;
    }

    VarsListNode* position = listHead_;
    while (position && position->next && position->next->value >= var)
    {
        position = position->next;
    }
    return position;
}

inline void MonomDRL::setOne()
{
    totalDegree_ = 0;
    if (listHead_)
    {
        while (listHead_)
        {
            auto* tmpNode = listHead_;
            listHead_ = listHead_->next;
            delete tmpNode;
        }
    }
}

inline MonomDRL::Integer MonomDRL::operator[](Integer var) const
{
    VarsListNode* varPosition = find(var);
    return varPosition && varPosition->value == var;
}

inline const MonomDRL& MonomDRL::operator=(const MonomDRL& anotherMonom)
{
    if (this == &anotherMonom)
    {
        return *this;
    }

    if (!anotherMonom.listHead_)
    {
        setOne();
    }
    else
    {
        totalDegree_ = anotherMonom.totalDegree_;

        VarsListNode *iteratorAnother = anotherMonom.listHead_,
                     **iterator = &listHead_;
        while (*iterator && iteratorAnother)
        {
            (*iterator)->value = iteratorAnother->value;
            iterator = &((*iterator)->next);
            iteratorAnother = iteratorAnother->next;
        }

        if (*iterator)
        {
            VarsListNode* nodeToDelete = *iterator;
            *iterator = 0;
            while (nodeToDelete)
            {
                iteratorAnother = nodeToDelete;
                nodeToDelete = nodeToDelete->next;
                delete iteratorAnother;
            }
        }
        else while (iteratorAnother)
        {
            *iterator = new VarsListNode();
            (*iterator)->value = iteratorAnother->value;

            iterator = &((*iterator)->next);
            iteratorAnother = iteratorAnother->next;
        }
    }
    return *this;
}

inline void MonomDRL::multiplyBy(Integer var)
{
    // inserted variable is the only one
    if (!listHead_)
    {
        listHead_ = new VarsListNode();
        listHead_->value = var;
        ++totalDegree_;
    }
    else
    {
        VarsListNode* position = find(var);

        // inserted variable is the eldest one
        if (!position)
        {
            position = new VarsListNode();
            position->value = var;
            position->next = listHead_;
            listHead_ = position;
            ++totalDegree_;
        }
        // all other cases
        else if(position->value != var)
        {
            VarsListNode* newNode = new VarsListNode();
            newNode->value = var;
            newNode->next = position->next;
            position->next = newNode;
            ++totalDegree_;
        }
    }
}

inline const MonomDRL& MonomDRL::operator*=(Integer var)
{
    multiplyBy(var);
    return *this;
}

inline const MonomDRL& MonomDRL::operator*=(const MonomDRL& anotherMonom)
{
    if (!listHead_)
    {
        *this = anotherMonom;
    }
    else
    {
        if (anotherMonom.listHead_)
        {
            VarsListNode **iterator = &listHead_,
                         *anotherIterator = anotherMonom.listHead_;

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
                    ++totalDegree_;

                    iterator = &(newNode->next);
                    anotherIterator = anotherIterator->next;
                }
            }

            while (anotherIterator)
            {
                *iterator = new VarsListNode();
                (*iterator)->value = anotherIterator->value;
                ++totalDegree_;

                iterator = &((*iterator)->next);
                anotherIterator = anotherIterator->next;
            }
        }
    }

    return *this;
}

inline const MonomDRL& MonomDRL::operator/=(const MonomDRL& anotherMonom)
{
    VarsListNode **iterator = &listHead_,
                 *anotherIterator = anotherMonom.listHead_;

    while (*iterator && anotherIterator)
    {
        if ((*iterator)->value == anotherIterator->value)
        {
            VarsListNode* nodeToDelete = *iterator;
            *iterator = (*iterator)->next;
            delete nodeToDelete;
            --totalDegree_;
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
    VarsListNode **iterator = &listHead_,
                 *iteratorA = monomA.listHead_,
                 *iteratorB = monomB.listHead_;

    while (iteratorA && iteratorB)
    {
        if (iteratorA->value == iteratorB->value)
        {
            iteratorA = iteratorA->next;
            iteratorB = iteratorB->next;
        }
        else
        {
            ++totalDegree_;
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
        ++totalDegree_;
        *iterator = new VarsListNode();
        (*iterator)->value = iteratorA->value;
        iterator = &((*iterator)->next);
        iteratorA = iteratorA->next;
    }
}

inline bool MonomDRL::operator==(const MonomDRL& anotherMonom) const
{
    if (totalDegree_ != anotherMonom.totalDegree_)
    {
        return false;
    }

    VarsListNode *iterator = listHead_,
                 *anotherIterator = anotherMonom.listHead_;
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

inline bool MonomDRL::operator!=(const MonomDRL& anotherMonom) const
{
    return !(*this == anotherMonom);
}

inline bool MonomDRL::operator<(const MonomDRL& anotherMonom) const
{
    if (totalDegree_ < anotherMonom.totalDegree_)
    {
        return true;
    }
    else if (totalDegree_ > anotherMonom.totalDegree_)
    {
        return false;
    }

    VarsListNode *iterator = listHead_,
                 *anotherIterator = anotherMonom.listHead_;
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

inline bool MonomDRL::operator>(const MonomDRL& anotherMonom) const
{
    if (totalDegree_ < anotherMonom.totalDegree_)
    {
        return false;
    }
    else if (totalDegree_ > anotherMonom.totalDegree_)
    {
        return true;
    }

    VarsListNode *iterator = listHead_,
                 *anotherIterator = anotherMonom.listHead_;
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

inline bool MonomDRL::isDivisibleBy(const MonomDRL& anotherMonom) const
{
    VarsListNode *iterator = listHead_,
                 *anotherIterator = anotherMonom.listHead_;
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

inline bool MonomDRL::isTrueDivisibleBy(const MonomDRL& anotherMonom) const
{
    if (totalDegree_ <= anotherMonom.totalDegree_)
    {
        return false;
    }

    VarsListNode *iterator = listHead_,
                 *anotherIterator = anotherMonom.listHead_;
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

inline bool MonomDRL::isPommaretDivisibleBy(const MonomDRL& anotherMonom) const
{
    if (totalDegree_ < anotherMonom.totalDegree_)
    {
        return false;
    }
    if (!anotherMonom.totalDegree_)
    {
        return true;
    }

    VarsListNode *iterator = listHead_,
                 *anotherIterator = anotherMonom.listHead_;
    while (iterator && iterator->value > anotherIterator->value)
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

inline MonomDRL::Integer MonomDRL::firstMultiVar() const
{
    return listHead_ ? listHead_->value : 0;
}

inline std::set<MonomDRL::Integer> MonomDRL::variablesSet() const
{
    std::set<Integer> result;
    VarsListNode *iterator = listHead_;
    while (iterator)
    {
        result.insert(iterator->value);
        iterator = iterator->next;
    }
    return result;
}
