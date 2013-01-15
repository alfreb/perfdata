// regex_iterator constructor
#include <iostream>
#include <string>
#include <regex>

int main ()
{
  std::string s ("this subject has a submarine as a subsequence");
  std::regex e ("\\b(sub)([^ ]*)");   // matches words beginning by "sub"

  std::regex_iterator<std::string::iterator> rit ( s.begin(), s.end(), e );
  std::regex_iterator<std::string::iterator> rend;

  while (rit!=rend) {
    std::cout << rit->str() << std::endl;
    ++rit;
  }

  return 0;
}
