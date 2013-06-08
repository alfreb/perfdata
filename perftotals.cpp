#include <iostream>
#include <fstream>
#include <sstream>

#include "cpuSample2.h"
#include "globals.h"
#include "memDataPoint.h"

using namespace std;

int main(int argc, char** argv){  

  bool logToFile=false;
  const char* logfile="./perftotals.log";
  ofstream logstream;

  //Sample rate, in seconds
  int interval(1);
  
  if(argc>1){
    if(string(argv[1])==string("-l")){
      logToFile=true;
      cout << "Logging to file: " << logfile<< endl;
    }  
  }
  
  cpuSample prevSample;
  
  float cpuPct;
  float memPct;

  string sep="\t";
  
  int t1=time(0);
  int t(0);
  
  cout << "time" << sep << "cpu_%" << sep << "mem_%"<<endl;
  if(logToFile){
    logstream.open(logfile);
    logstream << "time" << sep << "cpu_%" << sep << "mem_%"<<endl;
  }
  
  
  
  while(true){

    //Gather samples
    cpuSample currentSample;
    perfdata::memDataPoint m;
    
    //Calculate data points
    t=time(0)-t1;
    cpuPct=cpuSample::pctUsed(prevSample,currentSample);
    memPct=m.pctUsed();
    
    //Print to screen
    cout << t << sep << cpuPct << sep << memPct << endl;
    
    if(logToFile and logstream.good())
      logstream << t << sep << cpuPct << sep << memPct << endl;
    
    //Remember cpu-sample for next time
    prevSample=currentSample;
    
    //Round complete
    sleep(interval);
  }
}
