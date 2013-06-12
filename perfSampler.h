//Sample rate, in seconds

#include "cpuSample2.h"

namespace perfdata{

  class sample{  
    cpuSample cpu;
    memDataPoint mem;
    
    int sampleInterval;
    
    //Aggregated/computed data points
    int x;
    float y1; //CPU
    float y2; //Mem OR y1_ERROR, for multisample

  public:
    sample(int interval=1):cpu(),mem(){
      x=time(0);
      sleep(interval);
      y=cpuSample::pctUsed(cpu,cpuSample());
    }
  
    friend ostream& operator<<(&ostream s,singleSample s);
  
  };
  
  static string sep="\t";

  ostream& operator<<(&ostream s,singleSample s){
    s << x << sep << y1 << y2;
    return s;
  };

  
  class perfsampler{    
    
  public:
    perfsampler();        
    
  }
}
