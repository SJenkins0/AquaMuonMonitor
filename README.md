======================================

To compile:
$ g++ -o AquaMuonMonitor AquaMuonMonitor.cxx timeOpe.cpp gpioOpe.cpp -L/usr/local/lib -lwiringPi

To run:
$ sudo ./AquaMuonMonitor [command]

sudo is required to run, in order to access GPIO