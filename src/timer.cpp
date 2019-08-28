/***************************************************************************
 *   Copyright (C) 2008 by Blinkov Yu. A.                                  *
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

#ifdef _WIN32
    #ifndef _WIN32_WINNT
        #define _WIN32_WINNT 0x0500
    #endif
    #include <windows.h>
#else
    #include <unistd.h>
    #include <sys/times.h>
#endif //_WIN32

#include <iomanip>
#include "timer.h"

Timer::Timer()
    : UserTime(0.0)
    , SysTime(0.0)
    , RealTime(0.0)
    , UserElapsed(0.0)
    , SysElapsed(0.0)
    , RealElapsed(0.0)
{
}

Timer::~Timer()
{
}

#ifdef _WIN32

double Timer::Hz = 10000000.0;

void Timer::Start()
{
    UserElapsed = 0.0;
    SysElapsed = 0.0;
    RealElapsed = 0.0;

    ULARGE_INTEGER cTime, eTime, kTime, uTime, rTime;

    ::GetProcessTimes(::GetCurrentProcess(), (LPFILETIME)&cTime, (LPFILETIME)&eTime, (LPFILETIME)&kTime, (LPFILETIME)&uTime);
    ::GetSystemTimeAsFileTime((LPFILETIME)&rTime);

    UserTime = uTime.QuadPart/Hz;
    SysTime = kTime.QuadPart/Hz;
    RealTime = rTime.QuadPart/Hz;
}

void Timer::Continue()
{
    ULARGE_INTEGER cTime, eTime, kTime, uTime, rTime;

    ::GetProcessTimes(::GetCurrentProcess(), (LPFILETIME)&cTime, (LPFILETIME)&eTime, (LPFILETIME)&kTime, (LPFILETIME)&uTime);
    ::GetSystemTimeAsFileTime((LPFILETIME)&rTime);

    UserTime = uTime.QuadPart/Hz;
    SysTime = kTime.QuadPart/Hz;
    RealTime = rTime.QuadPart/Hz;
}

void Timer::Stop()
{
    ULARGE_INTEGER cTime, eTime, kTime, uTime, rTime;

    ::GetProcessTimes(::GetCurrentProcess(), (LPFILETIME)&cTime, (LPFILETIME)&eTime, (LPFILETIME)&kTime, (LPFILETIME)&uTime);
    ::GetSystemTimeAsFileTime((LPFILETIME)&rTime);

    UserElapsed += uTime.QuadPart/Hz - UserTime;
    SysElapsed += kTime.QuadPart/Hz - SysTime;
    RealElapsed += rTime.QuadPart/Hz - RealTime;

    UserTime = uTime.QuadPart/Hz;
    SysTime = kTime.QuadPart/Hz;
    RealTime = rTime.QuadPart/Hz;
}

#else

double Timer::Hz = double(sysconf(_SC_CLK_TCK));

void Timer::Start()
{
    UserElapsed = 0.0;
    SysElapsed = 0.0;
    RealElapsed = 0.0;

    tms buffer;
    RealTime = times(&buffer)/Hz;
    UserTime = buffer.tms_utime/Hz;
    SysTime = buffer.tms_stime/Hz;
}

void Timer::Continue()
{
    tms buffer;
    RealTime = times(&buffer)/Hz;
    UserTime = buffer.tms_utime/Hz;
    SysTime = buffer.tms_stime/Hz;
}

void Timer::Stop()
{
    tms buffer;
    double t = times(&buffer)/Hz;

    UserElapsed += buffer.tms_utime/Hz - UserTime;
    SysElapsed += buffer.tms_stime/Hz - SysTime;
    RealElapsed += t - RealTime;

    UserTime = buffer.tms_utime/Hz;
    SysTime = buffer.tms_stime/Hz;
    RealTime = t;
}

#endif // _WIN32

std::ostream& operator<<(std::ostream& out, const Timer &timer)
{
    std::ios::fmtflags flags = out.flags();
    out.flags(flags | std::ios::fixed);
    out << "  user time: " << std::setprecision(2) << timer.GetUserTime() << " sec" << std::endl;
    out << "system time: " << std::setprecision(2) << timer.GetSysTime()  << " sec" << std::endl;
    out << "  real time: " << std::setprecision(2) << timer.GetRealTime() << " sec" << std::endl;
    out.flags(flags);
    return out;
}
