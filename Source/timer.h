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

#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <iomanip>
#include <sys/times.h>

class Timer {
  static double mHZ;        //  Number of ticks per second
  static tms    mBuffer;

  clock_t       mUser;
  clock_t       mSys;
  clock_t       mTimeUser;
  clock_t       mTimeSys;

public:
  Timer(): mUser(0), mSys(0), mTimeUser(0), mTimeSys(0) {}
  ~Timer() {}

  void start();
  void stop();
  void ignore();
  void cont();

  double userTime() const { return mTimeUser / mHZ; }
  double sysTime() const { return mTimeSys / mHZ; }
  double realTime() const { return (mTimeUser + mTimeSys) / mHZ; }

  void operator= (const Timer &a);

  friend std::ostream& operator<<(std::ostream& out, const Timer &a);
};

#endif // ITIMER_H
