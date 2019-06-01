#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
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
	int rob(const TreeNode* root) {
		if (!root)
			return 0;

		// Element of a path from the tree root to some node.
		struct PathNode {
			const TreeNode* node;
			// Max amount of money we can rob from the subtree
			// rooted at this node if it is or isn't included,
			// respectively.
			int val_with, val_without;
			PathNode(const TreeNode* n):
				node(n), val_with(n->val), val_without(0) {}
		};

		// Path built by post-order DFS.
		stack<PathNode> path;
		path.emplace(root);

		// Node visited on the previous iteration.
		TreeNode dummy(0);
		PathNode prev(&dummy);

		while (!path.empty()) {
			auto& curr = path.top();
			auto left = curr.node->left;
			auto right = curr.node->right;

			// Update the value with the sub-tree that we visited
			// on the previous iteration.
			if (left == prev.node || right == prev.node) {
				curr.val_with += prev.val_without;
				curr.val_without += max(prev.val_with,
							prev.val_without);
			}

			if (left && left != prev.node && right != prev.node) {
				// Visit the left sub-tree.
				path.emplace(left);
				prev = curr;
			} else if (right && right != prev.node) {
				// Visit the right sub-tree.
				path.emplace(right);
				prev = curr;
			} else {
				// Visited both sub-trees. Ascend the tree.
				prev = curr;
				path.pop();
			}
		}
		return max(prev.val_with, prev.val_without);
	}
};

int main()
{
	vector<int> input[] = {
		{}, // 0
		{1}, // 1
		{1, 2}, // 2
		{3, 1, 1}, // 3
		{3, 2, 2}, // 4
		{3, 0, 4}, // 4
		{3, 4, 5, 1, 3, 0, 1}, // 9
		{4, 1, 0, 2, 0, 3}, // 7
		{3, 2, 3, 0, 3, 0, 1}, // 7
	};
	Solution solution;
	for (const auto& values: input) {
		auto root = makeTree(values);
		cout << root << " => " << solution.rob(root) << endl;
		deleteTree(root);
	}
	return 0;
}
