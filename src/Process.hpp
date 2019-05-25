//
// Created by victor on 5/20/19.
//

#ifndef PROJECT_PROCESS_HPP
#define PROJECT_PROCESS_HPP

#include <string>
#include "ProcessParser.hpp"

/*
 * Basic class for Process representation
 * It contains relevant attributes as shown below
 */
class Process {
 public:
  Process(std::string pid);
  void setPid(int pid);
  std::string getPid() const;
  std::string getUser() const;
  std::string getCmd() const;
  int getCpu() const;
  int getMem() const;
  std::string getUpTime() const;
  std::string getProcess();

 private:
  std::string pid;
  std::string user;
  std::string cmd;
  std::string cpu;
  std::string mem;
  std::string upTime;
};

#endif //PROJECT_PROCESS_HPP
