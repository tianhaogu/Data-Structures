#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <cmath>
using namespace std;

class Fighters {
public:
  Fighters(const string &name);
  const string& getName() const;
  void storeInfo(const string& move_name, int move_frame);
  int getFrameInMove(const string &move_name) const;
  const string& getFrameName(int index) const;

private:
  string name_;
  map<string, int> individual_moveinfo_;
};