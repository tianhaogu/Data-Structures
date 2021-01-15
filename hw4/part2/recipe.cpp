#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <cmath>
#include <algorithm>
#include "recipe.h"
using namespace std;

Recipe::Recipe(const string& name) { //constructor
  recipe_name_ = name;
}

const string& Recipe::getRcpName() const { //get the name of the recipe
  return recipe_name_;
}

//first create a class (ingrneed) for the ingradient necessary for making this recipe
//then append this class to the list(private member variable of the ingradient class)
void Recipe::addIngradient(const string& name, int quantity) {
  Ingrneed ignd(name, quantity, recipe_name_);
  need_ingr_.push_back(ignd);
}

ostream& Recipe::printMix(ostream &ostr, const string& name) {
  ostr << "To make " << name << ", mix together:" << endl;
  need_ingr_.sort(less_ingr_in_recipe);
  //loop over the ingradient need list to print the information for making the recipe
  for (list<Ingrneed>::iterator j = need_ingr_.begin(); j != need_ingr_.end(); j++) {
  	if ((*j).getIngrneedQnty() == 1) {
  	  ostr << "  " << (*j).getIngrneedQnty() << " unit of " << (*j).getIngrneedName() << endl;
  	}
  	else {
  	  ostr << "  " << (*j).getIngrneedQnty() << " units of " << (*j).getIngrneedName() << endl;
  	}
  }
  return ostr;
}

ostream& Recipe::printMade(ostream &ostr, const string& name, Kitchen& kitchen) {
  need_ingr_.sort(less_ingr_in_recipe);
  bool check_complete = true;
  int count_incomplete = 0;
  //loop over the ingradient need list
  for (list<Ingrneed>::iterator j = need_ingr_.begin(); j != need_ingr_.end(); j++) {
    bool check_exist = false;
    //loop over the ingradient list to find the ingradients matching the ingradients necessary for making the recipe
    for (list<Ingradient>::const_iterator k = (kitchen.getIngrList()).begin(); k != (kitchen.getIngrList()).end(); ++k) {
      if ((*k).getIngrName() == (*j).getIngrneedName()) {
        check_exist = true;
        //if existing quantity of the ingradient in the kitchen is less then quantity necessary for making the recipe
        if ((*k).getIngrQnty() < (*j).getIngrneedQnty()) {
          check_complete = false;
          if (count_incomplete == 0) { //check to see if it's the first insufficient ingradient
            ostr << "Cannot make " << name << ", need to buy:" << endl;
            count_incomplete += 1;
          }
          //print the insufficient quantity of the ingradient need
          if (((*j).getIngrneedQnty() - (*k).getIngrQnty()) == 1) {
            ostr << "  " << ((*j).getIngrneedQnty() - (*k).getIngrQnty()) << " unit of " << (*j).getIngrneedName() << endl;
          }
          else {
            ostr << "  " << ((*j).getIngrneedQnty() - (*k).getIngrQnty()) << " units of " << (*j).getIngrneedName() << endl;
          }
        }
      }
    }
    //if the ingradient necessary for making the recipe does not exist in the ingradient list in the kitchen
    if (check_exist == false) {
      if (count_incomplete == 0) {
        ostr << "Cannot make " << name << ", need to buy:" << endl;
        count_incomplete += 1;
      }
      if ((*j).getIngrneedQnty() == 1) { // print the total quantity
        ostr << "  " << (*j).getIngrneedQnty() << " unit of " << (*j).getIngrneedName() << endl;
      }
      else {
        ostr << "  " << (*j).getIngrneedQnty() << " units of " << (*j).getIngrneedName() << endl;
      }
      check_complete = false;
    }
  }
  if (check_complete == true) { //if all ingradients necessary for making the recipe exists and are sufficient
    ostr << "Made " << name << endl;
    //loop over the ingradient need list and then ingradient list to match the name and then minus corresponding quantity in the kitchen
    for (list<Ingrneed>::iterator j = need_ingr_.begin(); j != need_ingr_.end(); j++) { 
      for (list<Ingradient>::const_iterator k = (kitchen.getIngrList()).begin(); k !=(kitchen.getIngrList()).end(); k++) {
        if ((*j).getIngrneedName() == (*k).getIngrName()) {
          kitchen.minusIngradient((*k).getIngrName(), (*j).getIngrneedQnty());
        }
      }
    }
  }
  return ostr;
}