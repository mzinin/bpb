#pragma once

#include <iostream>


class Timer
{
public:
    void start();
    void resume();
    void stop();

    double userTime() const;
    double sysTime() const;
    double realTime() const;

    friend std::ostream& operator<<(std::ostream& out, const Timer& timer);

private:
    static double Hz_;

    double userTime_ = 0.0;
    double sysTime_ = 0.0;
    double realTime_ = 0.0;

    double userElapsed_ = 0.0;
    double sysElapsed_ = 0.0;
    double realElapsed_ = 0.0;
};

inline double Timer::userTime() const
{
    return userElapsed_;
}

inline double Timer::sysTime() const
{
    return sysElapsed_;
}

inline double Timer::realTime() const
{
    return realElapsed_;
}
