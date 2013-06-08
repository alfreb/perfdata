#ifndef CPUSAMPLE_H
#define CPUSAMPLE_H

#include <string>

#include "globals.h"

namespace perfdata{
    
  /*
    Performance data from a single CPU, at one point in time
  */
  class cpuSample{  
    static int prop_count;
    static std::string prop_names[CPU_PROP_COUNT];

        
    //Actual data
    unsigned long long props[CPU_PROP_COUNT];  
    std::string rest;
    std::string cpu_name;
    friend class cpuDataPoint;
    
    
  public:
    //Construct
    //All data is read from stream - no stream no sample    
    cpuSample(std::string name,std::ifstream* fs=0);    
    cpuSample& operator=(cpuSample& s);
    
    //Get categorized sums, for cpu-load calculation
    unsigned long sumTotalJiffies();
    unsigned long sumWorkJiffies();
    
    //String representation
    std::string toTabsep(std::string="\t");
    std::string titles(std::string="\t");

  };


}

#endif
