
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
  std::string data;
  
  if (command == "get"){

    std::cout << "Getting current data" << std::endl;
    data = gpio.gpioReadTimer() + gpio.gpioReadStatus() + gpio.gpioReadUnit(1) + gpio.gpioReadUnit(2) + gpio.gpioReadUnit(3);
    std::cout << data << std::endl;
    
  }
  else if (command == "start"){
    if(gpio.alreadyStarted() == true)
      std::cout << "Already started." << std::endl;
    else
      std::cout << "Not started." << std::endl;
  }


  
  return 0;
  
}



