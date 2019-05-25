#ifndef PROJECT_PROCESSPARSER_HPP
#define PROJECT_PROCESSPARSER_HPP

#include <algorithm>
#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>
#include <iterator>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cerrno>
#include <cstring>
// TODO: use std::filesystem from c++17 instead of dirent.h
#include <dirent.h>
#include <time.h>
#include <unistd.h>

#include "Constants.hpp"
#include "Util.hpp"


class ProcessParser {
 public:
  static std::string getCmd(std::string pid);
  static std::vector<std::string> getPidList();
  static std::string getVmSize(std::string pid);
  static std::string getCpuPercent(std::string pid);
  static long int getSysUpTime();
  static std::string getProcUpTime(std::string pid);
  static std::string getProcUser(std::string pid);
  static std::vector<std::string> getSysCpuPercent(std::string coreNumber = "");
  static float getSysRamPercent();
  static std::string getSysKernelVersion();
  static int getTotalThreads();
  static int getTotalNumberOfProcesses();
  static int getNumberOfRunningProcesses();
  static std::string getOSName();
  static std::string PrintCpuStats(std::vector<std::string> values1, std::vector<std::string>values2);
  static bool isPidExisting(std::string pid);
 private:
  std::ifstream stream;
};

int getNumberOfCores();
float getSysActiveCpuTime(std::vector<std::string> values);
float getSysIdleCpuTime(std::vector<std::string>values);


#endif //PROJECT_PROCESSPARSER_HPP
