#include "ProcessParser.hpp"

std::string ProcessParser::getCmd (std::string pid)
{
  std::string line;
  std::ifstream stream = Util::getStream((Path::basePath() + pid + Path::cmdPath()));
  std::getline(stream, line);

  return line;
}

std::vector<std::string> ProcessParser::getPidList ()
{
  DIR* dir;
  // Basically, we are scanning /proc dir for all directories with numbers as their names
  // If we get valid check we store dir names in vector as list of machine pids
  std::vector<std::string> container;
  if(!(dir = opendir("/proc")))
    throw std::runtime_error(std::strerror(errno));

  while (dirent* dirp = readdir(dir)) {
    // is this a directory?
    if(dirp->d_type != DT_DIR) {
      continue;
    }

    // Is every character of the name a digit?
    if (std::all_of(dirp->d_name, dirp->d_name + std::strlen(dirp->d_name), [](char c){ return std::isdigit(c); })) {
      container.push_back(dirp->d_name);
    }
  }

  //Validating process of directory closing
  if(closedir(dir)) {
      throw std::runtime_error(std::strerror(errno));
  }

  return container;
}

//Reading /proc/[PID]/status for memory status of specific process
std::string ProcessParser::getVmSize (std::string pid)
{
  std::string line;
  //Declaring search attribute for file
  std::string name = "VmData";
  std::string value;
  float result;
  // Opening stream for specific file
  std::ifstream stream = Util::getStream((Path::basePath() + pid + Path::statusPath()));
  while(std::getline(stream, line)) {
    // Searching line by line
    if (line.compare(0, name.size(),name) == 0) {
      // slicing string line on ws for values using sstream
      std::istringstream buf(line);
      std::istream_iterator<std::string> beg(buf), end;
      std::vector<std::string> values(beg, end);
      //conversion kB -> GB
      result = (stof(values[1])/float(1024));
      break;
    }
  }
  return std::to_string(result);
}

std::string ProcessParser::getCpuPercent (std::string pid)
{
  std::string line;
  std::string value;
  float result;
  std::ifstream stream = Util::getStream((Path::basePath()+ pid + "/" + Path::statPath()));
  getline(stream, line);
  std::string str = line;
  std::istringstream buf(str);
  std::istream_iterator<std::string> beg(buf), end;
  std::vector<std::string> values(beg, end); // done!

  // acquiring relevant times for calculation of active occupation of CPU for selected process
  float utime = stof(ProcessParser::getProcUpTime(pid));
  float stime = stof(values[14]);
  float cutime = stof(values[15]);
  float cstime = stof(values[16]);
  float starttime = stof(values[21]);
  float uptime = ProcessParser::getSysUpTime();
  float freq = sysconf(_SC_CLK_TCK);
  float total_time = utime + stime + cutime + cstime;
  float seconds = uptime - (starttime/freq);
  result = 100.0*((total_time/freq)/seconds);

  return std::to_string(result);
}

long int ProcessParser::getSysUpTime ()
{
  std::string line;
  std::ifstream stream = Util::getStream((Path::basePath() + Path::upTimePath()));
  getline(stream,line);
  std::istringstream buf(line);
  std::istream_iterator<std::string> beg(buf), end;
  std::vector<std::string> values(beg, end);

  return stoi(values[0]);

}

std::string ProcessParser::getProcUpTime (std::string pid)
{
  std::string line;
  std::string value;
  float result;
  std::ifstream stream = Util::getStream((Path::basePath() + pid + "/" +  Path::statPath()));

  getline(stream, line);
  std::string str = line;
  std::istringstream buf(str);
  std::istream_iterator<std::string> beg(buf), end;
  std::vector<std::string> values(beg, end); // done!

  // Using sysconf to get clock ticks of the host machine
  return std::to_string(float(stof(values[13])/sysconf(_SC_CLK_TCK)));
}

std::string ProcessParser::getProcUser (std::string pid)
{
  std::string line;
  std::string name = "Uid:";
  std::string result = "";
  std::ifstream stream = Util::getStream((Path::basePath() + pid + Path::statusPath()));

  // Getting UID for user
  while (std::getline(stream, line)) {
      if (line.compare(0, name.size(),name) == 0) {
          std::istringstream buf(line);
          std::istream_iterator<std::string> beg(buf), end;
          std::vector<std::string> values(beg, end);
          result =  values[1];

          break;
        }
    }
  stream = Util::getStream("/etc/passwd");
  name = ("x:" + result);

  // Searching for name of the user with selected UID
  while (std::getline(stream, line)) {
    if (line.find(name) != std::string::npos) {
      result = line.substr(0, line.find(":"));

      return result;
    }
  }

  return "";
}

std::vector<std::string> ProcessParser::getSysCpuPercent (std::string coreNumber)
{
  // It is possible to use this method for selection of data for overall cpu or every core.
  // when nothing is passed "cpu" line is read
  // when, for example "0" is passed  -> "cpu0" -> data for first core is read
  std::string line;
  std::string name = "cpu" + coreNumber;
  std::string value;
  int result;

  std::ifstream stream = Util::getStream((Path::basePath() + Path::statPath()));
  while (std::getline(stream, line)) {
    if (line.compare(0, name.size(),name) == 0) {
      std::istringstream buf(line);
      std::istream_iterator<std::string> beg(buf), end;
      std::vector<std::string> values(beg, end);

      // set of cpu data active and idle times;
      return values;
    }
  }

  return (std::vector<std::string>());
}

