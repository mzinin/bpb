#pragma once

#include <cstddef>
#include <cstdint>
#include <list>


class FastAllocator
{
public:
    FastAllocator(uint64_t blockSize);
    ~FastAllocator();

    // throws std::bad_alloc
    void* allocate();
    void free(void* pointer);

    static uint64_t usedMemory();

private:
    // throws std::bad_alloc
    void expandMemory();

private:
    const uint64_t tSize_;
    const uint64_t memoryPageSize_;
    void**       freeBlock_;
    std::list<void*> allocatedBlocks_;

    static uint64_t usedMemory_;
    static const uint64_t pageSize_;
};

inline void* FastAllocator::allocate()
{
    if (!freeBlock_)
    {
        expandMemory();
    }

    void* pointer = static_cast<void*>(freeBlock_);
    freeBlock_ = static_cast<void**>(*freeBlock_);
    return pointer;
}

inline void FastAllocator::free(void* pointer)
{
    *(static_cast<void***>(pointer)) = freeBlock_;
    freeBlock_ = static_cast<void**>(pointer);
}
