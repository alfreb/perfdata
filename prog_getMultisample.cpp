#include <iostream>
#include <stdlib.h>

#include "scalingSample.h";

using namespace std;
using namespace perfdata;

int main(int argc, char** argv)
{

  if(argc<4){    
    cout << "Usage: executable <vmCount> <samples> <interval> [-header]"
	 << endl;
    return 0;
  }
  
  bool printHeader(false);
  if(argc>4)
    printHeader=true;
      

  int vmCount=atoi(argv[1]);
  int multiSamples=atoi(argv[2]);
  int interval=atoi(argv[3]);
  if(printHeader)
    cout << "vmCount: " << vmCount << endl
	 << "samples: " << multiSamples << endl
	 << "Interval: " << interval << endl;
		   

  scalingSample s(vmCount,interval,false);
  s.multiSampleCpu(multiSamples);
  cout << s << endl;
  
}
