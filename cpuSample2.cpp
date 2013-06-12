#include <sstream>

#include "cpuSample2.h"

using namespace std;

string cpuSample::prop_names[CPU_PROP_COUNT]={"User","nice","system","idle","iowait","irq","softirq","steal","user_rt","system_rt"};

float cpuSample::pctUsed(cpuSample& s1, cpuSample& s2){
  unsigned long workDone(0);
  unsigned long jiffiesPassed(0);

  workDone=s2.sumWorkJiffies()-s1.sumWorkJiffies();
  jiffiesPassed=s2.sumTotalJiffies()-s1.sumTotalJiffies();
  return (double(workDone)/(double)jiffiesPassed)*100;

}

cpuSample::cpuSample(){
    
  f.open("/proc/stat");
  //perfdata::cpuSample currentSample("totalCpu");
  //cout << currentSample.toTabsep() << endl;
  string rest,name;
  f>>name;
  for(int i=0;i<CPU_PROP_COUNT;i++){
    f >> props[i];
    //cout << prop_names[i] << ": " << props[i] << " ";
  }

  getline(f,rest);
    

  f.close();
  //sleep(1);
}
  
cpuSample& cpuSample::operator=(cpuSample& s){
  cpu_name=s.cpu_name;
  for(int i=0;i<CPU_PROP_COUNT;i++)
    props[i]=s.props[i];
  return *this;
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
  return props[perfdata::USER]+props[perfdata::NICE]+props[perfdata::SYSTEM];
}
  
string cpuSample::titles(string sep){
  stringstream sstr;
  for(int i=0;i<CPU_PROP_COUNT;i++){
    sstr << cpu_name << '.' << prop_names[i] << sep;
  }
  return sstr.str();
}
