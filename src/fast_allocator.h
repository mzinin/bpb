#pragma once

#include <cstddef>
#include <list>


class FastAllocator
{
public:
    FastAllocator(const size_t blockSize);
    ~FastAllocator();

    // throws std::bad_alloc
    void* allocate();
    void free(void* pointer);

    static unsigned long usedMemory();

private:
    // throws std::bad_alloc
    void expandMemory();

private:
    const size_t tSize_;
    const size_t memoryPageSize_;
    void**       freeBlock_;
    std::list<void*> allocatedBlocks_;

    static unsigned long usedMemory_;
    static const size_t pageSize_;
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