float ProcessParser::getSysRamPercent ()
{
  std::string line;
  std::string name1 = "MemAvailable:";
  std::string name2 = "MemFree:";
  std::string name3 = "Buffers:";

  std::string value;
  int result;
  std::ifstream stream = Util::getStream((Path::basePath() + Path::memInfoPath()));
  float total_mem = 0;
  float free_mem = 0;
  float buffers = 0;

  while (std::getline(stream, line)) {
    if (total_mem != 0 && free_mem != 0) {
      break;
    }

    if (line.compare(0, name1.size(), name1) == 0) {
      std::istringstream buf(line);
      std::istream_iterator<std::string> beg(buf), end;
      std::vector<std::string> values(beg, end);
      total_mem = stof(values[1]);
    }

    if (line.compare(0, name2.size(), name2) == 0) {
      std::istringstream buf(line);
      std::istream_iterator<std::string> beg(buf), end;
      std::vector<std::string> values(beg, end);
      free_mem = stof(values[1]);
    }

    if (line.compare(0, name3.size(), name3) == 0) {
      std::istringstream buf(line);
      std::istream_iterator<std::string> beg(buf), end;
      std::vector<std::string> values(beg, end);
      buffers = stof(values[1]);
    }
  }

  //calculating usage:
  return float(100.0*(1-(free_mem/(total_mem-buffers))));
}

std::string ProcessParser::getSysKernelVersion ()
{
  std::string line;
  std::string name = "Linux version ";
  std::ifstream stream = Util::getStream((Path::basePath() + Path::versionPath()));
  while (std::getline(stream, line)) {
      if (line.compare(0, name.size(),name) == 0) {
          std::istringstream buf(line);
          std::istream_iterator<std::string> beg(buf), end;
          std::vector<std::string> values(beg, end);
          return values[2];
        }
    }
  return "";
}

int ProcessParser::getTotalThreads ()
{
  std::string line;
  int result = 0;
  std::string name = "Threads:";
  std::vector<std::string>_list = ProcessParser::getPidList();

  for (int i=0 ; i<_list.size();i++) {
      std::string pid = _list[i];

      //getting every process and reading their number of their threads
      std::ifstream stream = Util::getStream((Path::basePath() + pid + Path::statusPath()));
      while (std::getline(stream, line)) {
         if (line.compare(0, name.size(), name) == 0) {
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> values(beg, end);
            result += stoi(values[1]);

            break;
         }
      }
    }
  return result;
}

int ProcessParser::getTotalNumberOfProcesses ()
{
  std::string line;
  int result = 0;
  std::string name = "processes";
  std::ifstream stream = Util::getStream((Path::basePath() + Path::statPath()));

  while (std::getline(stream, line)) {
    if (line.compare(0, name.size(), name) == 0) {
       std::istringstream buf(line);
       std::istream_iterator<std::string> beg(buf), end;
       std::vector<std::string> values(beg, end);
       result += stoi(values[1]);

       break;
    }
  }
  return result;
}

int ProcessParser::getNumberOfRunningProcesses ()
{
  std::string line;
  int result = 0;
  std::string name = "procs_running";
  std::ifstream stream = Util::getStream((Path::basePath() + Path::statPath()));

  while (std::getline(stream, line)) {
    if (line.compare(0, name.size(), name) == 0) {
      std::istringstream buf(line);
      std::istream_iterator<std::string> beg(buf), end;
      std::vector<std::string> values(beg, end);
      result += stoi(values[1]);

      break;
    }
  }

  return result;
}

std::string ProcessParser::getOSName ()
{
  std::string line;
  std::string name = "PRETTY_NAME=";

  std::ifstream stream = Util::getStream(("/etc/os-release"));

  while (std::getline(stream, line)) {
     if (line.compare(0, name.size(), name) == 0) {
        std::size_t found = line.find("=");
        found++;
        std::string result = line.substr(found);
        result.erase(std::remove(result.begin(), result.end(), '"'), result.end());

        return result;
     }
  }

  return "";
}

std::string ProcessParser::PrintCpuStats (std::vector<std::string> values1, std::vector<std::string> values2)
{
  /*
   * Because CPU stats can be calculated only if you take measures in two different time,
   * this function has two paramaters: two vectors of relevant values.
   * We use a formula to calculate overall activity of processor.
   */
  float active_time = getSysActiveCpuTime(values2) - getSysActiveCpuTime(values1);
  float idle_time = getSysIdleCpuTime(values2) - getSysIdleCpuTime(values1);
  float total_time = active_time + idle_time;
  float result = 100.0 * (active_time / total_time);
  return std::to_string(result);
}

bool ProcessParser::isPidExisting (std::string pid)
{
  auto list = ProcessParser::getPidList();
  return (std::find(list.begin(), list.end(), pid) != list.end());
}

int getNumberOfCores ()
{
  // Get the number of host cpu cores
  std::string line;
  std::string name = "cpu cores";
  std::ifstream stream = Util::getStream((Path::basePath() + "cpuinfo"));

  while (std::getline(stream, line)) {
    if (line.compare(0, name.size(),name) == 0) {
       std::istringstream buf(line);
       std::istream_iterator<std::string> beg(buf), end;
       std::vector<std::string> values(beg, end);

       return stoi(values[3]);
    }
  }

  return 0;
}

float getSysActiveCpuTime(std::vector<std::string> values)
{
  return (stof(values[S_USER]) +
          stof(values[S_NICE]) +
          stof(values[S_SYSTEM]) +
          stof(values[S_IRQ]) +
          stof(values[S_SOFTIRQ]) +
          stof(values[S_STEAL]) +
          stof(values[S_GUEST]) +
          stof(values[S_GUEST_NICE]));
}

float getSysIdleCpuTime(std::vector<std::string>values)
{
  return (stof(values[S_IDLE]) + stof(values[S_IOWAIT]));
}