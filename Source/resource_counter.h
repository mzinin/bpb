#ifndef RESOURCE_COUNTER_H
#define RESOURCE_COUNTER_H

#include "timer.h"

class ResourceCounter
{
public:
    Timer GroebnerBasisTimer;
    unsigned long NonMultiProlongations;
    unsigned long NonZeroReductions;

public:
   ~ResourceCounter();
    void PrintFullStatistics(std::ostream& out) const;
    void PrintBriefStatistics(std::ostream& out) const;

private:
   ResourceCounter();

friend ResourceCounter& GetResourceCounter();
};

ResourceCounter& GetResourceCounter();

#endif // RESOURCE_COUNTER_H
