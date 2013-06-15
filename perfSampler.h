//Sample rate, in seconds

#include "cpuSample2.h"

#include <fstream>
#include <iostream>
#include <QObject>
#include <QThread>
#include <vector>

#include "sample.h"
#include "outstream.h"

namespace perfdata{

class perfsampler : public QThread{

    Q_OBJECT

    std::vector<sample> cpuSamples;
    std::vector<sample> memSamples;
    std::vector<sample> qosSamples;

    std::ofstream outFile;
    std::ostream* out;

    int sampleRate;
    std::string logfile;

protected:
    //Call with start
    virtual void run();

public:
    perfsampler(bool log=false);
    ~perfsampler();
    int numberOfSamples();
    void printSamples(std::ostream* openStream);


signals:
    void samplingDone();

public slots:


  };

}
