#include "timer.h"

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


#ifdef _WIN32

double Timer::Hz_ = 10000000.0;

void Timer::start()
{
    userElapsed_ = 0.0;
    sysElapsed_ = 0.0;
    realElapsed_ = 0.0;

    ULARGE_INTEGER cTime, eTime, kTime, uTime, rTime;

    ::GetProcessTimes(::GetCurrentProcess(), (LPFILETIME)&cTime, (LPFILETIME)&eTime, (LPFILETIME)&kTime, (LPFILETIME)&uTime);
    ::GetSystemTimeAsFileTime((LPFILETIME)&rTime);

    userTime_ = uTime.QuadPart / Hz_;
    sysTime_ = kTime.QuadPart / Hz_;
    realTime_ = rTime.QuadPart / Hz_;
}

void Timer::resume()
{
    ULARGE_INTEGER cTime, eTime, kTime, uTime, rTime;

    ::GetProcessTimes(::GetCurrentProcess(), (LPFILETIME)&cTime, (LPFILETIME)&eTime, (LPFILETIME)&kTime, (LPFILETIME)&uTime);
    ::GetSystemTimeAsFileTime((LPFILETIME)&rTime);

    userTime_ = uTime.QuadPart / Hz_;
    sysTime_ = kTime.QuadPart / Hz_;
    realTime_ = rTime.QuadPart / Hz_;
}

void Timer::stop()
{
    ULARGE_INTEGER cTime, eTime, kTime, uTime, rTime;

    ::GetProcessTimes(::GetCurrentProcess(), (LPFILETIME)&cTime, (LPFILETIME)&eTime, (LPFILETIME)&kTime, (LPFILETIME)&uTime);
    ::GetSystemTimeAsFileTime((LPFILETIME)&rTime);

    userElapsed_ += uTime.QuadPart / Hz_ - userTime_;
    sysElapsed_ += kTime.QuadPart / Hz_ - sysTime_;
    realElapsed_ += rTime.QuadPart / Hz_ - realTime_;

    userTime_ = uTime.QuadPart / Hz_;
    sysTime_ = kTime.QuadPart / Hz_;
    realTime_ = rTime.QuadPart / Hz_;
}

#else

double Timer::Hz_ = double(sysconf(_SC_CLK_TCK));

void Timer::start()
{
    userElapsed_ = 0.0;
    sysElapsed_ = 0.0;
    realElapsed_ = 0.0;

    tms buffer;
    realTime_ = times(&buffer) / Hz_;
    userTime_ = buffer.tms_utime / Hz_;
    sysTime_ = buffer.tms_stime / Hz_;
}

void Timer::resume()
{
    tms buffer;
    realTime_ = times(&buffer) / Hz_;
    userTime_ = buffer.tms_utime / Hz_;
    sysTime_ = buffer.tms_stime / Hz_;
}

void Timer::stop()
{
    tms buffer;
    double t = times(&buffer) / Hz_;

    userElapsed_ += buffer.tms_utime / Hz_ - userTime_;
    sysElapsed_ += buffer.tms_stime / Hz_ - sysTime_;
    realElapsed_ += t - realTime_;

    userTime_ = buffer.tms_utime / Hz_;
    sysTime_ = buffer.tms_stime / Hz_;
    realTime_ = t;
}

#endif // _WIN32

std::ostream& operator<<(std::ostream& out, const Timer& timer)
{
    std::ios::fmtflags flags = out.flags();
    out.flags(flags | std::ios::fixed);
    out << "  user time: " << std::setprecision(2) << timer.userTime() << " sec" << std::endl;
    out << "system time: " << std::setprecision(2) << timer.sysTime()  << " sec" << std::endl;
    out << "  real time: " << std::setprecision(2) << timer.realTime() << " sec" << std::endl;
    out.flags(flags);
    return out;
}
