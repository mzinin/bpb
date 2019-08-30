#include "fast_allocator.h"
#include "resource_counter.h"

#include <iomanip>
#include <iostream>


void ResourceCounter::printFullStatistics(std::ostream& out) const
{
    out << std::setw(38) << std::left << "Non-Multiple Prolongations considered" << ": " << nonMultiProlongations << std::endl;

    out << std::setw(38) << std::left << "Non-Zero Reductions made" << ": " << nonZeroReductions
        << " (" << std::fixed << std::setprecision(2) << double(nonZeroReductions) / nonMultiProlongations * 100 << "%)" << std::endl;

    out << std::setw(38) << std::left << "Zero Reductions made" << ": " << nonMultiProlongations - nonZeroReductions
        << " (" << std::fixed << std::setprecision(2) << double(nonMultiProlongations - nonZeroReductions) / nonMultiProlongations * 100 << "%)" << std::endl << std::endl;

    out << std::setw(41) << std::left << "Average Non-Multiple Prolongation length" << ": "
        << std::setprecision(2) << double(nonMultiProlongationsLength) / nonMultiProlongations << std::endl;

    out << std::setw(41) << std::left << "Average Non-Zero Reduction length" << ": "
        << std::setprecision(2) << double(nonZeroReductionsLength) / nonZeroReductions << std::endl << std::endl;

    printBriefStatistics(out);
}

void ResourceCounter::printBriefStatistics(std::ostream& out) const
{
    out << std::setw(19) << "Memory used" << ": ";
    unsigned long usedMemory = FastAllocator::usedMemory();
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

    out << std::setw(19) << "AutoReduction time" << ": " << std::setprecision(2) << autoReductionTimer.realTime() << " sec" << std::endl;

    out << std::setw(19) << "Running time" << ": " << std::setprecision(2) << groebnerBasisTimer.realTime() << " sec" << std::endl << std::endl;
}

ResourceCounter& resourceCounter()
{
    static ResourceCounter counter;
    return counter;
}
