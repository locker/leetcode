#include <algorithm>
#include <iostream>
#include <queue>
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
	int minDepth(const TreeNode* root) {
		if (!root)
			return 0;
		int left = minDepth(root->left);
		int right = minDepth(root->right);
		if (left == 0)
			return 1 + right;
		if (right == 0)
			return 1 + left;
		return 1 + min(left, right);
	}
};

int main()
{
	vector<int> input[] = {
		{}, // 0
		{1}, // 1
		{1, 2}, // 2
		{1, 2, 3}, // 2
		{1, 0, 2}, // 2
		{1, 2, 3, 4, 5, 6, 7, 8}, // 3
		{1, 2, 3, 0, 4, 0, 5, 6}, // 3
		{1, 2, 0, 3, 0, 4, 0, 5, 0}, // 5
	};
	Solution solution;
	for (const auto& values: input) {
		auto root = makeTree(values);
		cout << "Min depth of " << root << " is " <<
			solution.minDepth(root) << endl;
		deleteTree(root);
	}
	return 0;
}
