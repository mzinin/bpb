#include "fast_allocator.h"

#include <cstdlib>
#include <cmath>


FastAllocator::FastAllocator(size_t blockSize)
    : tSize_(ceil((double)blockSize / sizeof(void*)))
    , memoryPageSize_(blockSize * pageSize_)
    , freeBlock_(nullptr)
{
}

FastAllocator::~FastAllocator()
{
    for (auto* block : allocatedBlocks_)
    {
        free(block);
    }
}

unsigned long FastAllocator::usedMemory()
{
    return usedMemory_;
}

void FastAllocator::expandMemory()
{
    usedMemory_ += memoryPageSize_;
    void **begin = static_cast<void**>(malloc(memoryPageSize_)),
         **end = begin + tSize_ * (pageSize_ - 1),
         **tmp;

    if (!begin)
    {
        throw std::bad_alloc();
    }

    allocatedBlocks_.push_back(static_cast<void*>(begin));

    *(reinterpret_cast<void***>(end)) = freeBlock_;
    freeBlock_ = static_cast<void**>(begin);
    do
    {
        tmp = begin + tSize_;
        *(reinterpret_cast<void***>(begin)) = tmp;
        begin = tmp;
    } while(begin < end);
}

unsigned long FastAllocator::usedMemory_ = 0;
const size_t FastAllocator::pageSize_ = 65536;
