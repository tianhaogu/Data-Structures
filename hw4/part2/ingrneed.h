#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

class Ingrneed {
public:
  Ingrneed(const string& ingrname, int quantity, const string& recipename);
  const string& getIngrneedName() const;
  const string& getIngrrecpName() const;
  int getIngrneedQnty() const;

private:
  string ingrneed_name_;
  int ingrneed_qnty_;
  string ingrrecipe_name_;
};

bool less_ingr_in_recipe(const Ingrneed& left, const Ingrneed& right);