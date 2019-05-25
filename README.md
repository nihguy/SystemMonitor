# System Monitor in C++

[Português do Brasil](README_pt_br.md)

### Introduction

This project was built following [orientation](https://github.com/udacity/CppND-System-Monitor/) of the [C++ Udacity’s Nanograduation](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The aim of this project is offering some information about all processes being executed on a Linux distribution. It happens through the OS file reading, providing a terminal’s output “similar” to renowned [Htop](https://hisham.hm/htop/). 

### How to install

** Until this moment, this project was tested only on Ubuntu 16.04.6 and Fedora 29 version. **

1. To run the project, it's necessary to install `ncurses` library on your linux distribution.

** On Ubuntu **

```shell
apt-get install libncurses5-dev libncursesw5-dev
```

** On Fedora **

```shell
dnf install ncurses-devel
```

1. To compile the project properly, create a directory `build` and from inside of it, execute the `cmake` and `make` commands as bellow. 

```shell
mkdir build && cd $_
cmake .. && make
```

1. If everyting is fine, the executable will be created inside `build` folder on project's root. In order to run the program properly, just run the executable `Project` located on `bin` directory.

```shell
cd ../bin
./Project
```
