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
	out << '[';
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
				out << ',';
			while (null_count > 0) {
				out << "null,";
				--null_count;
			}
			out << node->val;
		} else {
			++null_count;
		}
	}
	out << ']';
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
	// Return the length of the longest univalue path starting at
	// the root node and update max_len with the max univalue path
	// length encountered while descending the tree.
	int doLongestUnivaluePath(const TreeNode* root, int *max_len) {
		// Max path length passing through the root node.
		int len = 0;
		// Max path length starting at the root node and passing
		// through the left child node.
		int left_len = 0;
		// Max path length starting at the root node and passing
		// through the right child node.
		int right_len = 0;
		if (root->left) {
			left_len = doLongestUnivaluePath(root->left, max_len);
			if (root->left->val == root->val)
				len += ++left_len;
			else
				left_len = 0;
		}
		if (root->right) {
			right_len = doLongestUnivaluePath(root->right, max_len);
			if (root->right->val == root->val)
				len += ++right_len;
			else
				right_len = 0;
		}
		*max_len = max(*max_len, len);
		return max(left_len, right_len);
	}
public:
	int longestUnivaluePath(const TreeNode* root) {
		int max_len = 0;
		if (root)
			doLongestUnivaluePath(root, &max_len);
		return max_len;
	}
};

int main()
{
	vector<int> input[] = {
		{}, // 0
		{1}, // 0
		{1, 2, 3}, // 0
		{1, 1, 1}, // 2
		{1, 0, 1}, // 1
		{1, 0, 1, 1}, // 2
		{5, 4, 5, 1, 1, 0, 5}, // 2
		{1, 4, 5, 4, 4, 0, 5}, // 2
		{1, 0, 1, 1, 1, 1, 1, 1}, // 4
		{1, 2, 2, 0, 2, 2, 2, 2, 0, 3, 2}, // 3
	};
	Solution solution;
	for (const auto& values: input) {
		auto root = makeTree(values);
		auto len = solution.longestUnivaluePath(root);
		cout << root << " => " << len << endl;
		deleteTree(root);
	}
	return 0;
}
