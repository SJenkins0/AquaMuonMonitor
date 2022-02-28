======================================

To compile:
$ g++ -o AquaMuonMonitor AquaMuonMonitor.cxx timeOpe.cpp gpioOpe.cpp -L/usr/local/lib -lwiringPi

To run:
$ sudo ./AquaMuonMonitor [command]

IMPORTANT - sudo required due to GPIO permissions!
Usage:
-c : Pass command to system. Command options: get, start, stop, reset.
-h : Display this message.

