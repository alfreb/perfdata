#ifndef CPUDATAPOINT_H
#define CPUDATAPOINT_H

#include <vector>
#include <fstream>

//Local includes
#include "cpuSample.h"


namespace perfdata{

  
/*
  A collection of all interesting CPU data, for one point in time
  - Contains cpuSamples for each cpu, as well as other /proc/stat info
  - Currently this class is just a structured representation of /proc/stat
*/
class cpuDataPoint{
  long sample_time;
  std::vector<perfdata::cpuSample> cpuSamples;
  long contextSwiches;
  long bootTime;
  long processCount;
  long procs_running;
  long procs_blocked;
  
  std::ifstream procstat;
  
public:
  cpuDataPoint();
  std::string titles(std::string="\t");
  std::string toTabsep(std::string="\t");
};



}

#endif
