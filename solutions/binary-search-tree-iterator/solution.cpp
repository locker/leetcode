#include <iostream>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

ostream& operator<<(ostream& out, const TreeNode* root)
{
	out << '[';
	queue<const TreeNode*> todo;
	todo.push(root);
	int null_count = 0;
	while (!todo.empty()) {
		auto node = todo.front();
		todo.pop();
		if (node) {
			if (node != root)
				out << ',';
			while (null_count > 0) {
				out << "null,";
				--null_count;
			}
			out << node->val;
			todo.push(node->left);
			todo.push(node->right);
		} else {
			++null_count;
		}
	}
	out << ']';
	return out;
}

// Assume 0 means no value.
TreeNode* makeTree(const vector<int> values)
{
	if (values.empty())
		return nullptr;
	auto it = values.begin();
	auto root = new TreeNode(*it++);
	queue<TreeNode*> todo;
	todo.push(root);
	while (it != values.end()) {
		auto node = todo.front();
		todo.pop();
		int val;
		if ((val = *it++) != 0) {
			node->left = new TreeNode(val);
			todo.push(node->left);
		}
		if (it != values.end() && (val = *it++) != 0) {
			node->right = new TreeNode(val);
			todo.push(node->right);
		}
	}
	return root;
}

void deleteTree(TreeNode* root)
{
	if (root) {
		deleteTree(root->left);
		deleteTree(root->right);
		delete root;
	}
}

class BSTIterator {
	const TreeNode* curr;
	stack<const TreeNode*> todo;
public:
	BSTIterator(const TreeNode* root) {
		curr = root;
		if (curr) {
			while (curr->left) {
				todo.push(curr);
				curr = curr->left;
			}
		}
	}

	/** @return the next smallest number */
	int next() {
		int val = curr->val;
		if (curr->right) {
			curr = curr->right;
			while (curr->left) {
				todo.push(curr);
				curr = curr->left;
			}
		} else if (!todo.empty()) {
			curr = todo.top();
			todo.pop();
		} else {
			curr = nullptr;
		}
		return val;
	}

	/** @return whether we have a next smallest number */
	bool hasNext() {
		return curr != nullptr;
	}
};

int main()
{
	vector<int> input[] = {
		{1},
		{2, 1},
		{2, 1, 3},
		{1, 0, 2},
		{10, 5, 15, 2, 7},
		{7, 3, 15, 0, 0, 9, 20},
		{5, 4, 0, 3, 0, 2, 0, 1},
	};
	for (const auto& values: input) {
		auto root = makeTree(values);
		cout << root << " => [";
		BSTIterator it(root);
		bool first = true;
		while (it.hasNext()) {
			if (!first)
				cout << ',';
			cout << it.next();
			first = false;
		}
		cout << ']' << endl;
		deleteTree(root);
	}
	return 0;
}
