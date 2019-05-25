#include "Console.hpp"

char *Console::getCString (std::string str)
{
  char * cstr = new char [str.length()+1];
  std::strcpy (cstr, str.c_str());
  return cstr;
}

void Console::writeSysInfoToConsole (SysInfo sys, WINDOW *sys_win)
{
  sys.setAttributes();

  wattron(sys_win,COLOR_PAIR(3));
  mvwprintw(sys_win,2,2,getCString(( "OS: " + sys.getOSName())));
  mvwprintw(sys_win,3,2,getCString(( "Kernel version: " + sys.getKernelVersion())));
  wattroff(sys_win,COLOR_PAIR(3));

  wattron(sys_win,COLOR_PAIR(2));
  mvwprintw(sys_win,4,2,getCString( Util::padding("CPU:", 8)));
  wprintw(sys_win,getCString(Util::getProgressBar(sys.getCpuPercent())));
  wattroff(sys_win,COLOR_PAIR(2));

  mvwprintw(sys_win,5,2,getCString(( "Cores:")));

  wattron(sys_win,COLOR_PAIR(2));
  std::vector<std::string> val = sys.getCoresStats();

  for(int i=0;i<val.size();i++){
    mvwprintw(sys_win,(6+i),2,getCString(val[i]));
  }
  wattroff(sys_win,COLOR_PAIR(1));

  wattron(sys_win,COLOR_PAIR(1));
  mvwprintw(sys_win,10,2,getCString(( Util::padding("Memory: ", 8))));
  wprintw(sys_win,getCString(Util::getProgressBar(sys.getMemPercent())));
  wattroff(sys_win,COLOR_PAIR(1));

  mvwprintw(sys_win,11,2,getCString(( "Total Processes:" + sys.getTotalProc())));
  mvwprintw(sys_win,12,2,getCString(( "Running Processes:" + sys.getRunningProc())));
  mvwprintw(sys_win,13,2,getCString(( "Up Time: " + Util::convertToTime(sys.getUpTime()))));

  wrefresh(sys_win);
}

void Console::getProcessListToConsole (std::vector<std::string> processes, WINDOW *win)
{
  wattron(win,COLOR_PAIR(3));
  mvwprintw(win,1,2,"PID:");
  mvwprintw(win,1,9,"CPU[%%]:");
  mvwprintw(win,1,19,"RAM[MB]:");
  mvwprintw(win,1,29,"Uptime:");

  mvwprintw(win,1,39,"User:");
  mvwprintw(win,1,49,"CMD:");
  wattroff(win, COLOR_PAIR(3));

  for(int i=0; i< processes.size();i++){
    mvwprintw(win, 2+i,2,getCString(processes[i]));
  }
}

void Console::print (SysInfo sys, ProcessContainer procs)
{
  initscr();			/* Start curses mode 		  */
  noecho(); // not printing input values
  cbreak(); // Terminating on classic ctrl + c
  start_color(); // Enabling color change of text
  int yMax,xMax;

  getmaxyx(stdscr,yMax,xMax); // getting size of window measured in lines and columns(column one char length)
  WINDOW *sys_win = newwin(17,xMax-1,0,0);
  WINDOW *proc_win = newwin(15,xMax-1,18,0);

  init_pair(1,COLOR_GREEN,COLOR_BLACK);
  init_pair(2,COLOR_CYAN,COLOR_BLACK);
  init_pair(3,COLOR_YELLOW,COLOR_BLACK);

  int counter = 0;

  while(true) {
    box(sys_win,0,0);
    box (proc_win,0,0);
    procs.refreshList();
    std::vector<std::vector<std::string>> processes = procs.getList();
    writeSysInfoToConsole(sys,sys_win);
    getProcessListToConsole(processes[counter],proc_win);
    wrefresh(sys_win);
    wrefresh(proc_win);
    refresh();
    sleep(1);

    if(counter == (processes.size() -1)){
      counter = 0;
    }
    else {
      counter++;
    }
  }
  endwin();
}
