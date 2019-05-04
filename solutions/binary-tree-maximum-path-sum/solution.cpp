#include <algorithm>
#include <iostream>
#include <limits>
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
	// Return the max sum among all paths starting at the root node and
	// update max_sum with the max sum among all paths encountered while
	// descending the tree.
	int doMaxPathSum(const TreeNode* root, int* max_sum) {
		if (!root)
			return 0;
		int left_sum = max(0, doMaxPathSum(root->left, max_sum));
		int right_sum = max(0, doMaxPathSum(root->right, max_sum));
		*max_sum = max(*max_sum, root->val + left_sum + right_sum);
		return root->val + max(left_sum, right_sum);
	}
public:
	int maxPathSum(const TreeNode* root) {
		int max_sum = numeric_limits<int>::min();
		doMaxPathSum(root, &max_sum);
		return max_sum;
	}
};

int main()
{
	vector<int> input[] = {
		{1}, // 1
		{-3}, // -3
		{1, 2, 3}, // 6
		{1, 2, 0, 3, 4}, // 9
		{1, 2, 3, 4, 0, 0, 5}, // 15
		{1, 0, 1, 1, 1, 1, 1, 1}, // 5
		{1, 2, 3, 20, 30, 10, 10}, // 52
		{1, 2, 3, 10, 20, 10, 20}, // 46
		{-10, 9, 20, 0, 0, 15, 7}, // 42
	};
	Solution solution;
	for (const auto& values: input) {
		auto root = makeTree(values);
		auto sum = solution.maxPathSum(root);
		cout << root << " => " << sum << endl;
		deleteTree(root);
	}
	return 0;
}
