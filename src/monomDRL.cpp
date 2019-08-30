#include "monomDRL.h"

#include <sstream>


FastAllocator MonomDRL::allocator_(sizeof(MonomDRL));


MonomDRL::MonomDRL(const std::string& str)
{
    std::stringstream tmpStream(str);
    tmpStream >> *this;
}

int MonomDRL::compare(const MonomDRL& anotherMonom) const
{
    if (totalDegree_ < anotherMonom.totalDegree_)
    {
        return -1;
    }
    else if (totalDegree_ > anotherMonom.totalDegree_)
    {
        return 1;
    }

    VarsListNode *iterator(listHead_),
                 *iteratorAnother(anotherMonom.listHead_);
    while (iterator)
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
    return 0;
}
