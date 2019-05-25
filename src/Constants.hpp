#ifndef PROJECT_CONSTANTS_HPP
#define PROJECT_CONSTANTS_HPP

#include <string>

enum CPUStates{
    S_USER = 1,
    S_NICE,
    S_SYSTEM,
    S_IDLE,
    S_IOWAIT,
    S_IRQ,
    S_SOFTIRQ,
    S_STEAL,
    S_GUEST,
    S_GUEST_NICE
};

class Path{
 public:
  static std::string basePath();
  static std::string cmdPath();
  static std::string statusPath();
  static std::string statPath();
  static std::string upTimePath();
  static std::string memInfoPath();
  static std::string versionPath();
};

#endif //PROJECT_CONSTANTS_HPP
