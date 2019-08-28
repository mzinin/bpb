#include <iomanip>
#include <iostream>

#include "fast_allocator.h"
#include "resource_counter.h"

ResourceCounter::ResourceCounter()
    : GroebnerBasisTimer()
    , AutoReductionTimer()
    , NonMultiProlongations(0)
    , NonMultiProlongationsLength(0)
    , NonZeroReductions(0)
    , NonZeroReductionsLength(0)
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

    out << std::setw(41) << std::left << "Average Non-Multiple Prolongation length" << ": "
        << std::setprecision(2) << double(NonMultiProlongationsLength) / NonMultiProlongations << std::endl;

    out << std::setw(41) << std::left << "Average Non-Zero Reduction length" << ": "
        << std::setprecision(2) << double(NonZeroReductionsLength) / NonZeroReductions << std::endl << std::endl;

    PrintBriefStatistics(out);
}

void ResourceCounter::PrintBriefStatistics(std::ostream& out) const
{
    out << std::setw(19) << "Memory used" << ": ";
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

    out << std::setw(19) << "AutoReduction time" << ": " << std::setprecision(2) << AutoReductionTimer.GetRealTime() << " sec" << std::endl;

    out << std::setw(19) << "Running time" << ": " << std::setprecision(2) << GroebnerBasisTimer.GetRealTime() << " sec" << std::endl << std::endl;
}

ResourceCounter& GetResourceCounter()
{
    static ResourceCounter counter = ResourceCounter();
    return counter;
}
