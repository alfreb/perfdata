#include <fstream>
#include <stdexcept>

//Locals
#include "pidstat.hpp"


using namespace std;
using namespace perfdata;

Pidstat::Pidstat(int _pid){
  ifstream stat{"/proc/"+to_string(_pid)+"/stat"};
  
  if(not (stat.is_open() and stat.good()))
    throw PidstatException{"Couldn't open stat for PID "+to_string(_pid)};

  stat >> pid_ >> filename_ >> state_ >> ppid_ >>  pgrp_ >> session_
       >> tty_nr_ >> tpgid_ >> flags_ >> minflt_ >> cminflt_ >> majflt_ 
       >> cmajflt_ >> utime_ >> stime_ >> cutime_ >> cstime_ >> priority_ 
       >> nice_ >> num_threads_ >> itrealvalue_ >> starttime_ >> vsize_ 
       >> rss_ >> rlim_ >> startcode_ >> endcode_ >> startstack_ >> kstkesp_ 
       >> kstkeip_ >> signal_ >> blocked_ >> sigignore_ >>  sigcatch_ >> wchan_ 
       >> nswap_ >> cnswap_ >> exit_signal_ >> processor_ >> rt_priority_ 
       >> policy_ >> delayacct_blkio_ticks_ >> guest_time_ >> cguest_time_;
  
  // Remove parenthesis from filename
  filename_ = filename_.substr(1,filename_.size() -2);
  stat.close();

}

std::ostream& perfdata::operator<<(std::ostream& str,Pidstat& p){
  return str << p.filename_ << " Pid: " << p.pid_ <<  " state: " 
             << p.state_ << " ppid: " << p.ppid_ 
             << " threads: " << p.num_threads_ 
             << " utime: " << p.utime_<< " stime: " << p.stime_ 
             << " cutime: " << p.cutime_ << " cstime: " << p.cstime_;
}

