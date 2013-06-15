//Sample rate, in seconds

#include <iostream>
#include <vector>
#include <math.h>

#include "perfSampler.h"
#include "cpuSample2.h"
#include "memDataPoint.h"
#include "scalingSample.h"



using namespace perfdata;
using namespace std;

perfsampler::perfsampler(microManager *_manager,int _sampleRate, bool log):
    logfile("./perfsampler.log"),
    manager(_manager),sampleRate(_sampleRate)
{
    if(log){
        /*
        datastream_cpu.open(datafile_cpu.c_str());
        datastream_mem.open(datafile_mem.c_str());
        datastream_qos.open(logfile_qos.c_str());
        */
        logstream.open(logfile.c_str());
        out=&logstream;
    }else
        out=&cout;
}

int perfsampler::numberOfSamples(){
    return samples.size();
}

void perfsampler::printSamples(ostream* openStream){
    vector<scalingSample>::iterator it;
    for(it=samples.begin();it!=samples.end();++it){
        *openStream << *it << endl;
    }
}

void perfsampler::dumpData_separateFiles(string description){
    ofstream cpuStream;
    ofstream memStream;
    QString datestring=QDateTime::currentDateTime().toString(Qt::ISODate);
    QString cpuFilename="perfdata_cpu_"+datestring+".dat";
    QString memFilename="perfdata_mem_"+datestring+".dat";
    cpuStream.open(cpuFilename.toStdString().c_str());
    memStream.open(memFilename.toStdString().c_str());

    cpuStream << description << endl;
    memStream << description << endl;

    vector<scalingSample>::iterator it;
    scalingSample* s;
    for(it=samples.begin();it!=samples.end();++it){
        s=&(*it);

        //CPU Data
        cpuStream << s->getVmCount()
                  << s->getCpuPct()
                  << s->getCpuError()
                  << endl;

        //Memory data
        memStream << s->getVmCount()
                  << s->getMemPct()
                  //<< s->getMemError()>0?s->getMemError():""
                  << endl;
    }

}

perfsampler::~perfsampler()
{
    /*
    datastream_cpu.close();
    datastream_mem.close();
    datastream_qos.close();*/
    logstream.close();
}


float perfsampler::lastRecordedCpuUsage(){
    return (samples.at(samples.size()-1)).getCpuPct();
}

float perfsampler::lastRecordedMemUsage(){
    return (samples.at(samples.size()-1)).getMemPct();
}


void perfsampler::run(){
    scalingSample s(manager?manager->getVmsBooted():-1,sampleRate);
    s.multiSampleCpu();
    samples.push_back(s);
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
