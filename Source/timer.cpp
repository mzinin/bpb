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

#include "timer.h"
#include <sys/time.h>
#include <unistd.h>

void Timer::start()
{
    times(&mBuffer);

    mUser = Timer::mBuffer.tms_utime;
    mSys  = Timer::mBuffer.tms_stime;

    mTimeUser = 0;
    mTimeSys  = 0;
}

void Timer::stop()
{
    times(&mBuffer);

    mTimeUser += Timer::mBuffer.tms_utime - mUser;
    mTimeSys  += Timer::mBuffer.tms_stime - mSys;
}

void Timer::cont()
{
    times(&mBuffer);

    mUser = Timer::mBuffer.tms_utime;
    mSys  = Timer::mBuffer.tms_stime;
}

void Timer::operator = (const Timer & a)
{
    mUser = a.mUser;
    mSys = a.mSys;
    mTimeUser = a.mTimeUser;
    mTimeSys = a.mTimeSys;
}

tms Timer::mBuffer;
double Timer::mHZ = double(sysconf(_SC_CLK_TCK));

std::ostream& operator<<(std::ostream& out, const Timer &a)
{
    std::ios::fmtflags flags = out.flags();
    out.flags(flags | std::ios::fixed);
    out << "  user mTime: " << std::setprecision(2) << a.userTime() << " sec" << std::endl;
    out << "system mTime: " << std::setprecision(2) << a.sysTime()  << " sec" << std::endl;
    out << "  real mTime: " << std::setprecision(2) << a.realTime() << " sec" << std::endl;
    out.flags(flags);
    return out;
}
