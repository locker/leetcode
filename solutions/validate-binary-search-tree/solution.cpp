#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

ostream& operator<<(ostream& out, const TreeNode* root)
{
	cout << '[';
	queue<const TreeNode*> todo;
	todo.push(root);
	int null_count = 0;
	while (!todo.empty()) {
		auto node = todo.front();
		todo.pop();
		if (node) {
			todo.push(node->left);
			todo.push(node->right);
			if (node != root)
				cout << ',';
			while (null_count > 0) {
				cout << "null,";
				--null_count;
			}
			cout << node->val;
		} else {
			++null_count;
		}
	}
	cout << ']';
	return out;
}

// Assume 0 means no value.
TreeNode* makeTree(const vector<int>& values)
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

class Solution {
public:
	bool isValidBST(const TreeNode* root) {
		if (!root)
			return true;
		stack<const TreeNode*> todo;
		auto node = root;
		bool first = true;
		int prev_val = 0;
		while (node || !todo.empty()) {
			if (node) {
				todo.push(node);
				node = node->left;
			} else {
				node = todo.top();
				todo.pop();
				int val = node->val;
				if (!first && val <= prev_val)
					return false;
				first = false;
				prev_val = val;
				node = node->right;
			}
		}
		return true;
	}
};

int main()
{
	vector<int> input[] = {
		{}, // true
		{1}, // true
		{2, 1}, // true
		{1, 2}, // false
		{2, 1, 3}, // true
		{1, 2, 3}, // false
		{1, 0, 2}, // true
		{1, 0, 2, 3, 4}, // false
		{1, 0, 3, 2, 4}, // true
		{1, 0, 3, 0, 2}, // false
		{1, 0, 2, 0, 3}, // true
		{5, 1, 6, 2, 3, 0, 7}, // false
		{5, 2, 6, 1, 3, 0, 7}, // true
		{10, 5, 15, 0, 0, 6, 20}, // false
	};
	Solution solution;
	for (const auto& values: input) {
		auto root = makeTree(values);
		cout << "Binary tree " << root << " is ";
		if (!solution.isValidBST(root))
			cout << "not ";
		cout << "a valid BST" << endl;
		deleteTree(root);
	}
	return 0;
}
