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

#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "util.h"


class Allocator
{
    enum {memoryPageSize = 16384};

    const size_t mTSize;
    const size_t mPageSize;
    void**       mFree;
    static int   sMaxMemory;

    void getMem();

public:
    static int maxMemory() { return sMaxMemory*memoryPageSize; }

    Allocator(const size_t n);
    ~Allocator() { clear(); }

    inline void* allocate()
    {
        if (mFree == NULL)
        {
            getMem();
        }
        IASSERT(mFree != NULL);
        void* ptr = (void*)mFree;
        mFree = (void**)(*mFree);
        return ptr;
    }

    inline void deallocate(void* ptr)
    {
        *((void***)ptr) = mFree;
        mFree = (void**)ptr;
    }

    void clear() {}
};

#endif // ALLOCATOR_H
