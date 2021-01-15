#ifndef KITCHEN_H_
#define KITCHEN_H_
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <cmath>
#include <algorithm>
#include "ingradient.h"
using namespace std;

class Kitchen {
public:
  void addIngradient(const string& name, int quantity);
  void minusIngradient(const string& name, int quantity);
  const list<Ingradient>& getIngrList() const;
  ostream& printIngradients(ostream &ostr);
  void checkZero();

private:
  list<Ingradient> ingradient_list_;
};
#endif