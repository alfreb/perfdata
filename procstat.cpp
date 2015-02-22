#include <iostream>
#include <map>

// Locals
#include "stat.hpp"

using namespace std;


int main(int argc, char** argv){
  
  bool titles{false};
  if(argc > 1)
    if(string(argv[1]) != "-H"){
      cout << "USAGE: " << argv[0] << " -H" << endl;
      cout << "\t" << "-H" << " : " << "Print CSV header first" << endl;
      return 0;
    }else{
      titles=true;
    }
  
  perfdata::Stat s;
  if(titles)
    cout << s.titles() << endl;
  cout << s.toCsv() << endl;

}
