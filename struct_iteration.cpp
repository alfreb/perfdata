

#include <iostream>
#include <string>

using namespace std;

struct person{
  string firstName;
  string lastName;
  
  int age;
  float height;
};

int main(){
  person p={"Alfred","Bratterud",32,1.84};
  string* s=&p.firstName;
  int* i=(int*)s+2;
  cout << *i << endl;
  
}


