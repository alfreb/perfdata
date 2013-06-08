#ifndef CPU_SAMPLE_H
#define CPU_SAMPLE_H

#include <iostream>
#include <fstream>

#include "globals.h"

class cpuSample{
  std::string cpu_name;
  std::ifstream f;
  unsigned long props[CPU_PROP_COUNT];
  static std::string prop_names[CPU_PROP_COUNT]; 
  
public:  
  cpuSample();
  cpuSample& operator=(cpuSample& s);  
  unsigned long sumTotalJiffies();  
  unsigned long sumWorkJiffies();  
  std::string titles(std::string sep);
 
  static float pctUsed(cpuSample& s1, cpuSample& s2);
  
};

#endif
