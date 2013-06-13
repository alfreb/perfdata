#include <sstream>
#include <iostream>
#include <exception>
//Local includes
#include "memDataPoint.h"

using namespace perfdata;
using namespace std;

//Statics
const int memDataPoint::prop_count=7;
const std::string memDataPoint::prop_names[prop_count]=
  {"MemTotal","MemFree","Buffers","Cached","SwapCached",
   "Active","Inactive"};

memDataPoint::memDataPoint()
    //:props{&memTotal,&memFree,&buffers,&cached,
   // &swapCached,&active,&inactive}
{

  //Linking introspection - if C++11 initialization NOT OK
  /*
    for(int i=0; i<sizeof(props)/sizeof(props[0]); i++){
    *props[i]=0;
    }
  */
  string line,key;
  long value;
  meminfo.open("/proc/meminfo");
  while(meminfo.good()){
    meminfo >> key;
    meminfo >> value;
    propMap[key]=value;      
    getline(meminfo,line);
  }
  meminfo.close();
  //  cout << toTabsep() << endl;
};

string memDataPoint::titles(string sep){
  if(propMap.empty())
    throw "No headers yet";
  
  stringstream sstr;
  for(map<string, long>::iterator it = propMap.begin();
      it!=propMap.end(); it++)
    {
      sstr << it->first << sep; 
    }
  return sstr.str();  
  
}
string memDataPoint::toTabsep(std::string sep){
  stringstream sstr;
  //Print all values, separated by sep
  for(map<string, long>::iterator it = propMap.begin();
      it!=propMap.end(); it++)
    {
      sstr << it->second << sep; 
    }
  return sstr.str();  
}

float memDataPoint::pctUsed(){
  double total(propMap["MemTotal:"]);
  return (double(total-propMap["MemFree:"])/total)*100;
}

/*
std::string memDataPoint::toTabsep(std::string sep){
  stringstream sstr;
  for(int i=0; i<prop_count; i++){
    sstr << *props[i];
    if(i<(prop_count-1))
      sstr << sep;
    sstr << endl;
  }
  return sstr.str();
};
*/
