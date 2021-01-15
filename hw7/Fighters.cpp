#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include "Fighters.h"
using namespace std;

Fighters::Fighters(const string &name) {
  name_ = name;
}

const string& Fighters::getName() const {
  return name_;
}

//insert the pair of move name and frame into the map
void Fighters::storeInfo(const string& move_name, int move_frame) {
  individual_moveinfo_.insert(make_pair(move_name, move_frame));
}

int Fighters::getFrameInMove(const string &move_name) const {
  map<string, int>::const_iterator itr = individual_moveinfo_.find(move_name);
  if (itr == individual_moveinfo_.end()) { //if the move name does not exist in the key of the map
  	return -1;
  }
  else {
    int frame_in_move = itr-> second; //get the value(frame) of the move
    return frame_in_move;
  }
}

//get the name of the key (move name) according to index
const string& Fighters::getFrameName(int index) const {
  map<string, int>::const_iterator itr = individual_moveinfo_.begin();
  if (index != 0) {
  	for (int i = 0; i < index; ++i) {
  	  itr++;
  	}
  }
  //string frame_name0 = itr-> first;
  return itr-> first;
}