#include "Process.hpp"

Process::Process (std::string pid)
{
  this->pid = pid;
  this->user = ProcessParser::getProcUser(pid);
  this->mem = ProcessParser::getVmSize(pid);
  this->cmd = ProcessParser::getCmd(pid);
  this->upTime = ProcessParser::getProcUpTime(pid);
  this->cpu  = ProcessParser::getCpuPercent(pid);
}

void Process::setPid (int pid)
{
  this->pid = std::to_string (pid);
}

std::string Process::getPid () const
{
  return this->pid;
}

std::string Process::getUser () const
{
  return this->user;
}

std::string Process::getCmd () const
{
  return this->cmd;
}

int Process::getCpu () const
{
  return stoi(this->cpu);
}

int Process::getMem () const
{
  return stoi(this->mem);
}

std::string Process::getUpTime () const
{
  return this->upTime;
}

std::string Process::getProcess ()
{
  if(!ProcessParser::isPidExisting(this->pid)) {
    return "";
  }

  this->mem = ProcessParser::getVmSize(this->pid);
  this->upTime = ProcessParser::getProcUpTime(this->pid);
  this->cpu = ProcessParser::getCpuPercent(this->pid);

  std::string command = this->cmd;

  if (command.length() >= 47) {
      command = command.substr(0, 47);
      command += "...";
    }

  return (
      Util::padding(this->pid, 7) +
      Util::padding(this->cpu.substr(0, 8), 10) +
      Util::padding(this->mem.substr(0, 8), 10) +
      Util::padding(this->upTime.substr(0, 8), 10) +
      Util::padding(this->user.substr(0, 8), 10) +
      command
  );
}

