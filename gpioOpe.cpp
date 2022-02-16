#include "gpioOpe.h"

//#define DUMMY_DATA  1 //  dummy data output

// constructor
GPIO::GPIO()
{
    // wiringPi initialization
    if(wiringPiSetupGpio() == -1)
    {
        exit(1);
    }

    // Set the CS0～CS3、A[1]～A[4]、SEL_LH、WT pins to GPIO output
    pinMode(CS_0, OUTPUT);
    pinMode(CS_1, OUTPUT);
    pinMode(CS_2, OUTPUT);
    pinMode(CS_3, OUTPUT);
    pinMode(A_1, OUTPUT);
    pinMode(A_2, OUTPUT);
    pinMode(A_3, OUTPUT);
    pinMode(A_4, OUTPUT);
    pinMode(SEL_LH, OUTPUT);
    pinMode(WT, OUTPUT);

    // Set the RD[3] to RD[15] pins to GPIO input
    pinMode(RD_03, INPUT);
    pinMode(RD_04, INPUT);
    pinMode(RD_05, INPUT);
    pinMode(RD_06, INPUT);
    pinMode(RD_07, INPUT);
    pinMode(RD_08, INPUT);
    pinMode(RD_09, INPUT);
    pinMode(RD_10, INPUT);
    pinMode(RD_11, INPUT);
    pinMode(RD_12, INPUT);
    pinMode(RD_13, INPUT);
    pinMode(RD_14, INPUT);
    pinMode(RD_15, INPUT);
}

// GPIO mode-initialization (Read)
void GPIO::gpioModeInitRead()
{
    // Set the RD[0] to RD[2] pins to GPIO input
    pinMode(RD_00, INPUT);
    pinMode(RD_01, INPUT);
    pinMode(RD_02, INPUT);
}

// GPIO mode-initialization (Write)
void GPIO::gpioModeInitWrite()
{
    // Set the RD[0] to RD[2] pins to GPIO output
    pinMode(RD_00, OUTPUT);
    pinMode(RD_01, OUTPUT);
    pinMode(RD_02, OUTPUT);
}

// GPIO initialization (General)
void GPIO::gpioInitGen()
{
    // Output 0 to CS0～CS3、A[1]～A[4]、SELL_LH、WT pins
    digitalWrite(CS_0, 0);
    digitalWrite(CS_1, 0);
    digitalWrite(CS_2, 0);
    digitalWrite(CS_3, 0);
    digitalWrite(A_1, 0);
    digitalWrite(A_2, 0);
    digitalWrite(A_3, 0);
    digitalWrite(A_4, 0);
    digitalWrite(SEL_LH, 0);
    digitalWrite(WT, 0);
}

// Output 0 or 1 to any of the CS0 to CS3 pins, depending on the specified unit
void GPIO::gpioWriteUnit(int unit, int output)
{
  if (unit == 1)
  {
      // Output 0 or 1 to CS1
      digitalWrite(CS_1, output);
  }
  else if (unit == 2)
  {
      // Output 0 or 1 to CS2
      digitalWrite(CS_2, output);
  }
  else if (unit == 3)
  {
      // Output 0 or 1 to CS3
      digitalWrite(CS_3, output);
  }
}

// Determine whether the counter already started or not
bool GPIO::alreadyStarted()
{
    // GPIO mode-initialization
    gpioModeInitRead();

    // GPIO initialization
    gpioInitGen();

    // Output 1 to CS0
    digitalWrite(CS_0, 1);
    delayMicroseconds(1);

    // Get status value from RD[12] and return the status
    if (digitalRead(RD_12) == 1)
    {
        // Output 0 to CS0
        digitalWrite(CS_0, 0);
        return true;
    }
    // Output 0 to CS0
    digitalWrite(CS_0, 0);
    return false;
}

// Write start, stop, or reset
void GPIO::gpioWrite(string comm)
{
    // GPIO mode-initialization
    gpioModeInitWrite();

    // GPIO initialization
    gpioInitGen();

    // Output 1 to WT pin
    digitalWrite(WT, 1);

    // Change the processing depending on the command received on the Internet
    if (comm == "start")
    {
        digitalWrite(RD_00, 1);
        digitalWrite(RD_01, 0);
        digitalWrite(RD_02, 0);
    }
    else if (comm == "stop")
    {
        digitalWrite(RD_00, 0);
        digitalWrite(RD_01, 1);
        digitalWrite(RD_02, 0);
    }
    else if (comm == "reset")
    {
        digitalWrite(RD_00, 0);
        digitalWrite(RD_01, 0);
        digitalWrite(RD_02, 1);
    }

    // Output 1 to CS0
    digitalWrite(CS_0, 1);

    // Wait for 10 msec
    delayMicroseconds(10);

    // Output 0 to CS0
    digitalWrite(CS_0, 0);

    // Output 0 to WT pin
    digitalWrite(WT, 0);
}

// Read status register data
string GPIO::gpioReadStatus()
{
    // GPIO mode-initialization
    gpioModeInitRead();

    // GPIO initialization
    gpioInitGen();

    // Output 1 to CS0
    digitalWrite(CS_0, 1);
    delayMicroseconds(1);

    binRes = "";
    ss.str("");

    // Get count value from RD[0] to RD[15]
    for (vector<int>::size_type i = 0; i < RD_PORT; i++)
    {
        binRes.insert(0, to_string(digitalRead(readGPIO.at(i))));
    }

    // Output 0 to CS0
    digitalWrite(CS_0, 0);

    ss << uppercase << hex << setfill('0') << right << setw(4) << stoul(binRes, nullptr, 2);
    res = ss.str() + ", ";
#ifdef DUMMY_DATA
    res = "1124, "; // dummy data
#endif  // DUMMY_DATA
    return res;
}

