#include <iostream>
using namespace std;

struct node {
	node* left;
	node* right;
	int value;
	node(int v):value(v),left(nullptr),right(nullptr) {}
	node(int v,node* left_,node* right_) :value(v), left(left_), right(right_) {}
	node(const node&) = delete;
	node(const node&&) = delete;
};
struct elem {
	elem* down;
	node* me;
	elem(elem *down_, node* me_) :down(down_), me(me_) {}
};
struct elemc {
	elemc* down;
	node* me;
	int cnt;
	elemc(elemc* down_, node* me_,int cnt_) :down(down_), me(me_), cnt(cnt_) {}
};
struct stack {
	static elem* top;
	void push(node* t) {
		if (!top) { top = new elem(nullptr, t); }
		else {
			top = new elem(top,t);
		}
	}
	node* pop() {
		node* temp = top->me;
		top = top->down;
		if (!top)top = nullptr;
		return temp;
	}
	bool isempty() {
		return !top;
	}
};
struct stackc {
	static elemc* top;
	void push(node* t, int val) {
		if (!top) { top = new elemc(nullptr, t,val); }
		else {
			top = new elemc(top, t,val);
		}
	}
	elemc* pop() {
		elemc* temp = top;
		top = top->down;
		if (!top)top = nullptr;
		return temp;
	}
	bool isempty() {
		return !top;
	}
};
elem* stack::top = nullptr;
elemc* stackc::top = nullptr;

void preorder(node* root) {
	node* temp = root;
	stack stack1 = stack();
	while(temp || !stack1.isempty()){
		if (!temp && !stack1.isempty()) {
			temp = stack1.pop();
		}
	cout << (temp->value);
	if (temp->right)stack1.push(temp->right);
	temp = temp->left;
	}
}
void inorder(node* root) {
	node* temp = root;
	stack stack1 = stack();
	while (temp || !stack1.isempty()) {
		if (temp) {
			stack1.push(temp);
			if (temp->left) {
				temp = temp->left;
			}
			else {
				temp = nullptr;
			}
		}
		else {
			temp = stack1.pop();
			cout << temp->value;
			temp = temp->right;
		}
	}
}
void postorder(node* root) {
	node* temp = root;
	stackc stack1 = stackc();
	stack1.push(temp, 1);
	while (temp || !stack1.isempty()) {
		elemc* t = stack1.pop();
		if (t->me) {
			if (t->cnt == 1) {
				stack1.push(t->me, 0);
				stack1.push(t->me->left, 1);
			}
			else if (t->cnt == 0) {
				stack1.push(t->me, -1);
				stack1.push(t->me->right, 1);
			}
			else cout << t->me->value;
		}
	}
}

int main() {
	node* root = new node(1,new node(2,new node(3,nullptr,nullptr),new node(4, new node(5,nullptr,nullptr), nullptr)),new node(6, new node(7, nullptr, new node(8, nullptr, new node(9, nullptr, nullptr))),nullptr));

	preorder(root); cout << endl;
	inorder(root); cout << endl;
	postorder(root); cout << endl;
}

	
