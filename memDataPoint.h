#ifndef MEMDATAPOINT_H
#define MEMDATAPOINT_H

#include <fstream>
#include <map>

//Local includes
#include "dataPoint.h"

namespace perfdata{

  /*
  A collection of all interesting memory data, for one point in time
  - A Structured representation of some of the stuff in /proc/meminfo
  */
  #define PROP_COUNT 7
  class memDataPoint:dataPoint{
    std::ifstream meminfo;
    static const int prop_count;
    static const std::string prop_names[];
    unsigned long sample_time;
    unsigned long memTotal;
    unsigned long memFree;
    unsigned long buffers;
    unsigned long cached;
    unsigned long swapCached;
    unsigned long active;
    unsigned long inactive;    
    //unsigned long* props[PROP_COUNT];
    std::map<std::string,long> propMap;
  public:
    memDataPoint();
    std::string toTabsep(std::string="\t");
    std::string titles(std::string="\t");
    float pctUsed();
  };

}//End namespace perfdata

#endif
