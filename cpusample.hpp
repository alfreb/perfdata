#ifndef CPUSAMPLE_HPP
#define CPUSAMPLE_HPP

#include <string>

namespace perfdata{
    
  /*
    Performance data from a single CPU, at one point in time
  */
  class cpuSample{  
    
    static const int CPU_PROP_COUNT{10};
    enum cpu_prop {USER,NICE,SYSTEM,IDLE,IOWAIT,
                   IRQ,SOFTIRQ,STEAL,USER_RT,SYSTEM_RT}; 
    static int prop_count;
    static std::string prop_names[CPU_PROP_COUNT];
        
    //Actual data
    unsigned long long props[CPU_PROP_COUNT];  
    std::string rest;
    std::string cpu_name;
  
    
  public:
    //Construct
    //All data is read from stream - no stream no sample    
    cpuSample(std::string name,std::ifstream* fs=0);    
    cpuSample& operator=(cpuSample& s);
    
    //Get categorized sums, for cpu-load calculation
    unsigned long sumTotalJiffies();
    unsigned long sumWorkJiffies();
    
    //String representation
    std::string toCsv(std::string="\t");
    std::string titles(std::string="\t");

  };


}

#endif
