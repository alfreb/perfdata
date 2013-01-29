#include <iostream>
#include <fstream>
#include <sstream>

//Local includes
#include "globals.h"
#include "cpuSample.h"

using namespace perfdata;

using std::string;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::stringstream;
  
string cpuSample::prop_names[]={"User","nice","system","idle","iowait","irq","softirq","steal","user_rt","system_rt"};
int cpuSample::prop_count=CPU_PROP_COUNT;

cpuSample::cpuSample(std::ifstream &fs,string name){  

  //  cout << "Getting " << CPU_PROP_COUNT<< " rows of cpu data " << endl;
  cpu_name=name;
  //  cout << "Cpu: " << name << " ";
  for(int i=0;i<prop_count;i++){
    fs >> props[i];
    //cout << prop_names[i] << ": " << props[i] << " ";
  }
  //cout << endl;
  getline(fs,rest);
}

string cpuSample::toTabsep(string sep){
  stringstream sstr;
  for(int i=0;i<prop_count;i++){
    sstr << props[i] << sep;
  }
  return sstr.str();
}

string cpuSample::titles(string sep){
  stringstream sstr;
  for(int i=0;i<prop_count;i++){
    sstr << cpu_name << '.' << prop_names[i] << sep;
  }
  return sstr.str();
}
