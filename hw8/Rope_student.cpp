#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <cassert>
#include <vector>
#include <string>
#include "Rope.h"
using namespace std;

//Since it's in order traversal, I directly use the lecture code
rope_iterator& rope_iterator::operator++() {
  if (ptr_-> right != NULL) {
  	ptr_ = ptr_-> right;
  	while (ptr_-> left != NULL) {
  	  ptr_ = ptr_-> left;
  	}
  }
  else {
  	while (ptr_-> parent != NULL && ptr_-> parent-> right == ptr_) {
  	  ptr_ = ptr_-> parent;
  	}
  	ptr_ = ptr_-> parent;
  }
  return *this;
}

//Since it's in order traversal, I directly use the lecture code
rope_iterator Rope::begin() const {
  if (root == NULL) {
  	return rope_iterator(NULL);
  }
  Node* tmp = root;
  while (tmp-> left != NULL) {
  	tmp = tmp-> left;
  }
  return rope_iterator(tmp);
}

Rope::Rope() { //default constructor, set private to initial status
  root = NULL;
  size_ = 0;
}

Rope::Rope(Node* p) { //constructor according to existing tree
  root = p; //set the root
  Node* tmp = p;
  if (tmp-> right == NULL) { //only left child, size is its weight
  	size_ = tmp-> weight;
  }
  else { //with right child
  	size_ = tmp-> weight;
  	while (tmp-> right != NULL) { //add all the weight of right children
  	  tmp = tmp-> right;
      size_ += tmp-> weight;
  	}
  }
}

Rope::~Rope() { //destructor
  this-> destroy_rope(root);
  root = NULL;
  size_ = 0;
}

Rope::Rope(const Rope& r) { //copy constructor
  root = this-> copy_rope(r.root, NULL);
  size_ = r.size();
}

Rope& Rope::operator= (const Rope& r) { //assignment operator
  if (&r != this) {
  	this-> destroy_rope(root);
  	root = this-> copy_rope(r.root, NULL);
  	size_ = r.size();
  }
  return *this;
}

bool Rope::index(int i, char& c) const {
  if (i < 0 || i >= size_) { //invalid index
	  return false;
  }
  Node* tmp = root;
  int new_index = i; //record targeted index
  while (is_leaf(tmp) == false) {
  	if (new_index < tmp-> weight) {
  	  tmp = tmp-> left; //if index smaller than weight, just go left
  	}
  	else {
  	  new_index -= tmp-> weight;
  	  tmp = tmp-> right; //if index larger than weight, go right and minus index from weight
  	}
  }
  if (new_index >= tmp-> weight) {
  	return false;
  }
  else { //get the char of the index
  	c = (tmp-> value)[new_index];
    return true;
  }
}

void Rope::concat(Rope& r) {
  Node* right_root = copy_rope(r.root, NULL); //copy the right tree
  Node* new_root = new Node; //new root after concatenation
  new_root-> left = root; //make connections between old roots and the new root
  new_root-> left-> parent = new_root;
  new_root-> right = right_root;
  right_root-> parent = new_root;
  root = new_root; //reset root of the class object
  Node* tmp1 = root-> left;
  root-> weight = tmp1-> weight;
  while (tmp1-> right != NULL) { //calculate weight of the root
    tmp1 = tmp1-> right;
    root-> weight += tmp1-> weight;
  }
  Node* tmp2 = root-> right;
  size_ = (root-> weight) + (tmp2-> weight); //calculate size of the tree
  while (tmp2-> right != NULL) {
  	tmp2 = tmp2-> right;
  	size_ += tmp2-> weight;
  }
}

bool Rope::report(int i, int j, std::string& s) const {
  if (i < 0 || j >= size_ || j < i) { //deal with invalid case
    return false;
  }
  int begin_index = i; //record left index
  while (begin_index <= j) {
    Node* tmp = root;
    int new_index = begin_index; //record index of first char of each leaf node (in i~j range)
    while (is_leaf(tmp) == false) { //find the targeted leaf node
      if (new_index < tmp-> weight) {
        tmp = tmp-> left;
      }
      else {
        new_index -= tmp-> weight; //reduce index to that of first char
        tmp = tmp-> right;
      }
    }
    if ((j-begin_index+1) >= tmp-> weight) { //if number of remaining chars is greater than the string length
      for (int m = new_index; m < tmp-> weight; ++m) {
        if (begin_index == i) { //if string passed in is empty
          s = (tmp-> value)[m];
        }
        else { //otherwise add char to the passed in string
          s += (tmp-> value)[m];
        }
        begin_index += 1; //add index for next char
      }
    }
    else { //if we cannot print the whole string of this leaf node
      int keep_begin_index = begin_index;
      for (int n = new_index; n < (j-keep_begin_index+1+new_index); ++n) { //same thing as above
        if (begin_index == i) {
          s = (tmp-> value)[n];
        }
        else {
          s += (tmp-> value)[n];
        }
        begin_index += 1;
      }
    }
  }
  return true;
}

