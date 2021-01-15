#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <cmath>
#include <algorithm>
#include "kitchen.h"
using namespace std;

void Kitchen::addIngradient(const string& name, int quantity) {
  //loop over the ingradient list to find the name and add corresponding quantity
  for (list<Ingradient>::iterator i = ingradient_list_.begin(); i != ingradient_list_.end(); i++) {
  	if ((*i).getIngrName() == name) {
  	  (*i).addIngrQnty(quantity);
  	  return;
  	}
  }
  //if the ingradient first time appears, create a new class and then append to the list
  Ingradient ingr(name, quantity);
  ingradient_list_.push_back(ingr);
}

void Kitchen::minusIngradient(const string& name, int quantity) { //same technique as add ingradient
  for (list<Ingradient>::iterator m = ingradient_list_.begin(); m != ingradient_list_.end(); m++) {
  	if ((*m).getIngrName() == name) {
  	  (*m).minusIngrQnty(quantity);
  	}
  }
}

const list<Ingradient>& Kitchen::getIngrList() const { //return the ingradient list (private member variable) of the class
  return ingradient_list_;
}

ostream& Kitchen::printIngradients(ostream &ostr) {
  ingradient_list_.sort(less_ingradient);
  ostr << "In the kitchen:" << endl;
  //loop over the ingradient list to print existing units of each ingradient
  for (list<Ingradient>::iterator i = ingradient_list_.begin(); i != ingradient_list_.end(); i++) {
  	if ((*i).getIngrQnty() == 1) {
  	  ostr << "  " << (*i).getIngrQnty() << " unit of " << (*i).getIngrName() << endl;
  	}
  	else {
  	  ostr << "  " << (*i).getIngrQnty() << " units of " << (*i).getIngrName() << endl;
  	}
  }
  return ostr;
}

//if the ingradient has zero quantity after making the recipe, erase it from the ingradient list
void Kitchen::checkZero() {
  for (list<Ingradient>::iterator n = ingradient_list_.begin(); n != ingradient_list_.end(); n++) {
    if ((*n).getIngrQnty() == 0) {
      n = ingradient_list_.erase(n);
      --n;
    }
  }
}