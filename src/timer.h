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

#ifndef TIMER_H
#define TIMER_H

#include <iostream>

class Timer
{
private:
    static double Hz;

    double UserTime;
    double SysTime;
    double RealTime;

    double UserElapsed;
    double SysElapsed;
    double RealElapsed;

public:
    Timer();
    ~Timer();

    void Start();
    void Continue();
    void Stop();

    double GetUserTime() const;
    double GetSysTime() const;
    double GetRealTime() const;

    friend std::ostream& operator<<(std::ostream& out, const Timer &timer);
};

inline double Timer::GetUserTime() const
{
    return UserElapsed;
}

inline double Timer::GetSysTime() const
{
    return SysElapsed;
}

inline double Timer::GetRealTime() const
{
    return RealElapsed;
}

#endif // TIMER_H
