//Sample rate, in seconds

#include <iostream>
#include <vector>
#include <math.h>

#include "perfSampler.h"
#include "cpuSample2.h"
#include "memDataPoint.h"
#include "sample.h"


using namespace perfdata;
using namespace std;

perfsampler::perfsampler(microManager *_manager, bool log):
    logfile("./perftotals.log"),manager(_manager)
{
    if(log){
        outFile.open(logfile.c_str());
        out=&outFile;
    }else
        out=&cout;
}

int perfsampler::numberOfSamples(){
    return cpuSamples.size();
}

void perfsampler::printSamples(ostream* openStream){
    vector<sample>::iterator it;
    for(it=cpuSamples.begin();it!=cpuSamples.end();++it){
        *openStream << *it << endl;
    }
}

perfsampler::~perfsampler()
{
    outFile.close();
}

void perfsampler::run(){
    sample s(manager?manager->getVmsBooted():-1);
    s.multiSampleCpu();
    cpuSamples.push_back(s);
    *out << s << endl;

    emit samplingDone();
    /*if(logstream.good())
            logstream << s << endl;*/
}


/*
int main(){
    perfsampler s(true);
    s.startSampling();
}*/
