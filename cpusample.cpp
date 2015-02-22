#include <iostream>
#include <fstream>
#include <sstream>

//Local includes
#include "cpusample.hpp"

using namespace perfdata;

using std::string;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::stringstream;
 
int cpuSample::prop_count=CPU_PROP_COUNT; 
string cpuSample::prop_names[CPU_PROP_COUNT]={"User","nice","system","idle","iowait","irq","softirq","steal","user_rt","system_rt"};


cpuSample& cpuSample::operator=(cpuSample& s){
  cpu_name=s.cpu_name;
  for(int i=0;i<CPU_PROP_COUNT;i++)
    props[i]=s.props[i];
  return *this;
}
cpuSample::cpuSample(string name,std::ifstream* fs_arg){  

  //  cout << "Getting " << CPU_PROP_COUNT<< " rows of cpu data " << endl;
  cpu_name=name;
  ifstream* fs;
  if(!fs_arg){
    fs=new ifstream;
    fs->open("/proc/stat");   
  }else{
    fs=fs_arg;
  }
  //  cout << "Cpu: " << name << " ";
  if(!fs->good())
    throw "File stream not good!";

  for(int i=0;i<prop_count;i++){
    *fs >> props[i];
    //cout << prop_names[i] << ": " << props[i] << " ";
  }
  //cout << endl;
  getline(*fs,rest);
  if(!fs_arg){
    cout << "Closing file" << endl;
    fs->close();
    delete fs;
  }
}

string cpuSample::toCsv(string sep){
  stringstream sstr;
  for(int i=0;i<prop_count;i++){
    sstr << props[i] << sep;
  }
  return sstr.str();
}

unsigned long cpuSample::sumTotalJiffies()
{
  unsigned long sum(0);
  for(int i=0;i<CPU_PROP_COUNT;i++)
    sum+=props[i];
  return sum;
}

unsigned long cpuSample::sumWorkJiffies()
{
  return props[USER]+props[NICE]+props[SYSTEM];
}

string cpuSample::titles(string sep){
  stringstream sstr;
  for(int i=0;i<prop_count;i++){
    sstr << cpu_name << '.' << prop_names[i] << sep;
  }
  return sstr.str();
}

