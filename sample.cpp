#include <vector>
#include <math.h>

#include "sample.h"

using namespace perfdata;
using namespace std;

string sample::sep="\t";
string sample::header="Time"+sep+"Cpu_%"+sep+"Mem_%";


sample::sample(int interval):sampleInterval(interval){
    x=time(0);
    sleep(interval);
    cpuSample cpu1;
    y1=cpuSample::pctUsed(cpu,cpu1);
    std::cout << "initialSample: " << y1 << std::endl;
    y2=mem.pctUsed();
    cpu=cpu1;
}

sample::sample(const sample &s)
    //:cpu(s.cpu),mem(s.mem), Requires copy constructor in cpu/mem
    :sampleInterval(s.sampleInterval),x(s.x),y1(s.y1),y2(s.y2)
{}

sample& sample::operator=(const sample& s){
    //s.cpu; //Requires operator= in cpuSample
    //s.mem; //Requires operator= in memDataPoint
    sampleInterval=s.sampleInterval;
    x=s.x;
    y1=s.y1;
    y2=s.y2;
    return *this;
}

void sample::multiSampleCpu(int samples){
    vector<float> cpuPcts;
    cpuPcts.push_back(y1);
    double sum(y1);
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

    y2=stddev;

}

int sample::getX(){return x;}
float sample::getY1(){return y1;}
float sample::getY2(){return y2;}

ostream& perfdata::operator<<(ostream& out,sample& s){
    out << s.x << sample::sep << s.getY1() << sample::sep << s.getY2();
    return out;
};

