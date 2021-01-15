#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <cmath>
#include <algorithm>
#include "ingradient.h"
using namespace std;

Ingradient::Ingradient(const string& name, int quantity) { //constructor
  ingr_name_ = name;
  ingr_qnty_ = quantity;
}

const string& Ingradient::getIngrName() const { //get the ingradient name
  return ingr_name_;
}

int Ingradient::getIngrQnty() const { //get the ingradient quantity in the kitchen
  return ingr_qnty_;
}

void Ingradient::addIngrQnty(int quantity) { //add the quantity of the ingradient in the kitchen
  ingr_qnty_ += quantity;
}

void Ingradient::minusIngrQnty(int quantity) { //minus the quantity of the ingradient in the kitchen after making recipe
  ingr_qnty_ -= quantity;
}

bool less_ingradient(const Ingradient& left, const Ingradient& right) { //for sorting according to quantity and then alphabetically
  return (left.getIngrQnty() < right.getIngrQnty() ||
  	     (left.getIngrQnty() == right.getIngrQnty() && left.getIngrName() < right.getIngrName()));
}