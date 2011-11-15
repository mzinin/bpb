#include <sstream>
#include "monomLex.h"

MonomLex::MonomLex(const std::string& str)
    : Monom()
    , Next(0)
{
    std::stringstream tmpStream(str); 
    tmpStream >> *this;
}

int MonomLex::Compare(const MonomLex& anotherMonom)
{
    VarsListNode *iterator = ListHead,
                 *iteratorAnother = anotherMonom.ListHead;
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

FastAllocator MonomLex::Allocator(sizeof(MonomLex));
