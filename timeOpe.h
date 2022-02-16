#ifndef TIMEOPE_H
#define TIMEOPE_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
using namespace std;

class Time
{
private:
    struct timespec ts;
    struct tm t;
    char time[18];
    int msec;
    string output;
    stringstream ss;

public:
    Time();
    string getTime();
};

#endif // TIMEOPE_H
