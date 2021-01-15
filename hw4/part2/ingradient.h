#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

class Ingradient {
public:
  Ingradient(const string& name, int quantity);
  const string& getIngrName() const;
  int getIngrQnty() const;
  void addIngrQnty(int quantity);
  void minusIngrQnty(int quantity);

private:
  string ingr_name_;
  int ingr_qnty_;
};

bool less_ingradient(const Ingradient& left, const Ingradient& right);