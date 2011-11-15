#ifndef RESOURCE_COUNTER_H
#define RESOURCE_COUNTER_H

#include "timer.h"

class ResourceCounter
{
public:
    Timer GroebnerBasisTimer;
    Timer AutoReductionTimer;
    unsigned long NonMultiProlongations;
    unsigned long NonMultiProlongationsLength;
    unsigned long NonZeroReductions;
    unsigned long NonZeroReductionsLength;

public:
   ~ResourceCounter();
    void PrintFullStatistics(std::ostream& out) const;
    void PrintBriefStatistics(std::ostream& out) const;

private:
    ResourceCounter();
    ResourceCounter(const ResourceCounter&);
    ResourceCounter& operator=(const ResourceCounter&);

friend ResourceCounter& GetResourceCounter();
};

ResourceCounter& GetResourceCounter();

#endif // RESOURCE_COUNTER_H