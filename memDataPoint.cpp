#include <sstream>
#include <iostream>

//Local includes
#include "memDataPoint.h"

using namespace perfdata;
using namespace std;

//Statics
const int memDataPoint::prop_count=7;
const std::string memDataPoint::prop_names[prop_count]=
  {"MemTotal","MemFree","Buffers","Cached","SwapCached",
   "Active","Inactive"};

memDataPoint::memDataPoint():
  props({&memTotal,&memFree,&buffers,&cached,
	&swapCached,&active,&inactive})
{

  
  for(int i=0; i<sizeof(props)/sizeof(props[0]); i++){
    *props[i]=0;
  }
  
  
  cout << "Empty memDataPoint" << endl;
};

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
