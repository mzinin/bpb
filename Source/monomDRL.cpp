#include "monomDRL.h"

int MonomDRL::Compare(const Monom& anotherMonom)
{
    const MonomDRL* castedAnotherMonom = CastToMe(anotherMonom);

    if (TotalDegree < castedAnotherMonom->TotalDegree)
    {
        return -1;
    }
    else if (TotalDegree > castedAnotherMonom->TotalDegree)
    {
        return 1;
    }
    else
    {
        VarsListNode *iterator(ListHead),
                     *iteratorAnother(castedAnotherMonom->ListHead);
        while (iterator)
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
        return 0;
    }
}

Monom::Integer MonomDRL::GcdDegree(const Monom& anotherMonom)
{
    const MonomDRL* castedAnotherMonom = CastToMe(anotherMonom);

    Monom::Integer gcd = 0;
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
        else if (iterator->Value > iteratorAnother->Value)
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

Monom::Integer MonomDRL::LcmDegree(const Monom& anotherMonom)
{
    const MonomDRL* castedAnotherMonom = CastToMe(anotherMonom);

    Monom::Integer lcm = 0;
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
        else if (iterator->Value > iteratorAnother->Value)
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

FastAllocator MonomDRL::Allocator(sizeof(MonomDRL));
FastAllocator MonomDRL::VarsListNode::Allocator(sizeof(MonomDRL::VarsListNode));
