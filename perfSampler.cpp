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

perfsampler::perfsampler(bool log):
    logfile("./perftotals.log")
{
    if(log){
        outFile.open(logfile.c_str());
        out=&outFile;
    }else
        out=&cout;
}

perfsampler::~perfsampler()
{
    outFile.close();
}

void perfsampler::run(){
    sample s;
    s.multiSampleCpu();
    cpuSamples.push_back(s);
    *out << s << endl;

    /*if(logstream.good())
            logstream << s << endl;*/
}


/*
int main(){
    perfsampler s(true);
    s.startSampling();
}*/
