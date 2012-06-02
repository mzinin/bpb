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

#include "iallocator.h"


void IAllocator::getMem() {
  ++sMaxMemory;
  void **beg = (void**)imalloc(memoryPageSize),
       **end = beg + mTSize*(mPageSize-1),
       **tmp;
  IASSERT(beg != NULL);
  *((void***)end) = mFree;
  mFree = (void**)beg;
  do {
    tmp = beg + mTSize;
    *((void***)beg) = tmp;
    beg = tmp;
  } while(beg < end);
}

IAllocator::IAllocator(const size_t n):
    mTSize((n+sizeof(void*)-1)/sizeof(void*)),
    mPageSize(memoryPageSize/(sizeof(void*)*(n+sizeof(void*)-1)/sizeof(void*))),
    mFree(NULL) {
}

int IAllocator::sMaxMemory = 0;
