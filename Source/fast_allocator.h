/***************************************************************************
 *   Copyright (C) 2004 by Blinkov Yu.A.                                   *
 *   BlinkovUA@info.sgu.ru                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef FAST_ALLOCATOR_H
#define FAST_ALLOCATOR_H

#include <list>

class FastAllocator
{
public:
    static unsigned long GetUsedMemory();

    FastAllocator(const size_t blockSize);
    ~FastAllocator();

    void* Allocate(); // throws std::bad_alloc
    void Free(void* pointer);

private:
    void ExpandMemory(); // throws std::bad_alloc

private:
    const size_t TSize;
    const size_t MemoryPageSize;
    void**       FreeBlock;
    std::list<void*> AllocatedBlocks;

    static unsigned long UsedMemory;
    static const size_t PageSize;
};

inline void* FastAllocator::Allocate()
{
    if (!FreeBlock)
    {
        ExpandMemory();
    }

    void* pointer = static_cast<void*>(FreeBlock);
    FreeBlock = static_cast<void**>(*FreeBlock);
    return pointer;
}

inline void FastAllocator::Free(void* pointer)
{
    *(static_cast<void***>(pointer)) = FreeBlock;
    FreeBlock = static_cast<void**>(pointer);
}

#endif // FAST_ALLOCATOR_H
