#include <iostream>
#include <unistd.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "gpioOpe.h"
#include "timeOpe.h"



//Take the data and print it to screen in a reader friendly format
void output(std::string data, std::string time, bool running){

  char del = ',';
  std::vector<string> val;
  std::string count;
  std::vector<string> A, B, C;

  std::stringstream sstream(data);
  std::string str;
  while(std::getline(sstream, str, del)){
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    val.push_back(str);
  }
  std::string status = running ? "\033[32mRecording\033[0m" : "\033[31mStopped\033[0m\t";
  
  for(int i=0; i<val.size()-1; i++){//-1 ignores the white space on last entry

    if(i==0) count = val.at(i);
    else if (i<12) A.push_back(val.at(i));
    else if (i<23) B.push_back(val.at(i));
    else           C.push_back(val.at(i));
  }

  //Formatting
  std::cout << "################################### UK-HKMSDD ###################################" << std::endl;
  std::cout << "#\t\t\t\t\t\t\t\t\t\t#"                               << std::endl;
  std::cout << "#\t\tCurrent time (JST):\t" << time << "\t\t\t#"      << std::endl;
  std::cout << "#\t\tTime since start /s:\t" << count << "\t\t\t\t#"  << std::endl;
  std::cout << "#\t\tStatus:\t\t\t" << status << "\t\t\t\t#"        << std::endl;
  std::cout << "#\t\t\t\t\t\t\t\t\t\t#"                               << std::endl;
  std::cout << "#\t\t    A \t\t\t    B \t\t       Coincidence \t#"    << std::endl;
    std::cout << "#\t\t\t\t\t\t\t\t\t\t#"                             << std::endl;
  for(int i=0; i<A.size(); i++){
    if(i<10)
      printf("#\t D%i \t%s\t\t%s\t\t%s\t#\n",i, A[i].c_str(), B[i].c_str(), C[i].c_str());
    else
      printf("#  Overflow\t    %s\t\t    %s\t\t    %s\t#\n",A[i].c_str(), B[i].c_str(), C[i].c_str());
  }
  std::cout << "#\t\t\t\t\t\t\t\t\t\t#"                               << std::endl; 
  std::cout << "#\t\t\t\t\t\t\t\t\t\t#"                               << std::endl;
    std::cout << "#################################################################################" << std::endl;
}




int main(int argc, char *argv[]){


  std::string command;

  if(argc<2){
    std::cout << "[ERROR]: Arguments required!" << std::endl;
    exit(1);
  }

  int option;
  while((option = getopt(argc, argv, ":c:h")) != -1){
    switch(option)
      {
      case 'c':
	command = optarg;
	break;
      case 'h':
	std::cout << "IMPORTANT - sudo required due to GPIO permissions!" << std::endl;
	std::cout << "Usage:" << std::endl;
	std::cout << "-c : Pass command to system. Command options: get, start, stop, reset.\n"
		  << "-h : Display this message.\n";
	exit(0);
      case ':':
	printf("[ERROR]: -%c requires an argument to pass command.\n", optopt);
	exit(1);
      case '?':
	printf("[ERROR]: -%c is an unknown argument. Consider -h for help.\n", optopt);
	exit(1);
	
      default:
	std::cout << "[ERROR]: command argument -c required. Consider -h for help." << std::endl;
	exit(1);
      }
  }


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
    std::string time = tm.getTime();
    data = gpio.gpioReadTimer() + gpio.gpioReadUnit(1) + gpio.gpioReadUnit(2) + gpio.gpioReadUnit(3);
    //std::cout << data << std::endl;
    output(data, time, gpio.alreadyStarted());
    
  }
  //Stop the count
  else if (command == "stop"){
    gpio.gpioWrite("stop");
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
