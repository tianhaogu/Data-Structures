#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
  /*list<int> mylist;
  mylist.push_back(3);
  mylist.push_back(0);
  mylist.push_back(7);
  mylist.push_back(5);
  mylist.push_back(4);
  mylist.push_back(0);
  mylist.push_back(16);
  mylist.push_back(19);
  for (list<int>::iterator i = mylist.begin(); i != mylist.end(); i++) {
    if (*i == 0) {
      i = mylist.erase(i);
      i--;
    }
  }
  for (list<int>::iterator i = mylist.begin(); i != mylist.end(); i++) {
    cout << *i << endl;
  }*/
  std::list<int> mylist;
  for (int i=1; i<=8; ++i) mylist.push_back(i);

  std::cout << "mylist backwards:";
  for (std::list<int>::reverse_iterator rit=mylist.rbegin(); rit!=mylist.rend(); ++rit) {
    if (*rit == 0) {
      rit = mylist.erase(rit);
      rit++;
    }
  }
  for (std::list<int>::reverse_iterator rit=mylist.rbegin(); rit!=mylist.rend(); ++rit) {
    cout << *rit << endl;
  }
  std::cout << '\n';
  return 0;
}