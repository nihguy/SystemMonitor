//
// Created by victor on 5/20/19.
//

#ifndef PROJECT_PROCESSCONTAINER_HPP
#define PROJECT_PROCESSCONTAINER_HPP

#include "Process.hpp"
#include <vector>

class ProcessContainer {
 public:
  ProcessContainer();
  void refreshList();
  std::string printList();
  std::vector<std::vector<std::string>> getList();

 private:
  std::vector<Process>_list;
};

#endif //PROJECT_PROCESSCONTAINER_HPP
