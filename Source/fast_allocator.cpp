#include <cstdlib>
#include <cmath>

#include "fast_allocator.h"

FastAllocator::FastAllocator(size_t blockSize)
    : MemoryPageSize(1048576)
    , TSize(ceil((double)blockSize / sizeof(void*)))
    , PageSize(floor((double)MemoryPageSize / blockSize))
    , FreeBlock(0)
{
}

FastAllocator::~FastAllocator()
{
}

unsigned long FastAllocator::GetUsedMemory()
{
    return UsedMemory;
}

void FastAllocator::ExpandMemory()
{
    UsedMemory += MemoryPageSize;
    void **begin = static_cast<void**>(malloc(MemoryPageSize)),
         **end = begin + TSize * (PageSize - 1),
         **tmp;

    if (!begin)
    {
        exit(EXIT_FAILURE);
    }

    *(reinterpret_cast<void***>(end)) = FreeBlock;
    FreeBlock = static_cast<void**>(begin);
    do
    {
        tmp = begin + TSize;
        *(reinterpret_cast<void***>(begin)) = tmp;
        begin = tmp;
    } while(begin < end);
}

unsigned long FastAllocator::UsedMemory = 0;