Rope& Rope::split(int i, Rope& rhs) {
  if (i <= 0 || i >= size_) { //deal with invalid spit
    return *this;
  }
  Node* new_start;
  //check if it's first char of leaf, and set new_start to the targeted leaf
  int leaf_index = this-> checkFirst(i, new_start);
  vector<Node*> path_vec; //one vector for storing node pointers pointing to nodes we go back to the root
  vector<Node*> cut_vec; //the other: nodes we have to disconnect with parent
  if (leaf_index != 0) { //if not the first char of leaf
    new_start-> left = new Node; //generate left leaf
    new_start-> left-> parent = new_start;
    new_start-> left-> weight = leaf_index;
    new_start-> left-> value = (new_start-> value).substr(0, leaf_index);
    new_start-> right = new Node; //generate right leaf
    new_start-> right-> parent = new_start;
    new_start-> right-> weight = new_start-> weight - leaf_index;
    new_start-> right-> value = (new_start-> value).substr(leaf_index, new_start-> weight - leaf_index);
    new_start-> weight = leaf_index;
    new_start = new_start-> right; //make right leaf the target node
  }
  //if target node is left leaf, set target up to the parent that is a right child
  if (new_start-> parent-> left == new_start) {
    while (new_start-> parent-> right != new_start) {
      new_start = new_start-> parent;
    }
  }
  splitHelper(rhs, new_start, path_vec, cut_vec); //call the real split function
  //update weight of weights of all nodes in the path vector
  for (unsigned int k = 0; k < path_vec.size(); ++k) {
    Node* adjust_tmp = path_vec[k];
    if (adjust_tmp-> left != NULL) {
      adjust_tmp-> weight = adjust_tmp-> left-> weight;
      Node* adjust_tmp0 = adjust_tmp-> left;
      while (adjust_tmp0-> right != NULL) { //add weights of all right children
        adjust_tmp0 = adjust_tmp0-> right;
        adjust_tmp-> weight += adjust_tmp0-> weight;
      }
    }
    else {
      adjust_tmp-> weight = 0;
    }
  }
  this-> size_ = this-> getSize(this-> root); //reset size of left tree
  return *this;
}

int Rope::checkFirst(int i, Node* &new_start) const {
  Node* tmp = root;
  int new_index = i;
  while (is_leaf(tmp) == false) {
    if (new_index < tmp-> weight) { //if index smaller than weight, just go left
      tmp = tmp-> left;
    }
    else { //if index larger than weight, go right and minus index from weight
      new_index -= tmp-> weight;
      tmp = tmp-> right;
    }
  }
  new_start = tmp; //now reset target node
  return new_index;
}

int Rope::getSize(Node* p) const {
  int new_size = 0;
  Node* temp = p;
  if (temp-> right == NULL) { //if root has no right child, weight is its size
    new_size = temp-> weight;
  }
  else {
    new_size = temp-> weight;
    while (temp-> right != NULL) { //other add weights of right children to its size
      temp = temp-> right;
      new_size += temp-> weight;
    }
  }
  return new_size;
}

void Rope::splitHelper(Rope& rhs, Node* &new_start, vector<Node*> &path_vec, vector<Node*> &cut_vec) {
  Node* tmp = new_start-> parent;
  cut_vec.push_back(new_start); //the target node is the first we need to disconnect with parent
  while (tmp != NULL) { //go back to the root from targeted leaf
    int path_size = path_vec.size(); //store all nodes pointers on the path back
    if (path_size != 0) {
      if (tmp-> right != NULL && tmp-> right != path_vec[path_size-1]) {
        cut_vec.push_back(tmp-> right); //if the right child is not on the path, store the right to the cut vector
      }
    }
    path_vec.push_back(tmp);
    tmp = tmp-> parent;
  }
  int cut_size = cut_vec.size();
  Node* cut_tmp = cut_vec[cut_size-1]; //begin from the last of the cut vector (from top to bottom)
  cut_tmp-> parent-> right = NULL; //disconnect with parent
  cut_tmp-> parent = NULL;
  if (cut_vec.size() >= 2) {
    for (int m = cut_size-2; m >= 0; --m) {
      Node* cut_tmp1 = cut_vec[m]; //the next element of the vector from the right
      cut_tmp1-> parent-> right = NULL;
      cut_tmp1-> parent = NULL;
      Node* right_root = new Node; //concatenate these two disconnected subtree to form the right tree
      right_root-> right = cut_tmp;
      cut_tmp-> parent = right_root;
      right_root-> left = cut_tmp1;
      cut_tmp1-> parent = right_root;
      right_root-> weight = cut_tmp1-> weight; //calculate weight of the root of right tree
      while (cut_tmp1-> right != NULL) {
        cut_tmp1 = cut_tmp1-> right;
        right_root-> weight += cut_tmp1-> weight;
      }
      cut_tmp = right_root;
    }
  }
  rhs.root = cut_tmp; //set root and size of right tree
  rhs.size_ = getSize(cut_tmp);
}

//similar to the lecture code
Node* Rope::copy_rope(Node* old_root, Node* the_parent) {
  if (old_root == NULL) { //deal with empty tree
  	return NULL;
  }
  Node *answer = new Node;
  answer-> weight = old_root-> weight;
  if (old_root-> left == NULL && old_root-> right == NULL) {
  	answer-> value = old_root-> value; //if leaf then copy the string
  }
  answer-> left = copy_rope(old_root-> left, answer);
  answer-> right = copy_rope(old_root-> right, answer);
  answer-> parent = the_parent;
  return answer;
}

void Rope::destroy_rope(Node* &p) { //similar to the lecture code
  if (p == NULL) { //empty tree
  	return;
  }
  destroy_rope(p-> left);
  destroy_rope(p-> right);
  delete p;
  p = NULL;
}