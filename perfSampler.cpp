//Sample rate, in seconds

#include <iostream>
#include <vector>
#include <math.h>

#include "cpuSample2.h"
#include "memDataPoint.h"


namespace perfdata{
    
  class sample{  
    
    static std::string sep;
    static std::string header;
    static std::string header_err;

    cpuSample cpu;
    memDataPoint mem;
    
    int sampleInterval;
    
    //Aggregated/computed data points
    int x;
    float y1; //CPU
    float y2; //Mem OR y1_ERROR, for multisample

  public:
    sample(int interval=1):sampleInterval(interval){
      x=time(0);
      sleep(interval);
      cpuSample cpu1;
      y1=cpuSample::pctUsed(cpu,cpu1);
      std::cout << "initialSample: " << y1 << std::endl;      
      y2=mem.pctUsed();
      cpu=cpu1;
    }
    
    
    
    void multiSampleCpu(int samples=20){
      std::vector<float> cpuPcts;
      cpuPcts.push_back(y1);
      double sum(y1);
      std::cout << "Multisampling Cpu" << std::endl;
      for(int i=1;i<samples;i++){
	sleep(sampleInterval); //firstSample was just taken
	cpuSample cpu_new;
	float newPct=cpuSample::pctUsed(cpu,cpu_new);
	cpuPcts.push_back(newPct);
	sum+=newPct;
	cpu=cpu_new;
 
	//std::cout << "\rSample " << i+1 << " / " << samples << " => " << newPct;
	std::cout << newPct << sep;	
	std::cout.flush(); 

      }
      double sampleMean=sum/samples;
      double sumVariances(0);
      std::vector<float>::iterator it;      
      for(it=cpuPcts.begin(); it!=cpuPcts.end(); ++it)
	{
	  sumVariances+=pow(((*it)-sampleMean),2);	  
	}
      double sampleVariance=sumVariances/(samples-1);
      double stddev=sqrt(sampleVariance);
                 
      std::cout << std::endl 
		<< "Multisample sum: "<< sum 
		<< " Mean: " << sum/samples 
		<< " Variance: " << sampleVariance
		<< " Stddev: " << stddev
		<< std::endl;
      
      y2=stddev;
      
    }
  
    friend std::ostream& operator<<(std::ostream& out,sample& s);
  
  };

  using namespace std;

  string sample::sep="\t";
  string sample::header="Time"+sep+"Cpu_%"+sep+"Mem_%";


  ostream& operator<<(ostream& out,sample& s){
    out << s.x << sample::sep << s.y1 << sample::sep << s.y2;
    return out;
  };


  class perfsampler{
    ofstream logstream;
    int sampleRate;
    string logfile;
  public:
    perfsampler(bool log=false):
      logfile("./perftotals.log")
    {
      if(log)
	logstream.open(logfile.c_str());
    }
    
    ~perfsampler()
    {
      logstream.close();
    }
    
    void startSampling(){
      while(true){	
	sample s;
	s.multiSampleCpu();
	cout << s << endl;
	if(logstream.good())
	  logstream << s << endl;
      }
    };
  };
    
  

}//End namespace


using namespace perfdata;

int main(){
  perfsampler s(true);
  s.startSampling();
}
