======================================

To compile:
$ g++ -o AquaMuonMonitor AquaMuonMonitor.cxx timeOpe.cpp gpioOpe.cpp -L/usr/local/lib -lwiringPi

To run:
$ ./AquaMuonMonitor [command]

Usage:
-c : Pass command to system. Command options: get, start, stop, reset.
-r : Read data out. Requires specification of file to output to.
-u : Update output file. Default is to override. Only works with -r option.
-h : Display this message.

======================================