#include <iostream>
#include <queue>

using namespace std;

class Node {
public:
	int val;
	Node* left;
	Node* right;
	Node* next;

	Node() {}

	Node(int _val, Node* _left, Node* _right, Node* _next) {
		val = _val;
		left = _left;
		right = _right;
		next = _next;
	}
};

ostream& operator<<(ostream& out, Node* root)
{
	if (!root)
		return out << "[]";
	out << '[';
	queue<Node*> todo;
	todo.push(root);
	while (!todo.empty()) {
		auto node = todo.front();
		todo.pop();
		if (node->left)
			todo.push(node->left);
		if (node->right)
			todo.push(node->right);
		if (node != root)
			out << ',';
		if (node->next)
			out << node->next->val;
		else
			out << "null";
	}
	out << ']';
	return out;
}

Node* makeNode(int val)
{
	return new Node(val, nullptr, nullptr, nullptr);
}

Node* makeTree(int level_count)
{
	if (level_count == 0)
		return nullptr;
	int val = 0;
	auto root = makeNode(++val);
	queue<Node*> todo;
	todo.push(root);
	todo.push(nullptr);
	for (int i = 1; i < level_count; ++i) {
		for (auto node = todo.front(); node != nullptr;
		     todo.pop(), node = todo.front()) {
			node->left = makeNode(++val);
			node->right = makeNode(++val);
			todo.push(node->left);
			todo.push(node->right);
		}
		todo.pop();
		todo.push(nullptr);
	}
	return root;
}

void deleteTree(Node* root)
{
	if (root) {
		deleteTree(root->left);
		deleteTree(root->right);
		delete root;
	}
}

class Solution {
	void doConnect(Node* root, Node* next) {
		if (!root)
			return;
		root->next = next;
		doConnect(root->left, root->right);
		doConnect(root->right, next ? next->left : nullptr);
	}
public:
	Node* connect(Node* root) {
		doConnect(root, nullptr);
		return root;
	}
};

int main()
{
	Solution solution;
	for (int i = 0; i < 6; ++i) {
		auto root = makeTree(i);
		solution.connect(root);
		cout << root << endl;
		deleteTree(root);
	}
	return 0;
}
