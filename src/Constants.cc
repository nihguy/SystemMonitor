#include "Constants.hpp"

std::string Path::basePath ()
{
  return "/proc/";
}

std::string Path::cmdPath ()
{
  return "/cmdline";
}

std::string Path::statusPath ()
{
  return "/status";
}

std::string Path::statPath ()
{
  return "stat";
}

std::string Path::upTimePath ()
{
  return "uptime";
}

std::string Path::memInfoPath ()
{
  return "meminfo";
}

std::string Path::versionPath ()
{
  return "version";
}