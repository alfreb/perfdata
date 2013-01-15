#include <iostream>
#include <fstream>
#include <sstream>

#include <string>



using namespace std;

class cpuSample{
  int time;
  int cpu_user;
  int cpu_nice;
  int cpu_system;
  int cpu_idle;
  int cpu_iowait;
  int cpu_irq;
  int cpu_softirq;
  int cpun_max;
  int cpun_min;  
  friend class perfCollector;
};

class perfCollector{
  ifstream procstat;
  void getCPUData();
public:
  void getData();  
};
  
void perfCollector::getData(){
  getCPUData();
};

void perfCollector::getCPUData(){
  string line;
  string word;
  stringstream ss;
  cpuSample cpu;
  procstat.open("/proc/stat");
  while(procstat.good()){
    procstat >> word; //get first word 
    if(word=="cpu"){
      //Could get rest of the line now, with:
      //getline(procstat,line);      
      procstat >> cpu.
      cout << "Cpu : " << line << endl;
    }    
  }
  procstat.close();
};

int main(){
  perfCollector perf;
  perf.getData();
  perf.getData();
  cout << "hey" << endl;
}
