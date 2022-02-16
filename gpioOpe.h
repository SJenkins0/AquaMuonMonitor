#ifndef GPIOOPE_H
#define GPIOOPE_H

#define GPIO02 2
#define GPIO03 3
#define GPIO04 4
#define GPIO05 5
#define GPIO06 6
#define GPIO07 7
#define GPIO08 8
#define GPIO09 9
#define GPIO10 10
#define GPIO11 11
#define GPIO12 12
#define GPIO13 13
#define GPIO14 14
#define GPIO15 15
#define GPIO16 16
#define GPIO17 17
#define GPIO18 18
#define GPIO19 19
#define GPIO20 20
#define GPIO21 21
#define GPIO22 22
#define GPIO23 23
#define GPIO24 24
#define GPIO25 25
#define GPIO26 26
#define GPIO27 27

// pin assign changed (RD[0] & WT)
#define RD_00 GPIO21    // RD[0]
#define RD_01 GPIO03    // RD[1]
#define RD_02 GPIO04    // RD[2]
#define RD_03 GPIO14    // RD[3]
#define RD_04 GPIO15    // RD[4]
#define RD_05 GPIO17    // RD[5]
#define RD_06 GPIO18    // RD[6]
#define RD_07 GPIO27    // RD[7]
#define RD_08 GPIO22    // RD[8]
#define RD_09 GPIO23    // RD[9]
#define RD_10 GPIO24    // RD[10]
#define RD_11 GPIO10    // RD[11]
#define RD_12 GPIO09    // RD[12]
#define RD_13 GPIO25    // RD[13]
#define RD_14 GPIO11    // RD[14]
#define RD_15 GPIO08    // RD[15]

#define CS_0 GPIO07     // CS0
#define CS_1 GPIO05     // CS1
#define CS_2 GPIO06     // CS2
#define CS_3 GPIO12     // CS3
#define A_1 GPIO13      // A[1]
#define A_2 GPIO19      // A[2]
#define A_3 GPIO16      // A[3]
#define A_4 GPIO26      // A[4]
#define SEL_LH GPIO20   // SEL_LH
#define WT GPIO02       // WT

#define UNIT_1 0        // UNIT 1
#define UNIT_2 1        // UNIT 2
#define UNIT_3 2        // UNIT 3

#define RD_PORT     16  // READ GPIO数
#define ADDR_PORT    4  // ADDR GPIO数
#define OF_PORT     10  // OVERFLOW GPIO数

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <wiringPi.h>
using namespace std;

class GPIO
{
private:
    vector<int> addrGPIO {
        A_1, A_2, A_3, A_4
    };
    vector<int> readGPIO {
        RD_00, RD_01, RD_02, RD_03, RD_04, RD_05, RD_06, RD_07, RD_08, RD_09, RD_10, RD_11, RD_12, RD_13, RD_14, RD_15
    };
    int addr;
    stringstream ss;
    string res;
    string binUpper;
    string binLower;
    string binRes;
    void gpioModeInitRead();
    void gpioModeInitWrite();
    void gpioInitGen();
    void gpioWriteUnit(int unit, int output);

public:
    GPIO();
    bool alreadyStarted();
    void gpioWrite(string comm);
    string gpioReadStatus();
    string gpioReadTimer();
    string gpioReadUnit(int unit);
};

#endif // GPIOOPE_H
