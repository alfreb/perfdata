#ifndef PERFSAMPLER_H
#define PERFSAMPLER_H
//Sample rate, in seconds

#include "cpuSample2.h"

#include <fstream>
#include <iostream>
#include <QObject>

#include <QThread>
#include <vector>

#include "scalingSample.h"
#include "outstream.h"

//Probably circular.
#include "micromanager.h"
class microManager;

namespace perfdata{

class perfsampler : public QThread{

    Q_OBJECT

    std::vector<scalingSample> samples;

    std::string logfile;
    std::ofstream logstream;

    std::ostream* out;

    int sampleRate;
    int sampleSize;

    int multiSampleRate;
    int multiSampleSize;

    bool dumpSeparately;

    microManager* manager;

protected:
    //Call with start
    virtual void run();

public:
    perfsampler(microManager* _manager=0, int _multiSampleRate=1,int _multiSampleSize=10,bool log=false, int _sampleRate=1, int _sampleSize=1, bool _dumpSeparately=0);

    /*
    perfsampler(const perfsampler& p);
    perfsampler& operator=(const perfsampler& p);
    */

    ~perfsampler();
    int numberOfSamples();
    void printSamples(std::ostream* openStream);

    void dumpData_separateFiles(std::string description); //Required by "plot" for mac


    float lastRecordedCpuUsage();
    float lastRecordedMemUsage();

signals:
    void samplingDone();

public slots:


  };

}

#endif
