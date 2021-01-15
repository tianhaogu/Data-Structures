#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <cmath>
#include <algorithm>
#include "ingrneed.h"
using namespace std;

Ingrneed::Ingrneed(const string& ingrname, int quantity, const string& recipename) { //constructor
  ingrneed_name_ = ingrname;
  ingrneed_qnty_ = quantity;
  ingrrecipe_name_ = recipename;
}

const string& Ingrneed::getIngrneedName() const { //get the name of the ingradient necessary for making the recipe
  return ingrneed_name_;
}

const string& Ingrneed::getIngrrecpName() const { //get the name of the corresponding recipe
  return ingrrecipe_name_;
}

int Ingrneed::getIngrneedQnty() const { //get the quantity of the ingradient necessary for making the recipe
  return ingrneed_qnty_;
}

bool less_ingr_in_recipe(const Ingrneed& left, const Ingrneed& right) { //for sorting alphabetically
  return (left.getIngrneedName() < right.getIngrneedName());
}