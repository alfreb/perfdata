#include <iostream>
#include "cpuDataPoint.h"

using namespace perfdata;
using namespace std;

cpuDataPoint::cpuDataPoint(){
  string firstWord;
  string rest;
  sample_time=time(0);
  procstat.open("/proc/stat");
  //  cout << "Started at " << sample_time << " ";
  while(procstat.good()){
    procstat >> firstWord; //get first word 
    if(firstWord.substr(0,3)=="cpu"){
      //Create a cpu-sample, add it to the vector
      //This requires the couSample constructor to consume a whole line from procstat
      cpuSamples.push_back(cpuSample(procstat,firstWord));
    }else{
      
      //Here the other properties should be gathered...
      contextSwiches=bootTime=processCount=procs_running=procs_blocked=0;
      // ...
      //...And then the rest of the line must be consumed
      getline(procstat,rest);
    }
  }
  cout << "Done" << endl;
  procstat.close();
  
};
