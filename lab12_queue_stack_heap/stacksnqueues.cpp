#include <iostream>
#include <stack>
#include <queue>

class Node{
public:
	Node(int v) : val(v), left(NULL), right(NULL) {}
	int val;
	Node* left;
	Node* right;
};

//Builds a balanced binary search tree with 1-7
Node* BuildTree(){
	Node* ret = new Node(4);
	ret->left = new Node(2);
	ret->right = new Node(6);
	ret->left->left = new Node(1);
	ret->left->right = new Node(3);
	ret->right->left = new Node(5);
	ret->right->right = new Node(7);
	return ret;
}

void DestroyTree(Node*& root){
	if(!root) return;
	DestroyTree(root->left);
	DestroyTree(root->right);
	delete root;
	root = NULL;
}

void preOrder(Node* root){
	std::stack<Node*> s;
	s.push(root);
	while(!s.empty()){
		Node* curr = s.top();
		s.pop();
		std::cout << curr->val << std::endl;
		if(curr->right)
			s.push(curr->right);
		if(curr->left)
			s.push(curr->left);

	}

}

//Looks a lot like how iterator++ worked!
void inOrder(Node* root){
	std::stack<Node*> s;

	Node* current = root;
	while(current){
		s.push(current);
		current = current->left;
	}
	while(!s.empty() && !current){
		current = s.top();
		s.pop();
		std::cout << current->val << std::endl;
		current = current->right;
		while(current){
			s.push(current);
			current = current->left;
		}
	}
}

//Looks a lot like our old BFS. If we want to keep rows separate we will need a current queue and next queue
void BFS(Node* root){
	std::queue<Node*> q;
	q.push(root);
	while(!q.empty()){
		Node* tmp = q.front();
		q.pop();
		if(tmp){
			std::cout << tmp->val;
			q.push(tmp->left);
			q.push(tmp->right);
		}
	}
}

int main(){
	Node* test = BuildTree();

	preOrder(test);
	std::cout << "============" << std::endl;
	inOrder(test);
	std::cout << "============" << std::endl;
	BFS(test);

	DestroyTree(test);
	return 0;
}
