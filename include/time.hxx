#pragma once
#include <chrono>

using Time = std::chrono::steady_clock;
using float_sec = std::chrono::duration<float>;
using float_time_point = std::chrono::time_point<Time, float_sec>;


class Clock
{
public: 
    typedef std::chrono::steady_clock clock_type;
    typedef std::chrono::time_point<clock_type> time_point_type;

    Clock()
    {
        reset();
    }

    void reset()
    {
        start_ = clock_type::now();
    }

    double elapsed() const
    {
        time_point_type now = clock_type::now();
        return std::chrono::duration_cast<std::chrono::nanoseconds>((now-start_)).count() * 1e-9;
    }

private:
    time_point_type start_;
};
