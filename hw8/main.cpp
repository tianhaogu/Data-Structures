#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include "Rope.h"
using namespace std;

void StudentTests();
bool SAME(const Rope& r, const std::string& s);
bool ValidRope(Node* root);
int countWeights(Node* root);
void BasicTests();
Node* IndexTestRope();
Node* ConcatTestRopeLeft();
Node* ConcatTestRopeRight();
Node* StudentConcatLeft();
Node* StudentConcatRight();
Node* StudentTestRope();

int main(){
  BasicTests();
  std::cout << "***Basic tests passed." << std::endl;
  StudentTests();
  std::cout << "***Student tests passed." << std::endl;
  return 0;
}

void StudentTests() {
  //same tree as basic test but using different index for split (left leaf)
  Rope r4(IndexTestRope());
  std::string s4 = "Hello my name is Simon";
  Rope r5;
  std::string s5 = s4.substr(0,9);
  std::string s6 = s4.substr(9,13);
  r4.split(9,r5);
  r4.print_strings(std::cout);
  r5.print_strings(std::cout);
  assert(SAME(r4,s5));
  assert(SAME(r5,s6));
  
  //same tree as basic test but using different index for split (index in the middle of leaf)
  cout << endl;
  Rope r6(IndexTestRope());
  std::string s7 = "Hello my name is Simon";
  Rope r7;
  std::string s8 = s7.substr(0,13);
  std::string s9 = s7.substr(13,9);
  r6.split(13,r7);
  r6.print_strings(std::cout);
  r7.print_strings(std::cout);
  assert(SAME(r6,s8));
  assert(SAME(r7,s9));
  std::cout << "***Student split test passed" << std::endl;
  
  //same tree as basic test, but different strings for concatenation (I create two subtrees by my own)
  cout << endl;
  Rope r8(StudentConcatLeft());
  Rope r9(StudentConcatRight());
  std::string s10 = "my ";
  std::string s11 = "s Simon";
  assert(SAME(r8,s10));
  assert(SAME(r9,s11));
  std::cout << "***Student more index tests passed." << std::endl;

  cout << endl;
  r8.concat(r9);
  s10 += s11;
  assert(SAME(r8, s10));
  r8.print_strings(std::cout);
  std::cout << "***Student concatenation test passed" << std::endl;

  //report test using different begin and end index
  cout << endl;
  Rope r1(IndexTestRope());
  std::string s1 = "o my name ";
  string rs1;
  assert(r1.report(4,13,rs1) && rs1 == s1);
  cout << "My reported substring: " << rs1 << endl;
  std::cout << "***Student report test passed" << std::endl;

  //now I create a huge tree for student test, first for constructor and index test
  cout << endl;
  Rope r20(StudentTestRope());
  string s20 = "Rensselaer Polytechnic Institute is good";
  r20.print(std::cout);
  r20.print_strings(std::cout);
  assert(SAME(r20,s20));
  std::cout << "***Student Huge index test passed." << std::endl;
  
  //next for report test 
  cout << endl;
  string s21 = " Polytechnic Institut";
  string rs21;
  assert(r20.report(10,30,rs21) && rs21 == s21);
  cout << "Substr from huge tree report: " << rs21 << endl;
  std::cout << "***Student Huge report test passed." << std::endl;
  
  //then for split test (in the middle of leaf node)
  cout << endl;
  Rope r22(StudentTestRope());
  std::string s22 = "Rensselaer Polytechnic Institute is good";
  Rope r23;
  std::string s23 = s22.substr(0,21);
  std::string s24 = s22.substr(21,19);
  r22.split(21,r23);
  r22.print_strings(std::cout);
  r23.print_strings(std::cout);
  assert(SAME(r22,s23));
  assert(SAME(r23,s24));
  std::cout << "***Student Huge split test passed" << std::endl;
  
  //last for copy and assignment test
  cout << endl;
  Rope r25(StudentTestRope());
  Rope r26(r25);
  std::string rs25; std::string rs26;
  assert(r26.expose_root() != r25.expose_root());
  assert(r26.size() == r25.size());
  assert(r25.report(0,r25.size()-1,rs25) && r26.report(0,r26.size()-1,rs26) && rs26 == rs26);
  std::cout << "***Student Huge copy test passed" << std::endl;
  Rope r27;
  r27 = r25;
  assert(r27.expose_root() != r25.expose_root());
  assert(r27.size() == r25.size());
  assert(r27.report(0,r27.size()-1,rs25) && r25.report(0,r25.size()-1,rs26) && rs25 == rs26);
  std::cout << "***Student Huge assignment test passed" << std::endl;
  cout << endl;
}

