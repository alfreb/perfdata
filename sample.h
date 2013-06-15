#ifndef SAMPLE_H
#define SAMPLE_H

#include "cpuSample2.h"
#include "memDataPoint.h"
#include <iostream>

namespace perfdata{

//class sample;
//std::ostream& operator<<(std::ostream& out,sample& s);

class sample
{


    static std::string header;
    static std::string header_err;
    static std::string sep;

    cpuSample cpu;
    memDataPoint mem;

    int sampleInterval;


    //Aggregated/computed data points
    //Right now, Only these are maintained over operator= or cpyConstruct.
    int x;
    float y1; //CPU or Memory
    float y2; //Mem OR y1_ERROR, for multisample

public:

    void multiSampleCpu(int samples=5);
    void multiSampleMem(int samples=20);

    sample(int interval=1);
    sample(const sample& s);

    sample& operator=(const sample& s);


    int getX();
    float getY1();
    float getY2();

    friend std::ostream& operator<<(std::ostream&,sample&);
};

std::ostream& operator<<(std::ostream&,sample&);

}
#endif // SAMPLE_H



