
#include <iostream>
#include <string>
#include <vector>
#include "gpioOpe.h"
#include "timeOpe.h"

int main(int argc, char *argv[]){

  if(argc != 2){
    std::cerr << "Only one argument accepted! Pass -h for help." << std::endl; //-h currently does nothing until I figure out flags
    return 1;
  }

  std::string command(argv[1]);


  GPIO gpio;
  Time tm;
  std::string data, startTime;
  startTime = "**************";


  //Start recording
  if (command == "start"){
    //Make sure not already recording
    if(gpio.alreadyStarted() == true)
      std::cout << "Already started. Ignoring command." << std::endl;
    else{
      std::cout << "Starting..." << std::endl;
      //Get current time as start time
      gpio.gpioWrite("start");
      startTime = tm.getTime();
    }
  }
  //Get the data
  else if (command == "get"){

    std::cout << "Getting current data..." << std::endl;
    data = startTime + ", " + tm.getTime() + ", " + gpio.gpioReadTimer() + gpio.gpioReadStatus() + gpio.gpioReadUnit(1) + gpio.gpioReadUnit(2) + gpio.gpioReadUnit(3);
    std::cout << data << std::endl;
    
  }
  //Stop the count
  else if (command == "stop"){
    gpio.gpioWrite("stop");
    data = startTime + ", " + tm.getTime() + ", " + gpio.gpioReadTimer() + gpio.gpioReadStatus() + gpio.gpioReadUnit(1) + gpio.gpioReadUnit(2) + gpio.gpioReadUnit(3);
  }
  //Reset the count
  else if (command == "reset"){
    gpio.gpioWrite("reset");
    startTime = "**************";
  }
  else
    std::cout << "Incorrect command passed." << std::endl;

  
  return 0;
  
}



