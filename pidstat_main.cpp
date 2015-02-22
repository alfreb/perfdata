#include <unistd.h>

#include "pidstat.hpp"

using namespace std;

int main(int argc, char** argv){
  if(argc < 2){
    cout << "USAGE: " << argv[0] << " PID" << endl;
    return 0;
  }
  
  perfdata::Pidstat p(atoi(argv[1]));
  cout << p << endl;
  
}