//Used to compare a string and a rope that should be the same.
//You can uncomment the .report assert to test report on the whole string
bool SAME(const Rope& r, const std::string& s) {
	/*std::cout << "Comparing string \"" << s << "\" to Rope:" << std::endl;
	r.print(std::cout);*/
	assert(r.size() == (int)s.length() && "ERROR: ROPE SIZE DOES NOT MATCH STRING SIZE");
	char c;
	for(unsigned int i=0; i<s.size(); i++) {
		assert(r.index(i,c) && c == s[i] && "MISMATCH BETWEEN A CHARACTER IN ROPE AND STRING USING INDEX");
	}
	/*
	std::string s2;
	assert(r.report(0,s.length()-1,s2) && s2 == s && "MISMATCH BETWEEN ROPE.REPORT(0,length-1) AND STRING");
	*/
	return true;
}

//Function to check that the weights and structure from a root form a valid Rope.
bool ValidRope(Node* root){
	int left_sub = 0;
	if(!root){
		return true;
	}
	//Check that weight is correct as a leafe
	if(!root->left && !root->right){
		return root->weight == (int)root->value.length();
	}
	//Check that I'm at least one of the children of my parent.
	if(root->parent && (root->parent->left != root) && (root->parent->right != root)){
		return false;
	}
	//Check my weight if I'm not a leaf
	if(root->left) {
		left_sub = countWeights(root->left);
	}
	return (root->weight == left_sub) && ValidRope(root->left) && ValidRope(root->right);
}

int countWeights(Node* root) {
  Node* tmp = root;
  int weights = tmp-> weight;
  while (tmp-> right != NULL) {
  	tmp = tmp-> right;
  	weights = tmp-> weight;
  }
  return weights;
}

void BasicTests(){
	Rope r1(IndexTestRope());
	std::string s1 = "Hello my name is Simon";
	std::string rs1;

	r1.print(std::cout);
	r1.print_strings(std::cout);
	assert(SAME(r1,s1));
	std::cout << "***Index test passed." << std::endl;
	assert(r1.report(0,s1.length()-1,rs1) && rs1 == s1);
	std::cout << "***Basic report test passed." << std::endl;

	//Concat test
	Rope r2(ConcatTestRopeLeft());
	Rope r3(ConcatTestRopeRight());
	std::string s2 = "Hello my ";
	std::string s3 = "name i";

	assert(SAME(r2,s2));
	assert(SAME(r3,s3));
	std::cout << "***More index tests passed." << std::endl;

	r2.concat(r3);
	s2 += s3;
	assert(SAME(r2, s2));
	std::cout << "***Concatenation test passed" << std::endl;

	//Split test
	Rope r4(IndexTestRope()); //Wikipedia split @ 11
	std::string s4 = "Hello my name is Simon";
	Rope r5;
	std::string s5 = s4.substr(0,11);
	std::string s6 = s4.substr(11,11);
	r4.split(11,r5);
	r4.print_strings(std::cout);
	r5.print_strings(std::cout);
	assert(SAME(r4,s5));
	assert(SAME(r5,s6));
	std::cout << "***Split test passed" << std::endl;

	//Copy & Assignment tests
	Rope r9(IndexTestRope());
	Rope r10(r9);
	std::string rs2;
	assert(r10.expose_root() != r9.expose_root());
 	assert(r10.size() == r9.size());
	assert(r10.report(0,r10.size()-1,rs1) && r9.report(0,r9.size()-1,rs2) && rs1 == rs2);
	std::cout << "***Copy test passed" << std::endl;
	Rope r11;
	r11 = r9;
	assert(r11.expose_root() != r9.expose_root());
 	assert(r11.size() == r9.size());
	assert(r11.report(0,r11.size()-1,rs1) && r9.report(0,r9.size()-1,rs2) && rs1 == rs2);
	std::cout << "***Assignment test passed" << std::endl;
}

