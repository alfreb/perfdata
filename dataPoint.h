#ifndef DATAPOINT_H
#define DATAPOINT_H

//Local includes
#include "dataPoint.h"


namespace perfdata{

  class dataPoint{   
    virtual std::string toTabsep(std::string sep="\t")=0;
  };
  
}//End namespace perfdata

#endif
