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

#ifndef IUTIL_H
#define IUTIL_H

#include <cassert>
#include <cstdlib>
#include <cstdio>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef NDEBUG
  #define IASSERT(a)
  #define IASSERT2(file, line, a)
  #define IASSERTVALID(a)
  #define IASSERT_VALID(a)
#else
  #define IASSERT(a)              assert(a)
  #define IASSERT2(file, line, a) if (!(a)) { printf("from file: '%s'  line: %d\n", file, line); assert(a); }
  #define IASSERTVALID(a)         (a).assertValid(__FILE__, __LINE__)
  #define IASSERT_VALID(a)        assertValid(a,__FILE__, __LINE__)
#endif // NDEBUG


#define IERROR(a)     printf("**** file: %s\n     line: %d\n    error: %s\n", __FILE__, __LINE__, a), abort()
#define IMESSAGE(a)   printf("**** file: %s\n     line: %d\n  message: %s\n", __FILE__, __LINE__, a)

#ifdef DLMALLOC
  #define USE_DL_PREFIX
  #include "./dlmalloc/dlmalloc.h"
  inline void* imalloc(size_t n) {
    return dlmalloc(n);
  }
  inline void ifree(void* ptr) {
    dlfree(ptr);
  }
  inline void* irealloc(void* ptr, size_t n) {
    return dlrealloc(ptr, n);
  }
#else
  inline void* imalloc(size_t n) {
    return malloc(n);
  }
  inline void ifree(void* ptr) {
    free(ptr);
  }
  inline void* irealloc(void* ptr, size_t n) {
    return realloc(ptr, n);
  }
#endif // DLMALLOC

#endif // IUTIL_H
