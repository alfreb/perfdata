#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

//Globals
#include "globals.h"

//Classes
#include "cpuSample.h"
#include "cpuDataPoint.h"
#include "memDataPoint.h"

//#include "cpuSample.cpp"
//#include "cpuDataPoint.cpp"

using namespace std;
using namespace perfdata;


class perfCollector{  
  //cpuDataPoints cpu;
  //memDataPoints mem
public:
  void getData();  
};
  
void perfCollector::getData(){
  cpuDataPoint cpuData;
  memDataPoint memData;
};

int main(){
  cout << "Getting performance data" << endl;
  perfCollector perf;
  perf.getData();
  //perf.getData();

}
