/** 
    Parsed representation of /proc/stat 
*/
#ifndef STAT_HPP
#define STAT_HPP

#include <vector>
#include <fstream>

//Local includes
#include "cpusample.hpp"


namespace perfdata{

  
  /**
     A collection of all interesting CPU data, for one point in time
     - Contains cpuSamples for each cpu, as well as other /proc/stat info
     - Currently this class is just a structured representation of /proc/stat
  */
  class Stat{
    long sample_time;
    
    /**
       A list of cpu-metrics, 1 for each CPU. 
       NOTE: The first CPU is an aggregate of all cores.
    **/
    std::vector<perfdata::cpuSample> cpuSamples;
    long contextSwiches;
    long bootTime;
    long processCount;
    long procs_running;
    long procs_blocked;
    
    std::ifstream procstat;
    
  public:
    Stat();
    std::string titles(std::string="\t");
    std::string toCsv(std::string="\t");
  };
  


}

#endif
