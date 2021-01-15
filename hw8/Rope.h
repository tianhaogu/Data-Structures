#ifndef _ROPE_H
#define _ROPE_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Node {
public:
  Node() : left(NULL), right(NULL), parent(NULL), weight(0) {}
  Node* left;
  Node* right;
  Node* parent;
  int weight;
  std::string value;
};

class Rope;

class rope_iterator {
public:
  rope_iterator();
  rope_iterator(Node* p);
  rope_iterator& operator++();
  rope_iterator operator++(int);
  int weight() const;
  const std::string& value() const;
  friend class Rope;
  bool operator!=(const rope_iterator& it2) const;
private:
  Node* ptr_;
};

class Rope {
public:
  Rope();
  ~Rope();
  Rope(Node* p);
  Rope(const Rope& r);
  Rope& operator= (const Rope& r);

  bool index(int i, char& c) const; //Get a single character
  void concat(Rope& r); //Add the other string to me
  bool report(int i, int j, std::string& s) const; //Substring
  Rope& split(int i, Rope& rhs); //Split the string at index i into this (LHS) and a new Rope rhs

  rope_iterator begin() const;
  rope_iterator end() const;

  int size() const;
  void print(std::ostream& out) const;
  void print_strings(std::ostream& out) const;
  Node* expose_root() const;

  int checkFirst(int i, Node* &new_start) const;
  int getSize(Node* p) const;
  void splitHelper(Rope& rhs, Node* &new_start, vector<Node*> &path_vec, vector<Node*> &cut_vec);
  Node* copy_rope(Node* old_root, Node* the_parent);
  void destroy_rope(Node* &p);
private:
  void print(std::ostream& out, Node* head, int depth) const;
private:
  int size_;
  Node *root;
};

bool is_leaf(Node* p);

#endif
