//Sample rate, in seconds

#include "cpuSample2.h"

#include <fstream>
#include <iostream>
#include <QObject>
#include <QThread>
#include <vector>

#include "scalingSample.h"
#include "outstream.h"
#include "micromanager.h"

namespace perfdata{

class perfsampler : public QThread{

    Q_OBJECT

    std::vector<scalingSample> samples;

    std::string logfile;
    std::ofstream logstream;

    std::ostream* out;

    int sampleRate;
    int sampleCount;

    microManager* manager;

protected:
    //Call with start
    virtual void run();

public:
    perfsampler(microManager* _manager=0,int _sampleRate=1,int _sampleCount=10,bool log=false);
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
