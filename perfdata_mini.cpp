#include "cpuSample.h"
#include <fstream>
#include <iostream>

using namespace std;
//using namespace perfdata;



int main(){
    
  unsigned long workDone(0);
  unsigned long jiffiesPassed(0);
  
  float cpuPct;
  long sample_time;  
  ifstream procstat;
  
  sample_time=time(0);
  procstat.open("/proc/stat");
  
  cout << "Started at " << sample_time << endl;
  
  if(!procstat.is_open()){
    throw "Could not open /proc/stat";
  }
  
  perfdata::cpuSample prevSample("totalCpu",&procstat);
  procstat.close();
  procstat.sync();
  while(true){
    ifstream temp_procstat;
    if(temp_procstat.is_open())
      throw "Procstat is open!";
    
    sample_time=time(0);
    temp_procstat.open("/proc/stat");
    
    //    cout << "Started at " << sample_time << endl;

    if(!temp_procstat.is_open()){
      throw "Could not open /proc/stat";
    }
    

    perfdata::cpuSample currentSample("totalCpu",&temp_procstat);
    
    workDone=currentSample.sumWorkJiffies()-prevSample.sumWorkJiffies();
    jiffiesPassed=currentSample.sumTotalJiffies()-prevSample.sumTotalJiffies();
    cpuPct=double(workDone)/(double)jiffiesPassed;
    cout << "Work done: " << workDone << endl;
    cout << "Jiffies: " << jiffiesPassed << endl;
    cout << "CPU load: " << cpuPct<<"%"<<endl;
    prevSample=currentSample;
    

    temp_procstat.sync();
    temp_procstat.close();
    sleep(3);
    
  }
  
}
