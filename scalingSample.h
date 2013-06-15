#ifndef SAMPLE_H
#define SAMPLE_H

#include "cpuSample2.h"
#include "memDataPoint.h"
#include <iostream>

namespace perfdata{

//class sample;
//std::ostream& operator<<(std::ostream& out,sample& s);

class scalingSample
{


    static std::string header;
    static std::string header_err;
    static std::string sep;

    cpuSample cpu;
    memDataPoint mem;

    int sampleInterval;
    int leadTime;


    //Aggregated/computed data points
    //Right now, Only these are maintained over operator= or cpyConstruct.
    int vm_count;
    float cpu_pct; //CPU or Memory
    float cpu_error; //Mem OR y1_ERROR, for multisample
    float mem_pct;
    float mem_error;

public:

    void multiSampleCpu(int samples=5);
    void multiSampleMem(int samples=5);

    scalingSample(int _vm_count, int interval=2);
    scalingSample(const scalingSample& s);

    scalingSample& operator=(const scalingSample& s);


    int getVmCount();
    float getCpuPct();
    float getCpuError();
    float getMemPct();
    float getMemError();

    static std::string colSep();

    friend std::ostream& operator<<(std::ostream&,scalingSample&);
};

std::ostream& operator<<(std::ostream&,scalingSample&);

}
#endif // SAMPLE_H