//Also used for split() test
Node* IndexTestRope(){
	Node* ret = new Node;
	ret->weight = 22;
	ret->left = new Node;
	ret->left->parent = ret;
	ret->left->weight = 9;
	ret->left->left = new Node;
	ret->left->left->parent = ret->left;
	ret->left->left->weight = 6;
	ret->left->right = new Node;
	ret->left->right->parent = ret->left;
	ret->left->right->weight = 6;
	ret->left->left->left = new Node;
	ret->left->left->left->parent = ret->left->left;
	ret->left->left->left->weight = 6;
	ret->left->left->left->value = "Hello ";
	ret->left->left->right = new Node;
	ret->left->left->right->parent = ret->left->left;
	ret->left->left->right->weight = 3;
	ret->left->left->right->value = "my ";
	ret->left->right->left = new Node;
	ret->left->right->left->parent = ret->left->right;
	ret->left->right->left->weight = 2;
	ret->left->right->right = new Node;
	ret->left->right->right->parent = ret->left->right;
	ret->left->right->right->weight = 1;
	ret->left->right->left->left = new Node;
	ret->left->right->left->right = new Node;
	ret->left->right->left->left->parent = ret->left->right->left;
	ret->left->right->left->left->weight = 2;
	ret->left->right->left->left->value = "na";
	ret->left->right->left->right->parent = ret->left->right->left;
	ret->left->right->left->right->weight = 4;
	ret->left->right->left->right->value = "me i";
	ret->left->right->right->left = new Node;
	ret->left->right->right->left->parent = ret->left->right->right;
	ret->left->right->right->left->weight = 1;
	ret->left->right->right->left->value = "s";
	ret->left->right->right->right = new Node;
	ret->left->right->right->right->parent = ret->left->right->right;
	ret->left->right->right->right->weight = 6;
	ret->left->right->right->right->value = " Simon";
	return ret;
}

Node* ConcatTestRopeLeft(){
	Node* ret = new Node;
	ret->weight = 6;
	ret->left = new Node;
	ret->right = new Node;
	ret->left->parent = ret;
	ret->left->weight = 6;
	ret->left->value = "Hello ";
	ret->right->parent = ret;
	ret->right->weight = 3;
	ret->right->value = "my ";
	return ret;
}

Node* ConcatTestRopeRight(){
	Node* ret = new Node;
	ret->weight = 2;
	ret->left = new Node;
	ret->right = new Node;
	ret->left->parent = ret;
	ret->left->weight = 2;
	ret->left->value = "na";
	ret->right->parent = ret;
	ret->right->weight = 4;
	ret->right->value = "me i";
	return ret;
}

//left and right subtrees for student concatenation test
Node* StudentConcatLeft() {
  Node* ret = new Node;
  ret-> weight = 3;
  ret-> value = "my ";
  return ret;
}

Node* StudentConcatRight() {
  Node* ret = new Node;
  ret-> weight = 1;
  ret-> left = new Node;
  ret-> left-> parent = ret;
  ret-> left-> weight = 1;
  ret-> left-> value = 's';
  ret-> right = new Node;
  ret-> right-> parent = ret;
  ret-> right-> weight = 6;
  ret-> right-> value = " Simon";
  return ret;
}

