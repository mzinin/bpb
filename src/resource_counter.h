#pragma once

#include "timer.h"


class ResourceCounter
{
public:
    Timer groebnerBasisTimer;
    Timer autoReductionTimer;

    unsigned long nonMultiProlongations = 0;
    unsigned long nonMultiProlongationsLength = 0;
    unsigned long nonZeroReductions = 0;
    unsigned long nonZeroReductionsLength = 0;

public:
    ResourceCounter(const ResourceCounter&) = delete;
    ResourceCounter& operator=(const ResourceCounter&) = delete;

    void printFullStatistics(std::ostream& out) const;
    void printBriefStatistics(std::ostream& out) const;

private:
    ResourceCounter() = default;

    friend ResourceCounter& resourceCounter();
};

ResourceCounter& resourceCounter();

