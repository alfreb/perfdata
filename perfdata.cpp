#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

//Globals
#include "globals.h"

//Classes
#include "cpuSample.h"
#include "cpuDataPoint.h"
#include "memDataPoint.h"

//#include "cpuSample.cpp"
//#include "cpuDataPoint.cpp"

using namespace std;
using namespace perfdata;


class perfCollector{  
  //cpuDataPoints cpu;
  //memDataPoints mem
public:
  void getData(bool=false);  
};
  
void perfCollector::getData(bool withTitles){
  cpuDataPoint cpuData;
  memDataPoint memData;
  if(withTitles)
    cout << cpuData.titles()
	 << memData.titles() << endl;
  
  cout << cpuData.toTabsep() 
       << memData.toTabsep() << endl;
};

int main(int argc,char** argv){
  bool withTitles=false;
  //  cout << "Getting performance data" << endl;
  if(argc>1){   
    if(string(argv[1])==string("-T")){
      //  cout << "With titles" << endl;
      withTitles=true;
    }else{
      //cout << "NO titles " << endl;
    }
  }
  perfCollector perf;
  perf.getData(withTitles);  
  //perf.getData();

}
