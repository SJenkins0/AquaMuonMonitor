#include "timeOpe.h"

Time::Time()
{}

string Time::getTime()
{
    // Returns the time in string format
    clock_gettime(CLOCK_REALTIME, &ts);
    localtime_r(&ts.tv_sec, &t);

    strftime(time, 18, "%y/%m/%d %H:%M:%S", &t);

    msec = ts.tv_nsec / 1000000;
    ss << setfill('0') << right << setw(3) << msec;
    output = string(time) + "." + ss.str();
    ss.str("");

    return output;
}
