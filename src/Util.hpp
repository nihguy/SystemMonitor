#ifndef PROJECT_UTIL_HPP
#define PROJECT_UTIL_HPP

#include <string>
#include <fstream>

// Classic helper function
class Util {
 public:
  static std::string convertToTime ( long int input_seconds );
  static std::string getProgressBar(std::string percent);
  static std::ifstream getStream(std::string path);
  static std::string padding(std::string str, int fixed_pad);
};

#endif //PROJECT_UTIL_HPP
