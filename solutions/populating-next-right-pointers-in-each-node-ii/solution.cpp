#include <iostream>
#include <queue>
#include <vector>

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
	out << '[';
	queue<Node*> todo;
	todo.push(root);
	int null_count = 0;
	while (!todo.empty()) {
		auto node = todo.front();
		todo.pop();
		if (node) {
			todo.push(node->left);
			todo.push(node->right);
			if (node != root)
				out << ',';
			while (null_count > 0) {
				out << "null,";
				--null_count;
			}
			out << node->val << "->";
			if (node->next)
				out << node->next->val;
			else
				out << "null";
		} else {
			++null_count;
		}
	}
	out << ']';
	return out;
}

Node* makeNode(int val)
{
	return new Node(val, nullptr, nullptr, nullptr);
}

// Assume 0 means no value.
Node* makeTree(const vector<int>& values)
{
	if (values.empty())
		return nullptr;
	auto it = values.begin();
	auto root = makeNode(*it++);
	queue<Node*> todo;
	todo.push(root);
	while (it != values.end()) {
		auto node = todo.front();
		todo.pop();
		int val;
		if ((val = *it++) != 0) {
			node->left = makeNode(val);
			todo.push(node->left);
		}
		if (it != values.end() && (val = *it++) != 0) {
			node->right = makeNode(val);
			todo.push(node->right);
		}
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
		root->next = next;
		while (next && !next->left && !next->right)
			next = next->next;
		if (next)
			next = next->left ? next->left : next->right;
		if (root->right) {
			doConnect(root->right, next);
			if (root->left)
				doConnect(root->left, root->right);
		} else if (root->left) {
			doConnect(root->left, next);
		}
	}
public:
	Node* connect(Node* root) {
		if (root)
			doConnect(root, nullptr);
		return root;
	}
};

int main()
{
	vector<int> input[] = {
		{},
		{1},
		{1, 2},
		{1, 2, 3},
		{1, 0, 2},
		{1, 2, 3, 4, 5, 0, 6},
		{1, 2, 3, 4, 0, 0, 5},
		{1, 2, 3, 0, 4, 0, 5},
		{1, 2, 3, 4, 0, 5, 6, 7, 0, 8, 9, 10, 11, 12, 0, 0, 0, 0, 13, 14},
		{1, 2, 3, 4, 5, 6, 0, 7, 8, 0, 9, 10, 11, 0, 12, 0, 0, 0, 0, 0, 0, 13, 0, 0, 0, 14},
	};
	Solution solution;
	for (const auto& values: input) {
		auto root = makeTree(values);
		solution.connect(root);
		cout << root << endl;
		deleteTree(root);
	}
	return 0;
}
