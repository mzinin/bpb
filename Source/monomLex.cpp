#include "monomLex.h"

int MonomLex::Compare(const Monom& anotherMonom)
{
    const MonomLex* castedAnotherMonom = CastToMe(anotherMonom);

    VarsListNode *iterator = ListHead,
                 *iteratorAnother = castedAnotherMonom->ListHead;
    while (iterator && iteratorAnother)
    {
        if (iterator->Value < iteratorAnother->Value)
        {
            return 1;
        }
        if (iterator->Value > iteratorAnother->Value)
        {
            return -1;
        }
        iterator = iterator->Next;
        iteratorAnother = iteratorAnother->Next;
    }

    if (iterator)
    {
        return 1;
    }
    else if (iteratorAnother)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

MonomLex::Integer MonomLex::GcdDegree(const Monom& anotherMonom)
{
    const MonomLex* castedAnotherMonom = CastToMe(anotherMonom);

    Integer gcd = 0;
    VarsListNode *iterator = ListHead,
                 *iteratorAnother = castedAnotherMonom->ListHead;

    while (iterator && iteratorAnother)
    {
        if (iterator->Value == iteratorAnother->Value)
        {
            ++gcd;
            iterator = iterator->Next;
            iteratorAnother = iteratorAnother->Next;
        }
        else if (iterator->Value < iteratorAnother->Value)
        {
            iterator = iterator->Next;
        }
        else
        {
            iteratorAnother = iteratorAnother->Next;
        }
    }
    return gcd;
}

MonomLex::Integer MonomLex::LcmDegree(const Monom& anotherMonom)
{
    const MonomLex* castedAnotherMonom = CastToMe(anotherMonom);

    Integer lcm = 0;
    VarsListNode *iterator = ListHead,
                 *iteratorAnother = castedAnotherMonom->ListHead;

    while (iterator && iteratorAnother)
    {
        ++lcm;
        if (iterator->Value == iteratorAnother->Value)
        {
            iterator = iterator->Next;
            iteratorAnother = iteratorAnother->Next;
        }
        else if (iterator->Value < iteratorAnother->Value)
        {
            iterator = iterator->Next;
        }
        else
        {
            iteratorAnother = iteratorAnother->Next;
        }
    }

    while (iterator)
    {
        ++lcm;
        iterator = iterator->Next;
    }

    while (iteratorAnother)
    {
        ++lcm;
        iteratorAnother = iteratorAnother->Next;
    }

    return lcm;
}

FastAllocator MonomLex::Allocator(sizeof(MonomLex));
FastAllocator MonomLex::VarsListNode::Allocator(sizeof(MonomLex::VarsListNode));
