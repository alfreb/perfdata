#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "cpuDataPoint.h"

using namespace perfdata;
using namespace std;

cpuDataPoint::cpuDataPoint(){
  string firstWord;
  string rest;
  sample_time=time(0);
  procstat.open("/proc/stat");
  //cout << "Started at " << sample_time << endl;
  if(!procstat.is_open()){
    throw "Could not open /proc/stat"; 
  }  
  
  while(procstat.good()){
    procstat >> firstWord; //get first word 
    if(firstWord.substr(0,3)=="cpu"){
      //Create a cpu-sample, add it to the vector
      //This requires the couSample constructor to consume a whole line from procstat
      cpuSamples.push_back(cpuSample(firstWord,&procstat));
    }else{
      
      //Here the other properties should be gathered...
      contextSwiches=bootTime=processCount=procs_running=procs_blocked=0;
      // ...
      //...And then the rest of the line must be consumed
      getline(procstat,rest);
    }
  }
  
  procstat.close();
  
};


string cpuDataPoint::toTabsep(string sep){
  stringstream sstr;
  for(vector<cpuSample>::iterator it=cpuSamples.begin();
      it!=cpuSamples.end();it++){
    sstr << it->toTabsep(sep) << sep;
  }
  
  return sstr.str();
};

string  cpuDataPoint::titles(string sep){
  stringstream sstr;
  for(vector<cpuSample>::iterator it=cpuSamples.begin();
      it!=cpuSamples.end();it++){
    sstr << it->titles(sep) << sep;
  }
  
  return sstr.str();
}
