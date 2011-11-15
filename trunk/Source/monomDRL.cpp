#include <sstream>
#include "monomDRL.h"

MonomDRL::MonomDRL(const std::string& str)
    : Monom()
    , Next(0)
{
    std::stringstream tmpStream(str); 
    tmpStream >> *this;
}

int MonomDRL::Compare(const MonomDRL& anotherMonom)
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

FastAllocator MonomDRL::Allocator(sizeof(MonomDRL));
