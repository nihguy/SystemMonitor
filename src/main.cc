#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <ncurses.h>
#include <time.h>
#include <sstream>
#include <iomanip>

#include "Util.hpp"
#include "SysInfo.hpp"
#include "ProcessContainer.hpp"
#include "Console.hpp"

auto main() -> int {
  //Object which contains list of current processes, Container for Process Class
  ProcessContainer procs;

  // Object which containts relevant methods and attributes regarding system details
  SysInfo sys;

  // Prints system info on console.
  Console::print(sys, procs);

  return EXIT_SUCCESS;
}

