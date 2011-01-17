#include "monomDL.h"

int MonomDL::Compare(const Monom& anotherMonom)
{
    const MonomDL* castedAnotherMonom = CastToMe(anotherMonom);

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

MonomDL::Integer MonomDL::GcdDegree(const Monom& anotherMonom)
{
    const MonomDL* castedAnotherMonom = CastToMe(anotherMonom);

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

MonomDL::Integer MonomDL::LcmDegree(const Monom& anotherMonom)
{
    const MonomDL* castedAnotherMonom = CastToMe(anotherMonom);

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

FastAllocator MonomDL::Allocator(sizeof(MonomDL));
FastAllocator MonomDL::VarsListNode::Allocator(sizeof(MonomDL::VarsListNode));