//huge tre I create for all tests
Node* StudentTestRope() {
  Node* ret = new Node;
  ret-> weight = 40;
  ret-> left = new Node;
  ret-> left-> parent = ret;
  ret-> left-> weight = 9;
  ret-> left-> left = new Node;
  ret-> left-> left-> parent = ret-> left;
  ret-> left-> left-> weight = 6;
  ret-> left-> left-> left = new Node;
  ret-> left-> left-> left-> parent = ret-> left-> left;
  ret-> left-> left-> left-> weight = 6;
  ret-> left-> left-> left-> value = "Rensse";
  ret-> left-> left-> right = new Node;
  ret-> left-> left-> right-> parent = ret-> left-> left;
  ret-> left-> left-> right-> weight = 3;
  ret-> left-> left-> right-> value = "lae";
  ret-> left-> right = new Node;
  ret-> left-> right-> parent = ret-> left;
  ret-> left-> right-> weight = 25;
  ret-> left-> right-> left = new Node;
  ret-> left-> right-> left-> parent = ret-> left-> right;
  ret-> left-> right-> left-> weight = 2;
  ret-> left-> right-> left-> left = new Node;
  ret-> left-> right-> left-> left-> parent = ret-> left-> right-> left;
  ret-> left-> right-> left-> left-> weight = 2;
  ret-> left-> right-> left-> left-> value = "r ";
  ret-> left-> right-> left-> right = new Node;
  ret-> left-> right-> left-> right-> parent = ret-> left-> right-> left;
  ret-> left-> right-> left-> right-> weight = 19;
  ret-> left-> right-> left-> right-> left = new Node;
  ret-> left-> right-> left-> right-> left-> parent = ret-> left-> right-> left-> right;
  ret-> left-> right-> left-> right-> left-> weight = 5;
  ret-> left-> right-> left-> right-> left-> left = new Node;
  ret-> left-> right-> left-> right-> left-> left-> parent = ret-> left-> right-> left-> right-> left;
  ret-> left-> right-> left-> right-> left-> left-> weight = 5;
  ret-> left-> right-> left-> right-> left-> left-> value = "Polyt";
  ret-> left-> right-> left-> right-> left-> right = new Node;
  ret-> left-> right-> left-> right-> left-> right-> parent = ret-> left-> right-> left-> right-> left;
  ret-> left-> right-> left-> right-> left-> right-> weight = 8;
  ret-> left-> right-> left-> right-> left-> right-> left = new Node;
  ret-> left-> right-> left-> right-> left-> right-> left-> parent = ret-> left-> right-> left-> right-> left-> right;
  ret-> left-> right-> left-> right-> left-> right-> left-> weight = 3;
  ret-> left-> right-> left-> right-> left-> right-> left-> left = new Node;
  ret-> left-> right-> left-> right-> left-> right-> left-> left-> parent = ret-> left-> right-> left-> right-> left-> right-> left;
  ret-> left-> right-> left-> right-> left-> right-> left-> left-> weight = 3;
  ret-> left-> right-> left-> right-> left-> right-> left-> left-> value = "ech";
  ret-> left-> right-> left-> right-> left-> right-> left-> right = new Node;
  ret-> left-> right-> left-> right-> left-> right-> left-> right-> parent = ret-> left-> right-> left-> right-> left-> right-> left;
  ret-> left-> right-> left-> right-> left-> right-> left-> right-> weight = 5;
  ret-> left-> right-> left-> right-> left-> right-> left-> right-> value = "nic I";
  ret-> left-> right-> left-> right-> left-> right-> right = new Node;
  ret-> left-> right-> left-> right-> left-> right-> right-> parent = ret-> left-> right-> left-> right-> left-> right;
  ret-> left-> right-> left-> right-> left-> right-> right-> weight = 6;
  ret-> left-> right-> left-> right-> left-> right-> right-> value = "nstitu";
  ret-> left-> right-> left-> right-> right = new Node;
  ret-> left-> right-> left-> right-> right-> parent = ret-> left-> right-> left-> right;
  ret-> left-> right-> left-> right-> right-> weight = 3;
  ret-> left-> right-> left-> right-> right-> left = new Node;
  ret-> left-> right-> left-> right-> right-> left-> parent = ret-> left-> right-> left-> right-> right;
  ret-> left-> right-> left-> right-> right-> left-> weight = 3;
  ret-> left-> right-> left-> right-> right-> left-> value = "te ";
  ret-> left-> right-> left-> right-> right-> right = new Node;
  ret-> left-> right-> left-> right-> right-> right-> parent = ret-> left-> right-> left-> right-> right;
  ret-> left-> right-> left-> right-> right-> right-> weight = 1;
  ret-> left-> right-> left-> right-> right-> right-> value = 'i';
  ret-> left-> right-> right = new Node;
  ret-> left-> right-> right-> parent = ret-> left-> right;
  ret-> left-> right-> right-> weight = 2;
  ret-> left-> right-> right-> left = new Node;
  ret-> left-> right-> right-> left-> parent = ret-> left-> right-> right;
  ret-> left-> right-> right-> left-> weight = 2;
  ret-> left-> right-> right-> left-> value = "s ";
  ret-> left-> right-> right-> right = new Node;
  ret-> left-> right-> right-> right-> parent = ret-> left-> right-> right;
  ret-> left-> right-> right-> right-> weight = 4;
  ret-> left-> right-> right-> right-> value = "good";
  return ret;
}