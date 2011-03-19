#include "monomDL.h"

int MonomDL::Compare(const MonomDL& anotherMonom)
{
    if (TotalDegree < anotherMonom.TotalDegree)
    {
        return -1;
    }
    else if (TotalDegree > anotherMonom.TotalDegree)
    {
        return 1;
    }
    else
    {
        VarsListNode *iterator(ListHead),
                     *iteratorAnother(anotherMonom.ListHead);
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

FastAllocator MonomDL::Allocator(sizeof(MonomDL));
