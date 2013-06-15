#include <vector>
#include <math.h>

#include "scalingSample.h"

using namespace perfdata;
using namespace std;

string scalingSample::sep="\t";
string scalingSample::header="Time"+sep+"Cpu_%"+sep+"Mem_%";

string scalingSample::colSep(){
    return sep;
}

scalingSample::scalingSample(int _vm_count,int interval):
    sampleInterval(interval),vm_count(_vm_count),
    leadTime(interval<=2 ? 3: interval),
    cpu_error(-1),
    mem_error(0)
{
    if(vm_count<0)
        vm_count=time(0);
    cpu=cpuSample();
    sleep(leadTime); //Lead time
    cpuSample cpu1;
    cpu_pct=cpuSample::pctUsed(cpu,cpu1);
    std::cout << "initialSample: " << cpu_pct << std::endl;
    mem_pct=mem.pctUsed();
    cpu=cpu1;
}

scalingSample::scalingSample(const scalingSample &s)
    //:cpu(s.cpu),mem(s.mem), Requires copy constructor in cpu/mem
    :sampleInterval(s.sampleInterval),vm_count(s.vm_count),cpu_pct(s.cpu_pct),cpu_error(s.cpu_error),mem_pct(s.mem_pct),mem_error(s.mem_error)
{}

scalingSample& scalingSample::operator=(const scalingSample& s){
    //s.cpu; //Requires operator= in cpuSample
    //s.mem; //Requires operator= in memDataPoint
    sampleInterval=s.sampleInterval;
    vm_count=s.vm_count;
    cpu_pct=s.cpu_pct;
    cpu_error=s.cpu_error;
    mem_pct=s.mem_pct;
    mem_error=s.mem_error;
    return *this;
}

void scalingSample::multiSampleCpu(int samples){
    vector<float> cpuPcts;
    cpuPcts.push_back(cpu_pct);
    double sum(cpu_pct);
    cout << "Multisampling Cpu" << endl;
    for(int i=1;i<samples;i++){
        sleep(sampleInterval); //firstSample was just taken
        cpuSample cpu_new;
        float newPct=cpuSample::pctUsed(cpu,cpu_new);
        cpuPcts.push_back(newPct);
        sum+=newPct;
        cpu=cpu_new;

        //std::cout << "\rSample " << i+1 << " / " << samples << " => " << newPct;
        cout << newPct << sep;
        cout.flush();

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

    cpu_pct=sampleMean;
    cpu_error=stddev;

}

int scalingSample::getVmCount(){return vm_count;}
float scalingSample::getCpuPct(){return cpu_pct;}
float scalingSample::getCpuError(){return cpu_error;}
float scalingSample::getMemPct(){return mem_pct;}
float scalingSample::getMemError(){return mem_error;}

ostream& perfdata::operator<<(ostream& out,scalingSample& s){
    out << s.vm_count << scalingSample::sep
        << s.cpu_pct << scalingSample::sep
        << s.cpu_error << scalingSample::sep
        << s.mem_pct << scalingSample::sep
        << s.mem_error;
    return out;
};

