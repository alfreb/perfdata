#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>



using namespace std;

//Number of columns pr. cpu in /proc/stat
#define CPU_PROP_COUNT 7

//Names for the columns
enum cpu_prop {USER,NICE,SYSTEM,IDLE,IOWAIT,IRQ,SOFTIRQ}; 

/*
  Performance data from a single CPU, at one point in time
*/
class cpuSample{  
  static int prop_count;
  static string prop_names[CPU_PROP_COUNT];
  long props[CPU_PROP_COUNT];  
  string rest;
  string cpu_name;
  friend class cpuDataPoint;
  
public:
  cpuSample(ifstream &fs,string name);
  
};


/*
  A collection of all interesting CPU data, for one point in time
  - Contains cpuSamples for each cpu, as well as other /proc/stat info
  - Currently this class is just a structured representation of /proc/stat
*/
class cpuDataPoint{
  long sample_time;
  vector<cpuSample> cpuSamples;
  long contextSwiches;
  long bootTime;
  long processCount;
  long procs_running;
  long procs_blocked;
  
  ifstream procstat;
public:
  cpuDataPoint();
};



string cpuSample::prop_names[]={"User","nice","system","idle","iowait","irq","softirq"};
int cpuSample::prop_count=CPU_PROP_COUNT;

cpuSample::cpuSample(ifstream &fs,string name){  
  cout << "Getting cpu data " << endl;
  cpu_name=name;
  cout << "Cpu: " << name << " ";
  for(int i=0;i<prop_count;i++){
    fs >> props[i];
    cout << prop_names[i] << ": " << props[i] << " ";
  }
  cout << endl;
  getline(fs,rest);
}


class memSample{
  int time;
};


class perfCollector{  
  //cpuDataPoints cpu;
  //memDataPoints mem
public:
  void getData();  
};
  
void perfCollector::getData(){
  cpuDataPoint cpuData;
};

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

int main(){

  perfCollector perf;
  perf.getData();
  //perf.getData();
  cout << "hey" << endl;
}
