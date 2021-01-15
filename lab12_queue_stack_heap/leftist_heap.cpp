//Buster Holzbauer copy/implementation of leftist heap exercise 22.14
//Written April 9th, 2019 at far too late in the night

#include <algorithm> //needed for std::swap
#include <iostream>

/////////////////////////Taken from Lecture 22 notes//////////////////////
template <class T> class LeftNode {
public:
  LeftNode() : npl(0), left(0), right(0) {}
  LeftNode(const T& init) : value(init), npl(0), left(0), right(0) {}
  T value;
  int npl; // the null-path length
  LeftNode* left;
  LeftNode* right;
};

template <class T>
LeftNode<T>* merge(LeftNode<T> *h1,LeftNode<T> *h2) {
 if (!h1)
   return h2;
 else if (!h2)
   return h1;
 else if (h2->value > h1->value)
   return merge_helper(h1, h2);
 else
   return merge_helper(h2, h1);
}

template <class T>
LeftNode<T>* merge_helper(LeftNode<T> *h1, LeftNode<T> *h2) {
   if (h1->left == NULL)
     h1->left = h2;
   else {
     h1->right = merge(h1->right, h2);
     if(h1->left->npl < h1->right->npl)
       std::swap(h1->left, h1->right);
     h1->npl = h1->right->npl + 1;
   }
   return h1;
}

///////////////////////Standard print sideways function////////////////////

template <class T>
void printTree(LeftNode<T>* head, int level){
	if(head){
		printTree(head->right, level+1);
		std::cout << std::string(level,'\t') << head->value << std::endl;
		printTree(head->left, level+1);
	}
}

template <class T>
void printTree(LeftNode<T>* head){
	printTree(head,0);
}

//////////////////////////22.14 exercise functions//////////////////////////

template <class T>
void insert(const T& val, LeftNode<T>*& head){
	if(!head){
		head = new LeftNode<T>(val);
	}
	else{
		LeftNode<T>* x = new LeftNode<T>(val);
		head = merge(head,x);
	}
}

//Many del_min functions will not return the value to be consistent with pop()
template <class T>
T del_min(LeftNode<T>*& head){
	T ret = head->value;
	LeftNode<T>* tmp = head;
	head = merge(head->left, head->right);
	delete tmp;
	return ret;
}

////////////////////Simple recursive binary tree destructor/////////////////

template <class T>
void destroyTree(LeftNode<T>* head){
	if(head){
		destroyTree(head->left);
		destroyTree(head->right);
		delete head;
	}
}

///////////////////////Actual main to do the inserts/pops////////////////////

int main(){
	LeftNode<int>* head = NULL;

	//insert 1,2,3,4,5,6
	for(int i=1; i<=6; i++){
		insert(i,head);
		std::cout << "Inserting " << i << std::endl;
		printTree(head);
		std::cout << "-------" << std::endl;
	}

	//del_min
	std::cout << "del_min: " << del_min(head) << std::endl;
	printTree(head);
	std::cout << "-------" << std::endl;

	//insert 7,8
	insert(7,head);
	std::cout << "Inserting " << 7 << std::endl;
	printTree(head);
	std::cout << "-------" << std::endl;
	insert(8,head);
	std::cout << "Inserting " << 8 << std::endl;
	printTree(head);
	std::cout << "-------" << std::endl;

	//del_min, del_min
	std::cout << "del_min: " << del_min(head) << std::endl;
	printTree(head);
	std::cout << "-------" << std::endl;
	std::cout << "del_min: " << del_min(head) << std::endl;
	printTree(head);
	std::cout << "-------" << std::endl;

	destroyTree(head); //Don't want to leak
	return 0;
}
