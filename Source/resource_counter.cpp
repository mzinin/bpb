#include <iomanip>
#include <iostream>

#include "fast_allocator.h"
#include "resource_counter.h"

ResourceCounter::ResourceCounter()
    : GroebnerBasisTimer()
    , NonMultiProlongations(0)
    , NonZeroReductions(0)
{
}

ResourceCounter::~ResourceCounter()
{
}

void ResourceCounter::PrintFullStatistics(std::ostream& out) const
{
    out << std::setw(38) << std::left << "Non-Multiple Prolongations considered" << ": " << NonMultiProlongations << std::endl;

    out << std::setw(38) << std::left << "Non-Zero Reductions made" << ": " << NonZeroReductions
        << " (" << std::fixed << std::setprecision(2) << double(NonZeroReductions) / NonMultiProlongations * 100 << "%)" << std::endl;

    out << std::setw(38) << std::left << "Zero Reductions made" << ": " << NonMultiProlongations - NonZeroReductions
        << " (" << std::fixed << std::setprecision(2) << double(NonMultiProlongations - NonZeroReductions) / NonMultiProlongations * 100 << "%)" << std::endl << std::endl;

    PrintBriefStatistics(out);
}

void ResourceCounter::PrintBriefStatistics(std::ostream& out) const
{
    out << "memory used: ";
    unsigned long usedMemory = FastAllocator::GetUsedMemory();
    if (usedMemory < 1024*1024)
    {
        out << std::fixed << std::setprecision(1) << double(usedMemory) / 1024 << " Kb" << std::endl;
    }
    else if (usedMemory < 1024*1024*1024)
    {
        out << std::fixed << std::setprecision(1) << double(usedMemory) / 1024 / 1024 << " Mb" << std::endl;
    }
    else
    {
        out << std::fixed << std::setprecision(3) << double(usedMemory) / 1024 / 1024 / 1024 << " Gb" << std::endl;
    }

    out << GroebnerBasisTimer << std::endl;
}

ResourceCounter& GetResourceCounter()
{
    static ResourceCounter counter = ResourceCounter();
    return counter;
}
