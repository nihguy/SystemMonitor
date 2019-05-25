#ifndef PROJECT_CONSOLE_HPP
#define PROJECT_CONSOLE_HPP

#include <string>
#include <ncurses.h>

#include "SysInfo.hpp"
#include "ProcessContainer.hpp"

class Console {
 public:
  static char* getCString(std::string str);
  static void writeSysInfoToConsole(SysInfo sys, WINDOW* sys_win);
  static void getProcessListToConsole(std::vector<std::string> processes,WINDOW* win);
  static void print(SysInfo sys,ProcessContainer procs);
};

#endif //PROJECT_CONSOLE_HPP
