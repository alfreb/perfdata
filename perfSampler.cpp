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

perfsampler::perfsampler(microManager *_manager, int _multiSampleRate, int _multiSampleSize, bool log, int _sampleRate, int _sampleSize,bool _dumpSeparately):
    logfile("./perfsampler.log"),
    manager(_manager),multiSampleRate(_multiSampleRate),multiSampleSize(_multiSampleSize),sampleRate(_sampleRate),sampleSize(_sampleSize),dumpSeparately(_dumpSeparately)
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

/*
perfsampler::perfsampler(const perfsampler& p):
  logfile(p.logfile),
  manager(p.manager),sampleRate(p.sampleRate),sampleCount(p.sampleCount),out(p.out),logstream(p.logstream){}

perfsampler& perfsampler::operator=(const perfsampler& p)
{
  logfile=p.logfile;  
  manager=p.manager;
  sampleRate=p.sampleRate;
  sampleCount=p.sampleCount;
  out=p.out;
  logstream=p.logstream;
  return *this;
}
*/





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
        cpuStream << s->getVmCount() << scalingSample::colSep()
                  << s->getCpuPct() << scalingSample::colSep()
                  << s->getCpuError()
                  << endl;

        //Memory data
        memStream << s->getVmCount() << scalingSample::colSep()
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
    do{
      if(sampleSize>0)
	cout << "** Sample " << samples.size()+1 << " / "<< sampleSize+samples.size() << endl;
      scalingSample s(manager?manager->getVmsBooted():-1,multiSampleRate);
      s.multiSampleCpu(multiSampleSize);
      samples.push_back(s);
      *out << s << endl;   
      cout << endl;
    }while(sampleSize-- > 1);
        
    if(dumpSeparately){
        cout << "Logging to file, please write a line of comment: " << endl;
	string comment;
	getline(cin,comment);
	dumpData_separateFiles(comment);
    }

    cout << endl << endl << "** perfSampler thread had a great run. " << endl;
    emit samplingDone();
    /*if(logstream.good())
            logstream << s << endl;*/
}


/*
int main(){
    perfsampler s(true);
    s.startSampling();
}*/
