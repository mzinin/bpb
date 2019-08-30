#include "monomLex.h"

#include <sstream>


FastAllocator MonomLex::allocator_(sizeof(MonomLex));


MonomLex::MonomLex(const std::string& str)
{
    std::stringstream tmpStream(str);
    tmpStream >> *this;
}

int MonomLex::compare(const MonomLex& anotherMonom) const
{
    VarsListNode *iterator = listHead_,
                 *iteratorAnother = anotherMonom.listHead_;
    while (iterator && iteratorAnother)
    {
        if (iterator->value < iteratorAnother->value)
        {
            return 1;
        }
        if (iterator->value > iteratorAnother->value)
        {
            return -1;
        }
        iterator = iterator->next;
        iteratorAnother = iteratorAnother->next;
    }

    if (iterator)
    {
        return 1;
    }
    else if (iteratorAnother)
    {
        return -1;
    }
    return 0;
}