// Read timer data
string GPIO::gpioReadTimer()
{
    // GPIO mode-initialization
    gpioModeInitRead();

    // GPIO initialization
    gpioInitGen();

    binUpper = "";
    binLower = "";
    binRes = "";
    ss.str("");

    addr = 1;
    // Output channel numbers to A[1]-A[4]
    for (vector<int>::size_type i = 0; i < ADDR_PORT; i++)
    {
        digitalWrite(addrGPIO.at(i), ((addr >> i) & 1));
    }

    // Output 1 to CS0
    digitalWrite(CS_0, 1);
    delayMicroseconds(1);

    // Get count value from RD[0] to RD[15]
    for (vector<int>::size_type i = 0; i < RD_PORT; i++)
    {
        binUpper.insert(0, to_string(digitalRead(readGPIO.at(i))));
    }

    // Output 0 to CS0
    digitalWrite(CS_0, 0);

    addr = 2;
    // Output channel numbers to A[1]-A[4]
    for (vector<int>::size_type i = 0; i < ADDR_PORT; i++)
    {
        digitalWrite(addrGPIO.at(i), ((addr >> i) & 1));
    }

    // Output 1 to CS0
    digitalWrite(CS_0, 1);
    delayMicroseconds(1);

    // Get count value from RD[0] to RD[15]
    for (vector<int>::size_type i = 0; i < RD_PORT; i++)
    {
        binLower.insert(0, to_string(digitalRead(readGPIO.at(i))));
    }

    // Output 0 to CS0
    digitalWrite(CS_0, 0);

    // Obtain the count value in hexadecimal
    binRes = binUpper + binLower;
    ss << hex << setfill('0') << right << setw(8) << stoul(binRes, nullptr, 2);
    res = ss.str() + ", ";
#ifdef DUMMY_DATA
    res = "00001234, ";     // dummy data
#endif  // DUMMY_DATA
    return res;
}

// Read the unit's count data
string GPIO::gpioReadUnit(int unit)
{
    // GPIO mode-initialization
    gpioModeInitRead();

    // GPIO initialization
    gpioInitGen();

    addr = 0;
    res = "";

    // Repeat 10 times
    for (int i = 0; i < 10; i++)
    {
        binUpper = "";
        binLower = "";
        ss.str("");

        // Output channel numbers to A[1]-A[4]
        for (vector<int>::size_type j = 0; j < ADDR_PORT; j++)
        {
            digitalWrite(addrGPIO.at(j), ((addr >> j) & 1));
        }
        addr++;

        // Output 1 to any of the CS0 to CS3 pins
        gpioWriteUnit(unit, 1);
        delayMicroseconds(1);

        // Get count value from RD[0] to RD[15]
        for (vector<int>::size_type k = 0; k < RD_PORT; k++)
        {
            binUpper.insert(0, to_string(digitalRead(readGPIO.at(k))));
        }

        // Output 0 to any of the CS0 to CS3 pins
        gpioWriteUnit(unit, 0);

        // Output 1 to SEL_LH
        digitalWrite(SEL_LH, 1);

        // Output 1 to any of the CS0 to CS3 pins
        gpioWriteUnit(unit, 1);
        delayMicroseconds(1);

        // Get count value from RD[0] to RD[15]
        for (vector<int>::size_type k = 0; k < RD_PORT; k++)
        {
            binLower.insert(0, to_string(digitalRead(readGPIO.at(k))));
        }

        // Output 0 to any of the CS0 to CS3 pins
        gpioWriteUnit(unit, 0);

        // Output 0 to SEL_LH
        digitalWrite(SEL_LH, 0);

        // Obtain the count value in hexadecimal
        binRes = binUpper + binLower;
        ss << hex << setfill('0') << right << setw(8) << stoul(binRes, nullptr, 2);
#ifdef DUMMY_DATA
        res += "87654321, ";     // dummy data
#else   // DUMMY_DATA
        res += ss.str() + ", ";
#endif  // DUMMY_DATA
    }

    // Get the overflow bit
    binRes = "";
    ss.str("");

    // Output channel numbers to A[1]-A[4]
    for (vector<int>::size_type j = 0; j < ADDR_PORT; j++)
    {
        digitalWrite(addrGPIO.at(j), ((addr >> j) & 1));
    }

    // Output 1 to SEL_LH
    digitalWrite(SEL_LH, 1);

    // Output 1 to any of the CS0 to CS3 pins
    gpioWriteUnit(unit, 1);
    delayMicroseconds(1);

    // Get count value from RD[0] to RD[09]
    for (vector<int>::size_type k = 0; k < OF_PORT; k++)
    {
        binRes.insert(0, to_string(digitalRead(readGPIO.at(k))));
    }

    // Output 0 to any of the CS0 to CS3 pins
    gpioWriteUnit(unit, 0);

    // Output 0 to SEL_LH
    digitalWrite(SEL_LH, 0);

    // Obtain the count value in hexadecimal
    ss << uppercase << hex << setfill('0') << right << setw(4) << stoul(binRes, nullptr, 2);
#ifdef DUMMY_DATA
    res += "0000, ";     // dummy data
#else   // DUMMY_DATA
    res += ss.str() + ", ";
#endif  // DUMMY_DATA

    // Return count data
    return res;
}
