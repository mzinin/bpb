#include <cstdlib>
#include <cmath>
#include <iostream>

#include "fast_allocator.h"

FastAllocator::FastAllocator(size_t blockSize)
    : TSize(ceil((double)blockSize / sizeof(void*)))
    , MemoryPageSize(blockSize * PageSize)
    , FreeBlock(0)
{
}

FastAllocator::~FastAllocator()
{
    for (std::list<void*>::iterator it = AllocatedBlocks.begin(); it != AllocatedBlocks.end(); ++it)
    {
        free(*it);
    }
}

unsigned long FastAllocator::GetUsedMemory()
{
    return UsedMemory;
}

void FastAllocator::ExpandMemory() // throws std::bad_alloc
{
    UsedMemory += MemoryPageSize;
    void **begin = static_cast<void**>(malloc(MemoryPageSize)),
         **end = begin + TSize * (PageSize - 1),
         **tmp;

    if (!begin)
    {
        throw std::bad_alloc();
    }

    AllocatedBlocks.push_back(static_cast<void*>(begin));

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
const size_t FastAllocator::PageSize = 65536;
