#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <cmath>
#include <algorithm>
#include "recipe.h"
#include "kitchen.h"
using namespace std;

void readRecipe(std::istream &istr, std::ostream &ostr, std::list<Recipe> &recipes);
void addIngradients(std::istream &istr, std::ostream &ostr, Kitchen &kitchen);
void printRecipe(std::istream &istr, std::ostream &ostr, std::list<Recipe> &recipes);
void makeRecipe(std::istream &istr, std::ostream &ostr, std::list<Recipe> &recipes, Kitchen &kitchen);

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " in-file out-file\n";
    return 1;
  }
  std::ifstream istr(argv[1]);
  if (!istr) {
    std::cerr << "Could not open " << argv[1] << " to read\n";
    return 1;
  }
  std::ofstream ostr(argv[2]);
  if (!ostr) {
    std::cerr << "Could not open " << argv[2] << " to write\n";
    return 1;
  }
  Kitchen kitchen;
  std::list<Recipe> recipes;
  char c;
  int count = 0;
  while (istr >> c) {
    if (c == 'r') {
      readRecipe(istr,ostr,recipes);
    }
    else if (c == 'a') {
      addIngradients(istr,ostr,kitchen);
    }
    else if (c == 'p') {
      printRecipe(istr,ostr,recipes);
    }
    else if (c == 'm') {
      makeRecipe(istr,ostr,recipes,kitchen);
    }
    else if (c == 'k') {
      count += 1;
      kitchen.printIngradients(ostr);
    }
    else {
      std::cerr << "unknown character: " << c << std::endl;
      exit(0);
    }
  }  
}

void readRecipe(std::istream &istr, std::ostream &ostr, std::list<Recipe> &recipes) {
  int units;
  std::string name, name2;  
  istr >> name;
  Recipe r(name);
  bool check_made = true;
  //loop over the recipe list to see if the recipe name already exists. If so, jump to the next
  for (list<Recipe>::iterator i = recipes.begin(); i != recipes.end(); i++) {
    if ((*i).getRcpName() == name) {
      ostr << "Recipe for " << name << " already exists" << endl;
      check_made = false;
    }
  }
  while (1) {
    istr >> units;
    if (units == 0) break;
    assert (units > 0);
    istr >> name2;
    if (check_made == true) {
      r.addIngradient(name2,units); //add ingradient name and corresponding quantity to the class
    }
  }
  if (check_made == true) { //append the recipe to the recipe list
    recipes.push_back(r);
    ostr << "Recipe for " << name << " added" << std::endl;
  }
}

void addIngradients(std::istream &istr, std::ostream &ostr, Kitchen &kitchen) {
  int units;
  std::string name;
  int count = 0;
  while (1) {
    istr >> units;
    if (units == 0) break;
    assert (units > 0);
    istr >> name;
    kitchen.addIngradient(name,units); //append ingradient class to the ingradient list in the kitchen class
    count++;
  }
  if (count == 1) {
    ostr << count << " ingredient added to kitchen" << std::endl;
  }
  else {
    ostr << count << " ingredients added to kitchen" << std::endl;
  }
}

void printRecipe(std::istream &istr, std::ostream &ostr, std::list<Recipe> &recipes) {
  std::string name;
  istr >> name;
  //loop over the recipe list to find the name, and print corresponding information
  for (list<Recipe>::iterator i = recipes.begin(); i != recipes.end(); i++) {
    if ((*i).getRcpName() == name) {
      (*i).printMix(ostr, name);
      return;
    }
  }
  ostr << "No recipe for " << name << endl; //print it if not found the recipe
}

void makeRecipe(std::istream &istr, std::ostream &ostr, std::list<Recipe> &recipes, Kitchen &kitchen) {
  std::string name;
  istr >> name;
  //loop over the recipe list to find the name, make the recipe, minus ingradient in the kitchen and check
  //if there exists zero quantity ingradient, if so, erase from the list 
  for (list<Recipe>::iterator i = recipes.begin(); i != recipes.end(); i++) {
    if ((*i).getRcpName() == name) {
      (*i).printMade(ostr, name, kitchen);
      kitchen.checkZero();
      return;
    }
  }
  ostr << "Don't know how to make " << name << endl;
}
