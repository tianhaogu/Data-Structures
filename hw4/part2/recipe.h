#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <cmath>
#include <algorithm>
//#include "ingradient.h"
#include "ingrneed.h"
#include "kitchen.h"
using namespace std;

class Recipe {
public:
  Recipe(const string& name);
  const string& getRcpName() const;
  void addIngradient(const string& name, int quantity);
  ostream& printMix(ostream &ostr, const string& name);
  ostream& printMade(ostream &ostr, const string& name, Kitchen& kitchen);

private:
  string recipe_name_;
  list<Ingrneed> need_ingr_;
};