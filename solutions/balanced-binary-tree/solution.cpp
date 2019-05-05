#include <algorithm>
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
	bool isBalanced(const TreeNode* root) {
		if (!root)
			return true;

		// Item of a path constructed by post-order DFS.
		struct PathItem {
			// Tree node.
			const TreeNode* node;
			// Left subtree depth or 0 if the left
			// subtree hasn't been searched yet.
			int left_depth;
			// Right subtree depth or 0 if the right
			// subtree hasn't been searched yet.
			int right_depth;

			PathItem(const TreeNode* n, int l, int r) :
				node(n), left_depth(l), right_depth(r) {}
		};
		stack<PathItem> path;
		path.emplace(root, 0, 0);
		while (!path.empty()) {
			auto& item = path.top();
			auto node = item.node;
			if (node->left && item.left_depth == 0) {
				// Search left subtree.
				path.emplace(node->left, 0, 0);
			} else if (node->right && item.right_depth == 0) {
				// Search right subtree.
				path.emplace(node->right, 0, 0);
			} else {
				// Searched both left and right subtrees.
				// Ascend the tree.
				if (abs(item.left_depth - item.right_depth) > 1)
					return false;
				int depth = 1 + max(item.left_depth,
						    item.right_depth);
				path.pop();
				if (!path.empty()) {
					auto& parent = path.top();
					if (parent.node->left == node)
						parent.left_depth = depth;
					else
						parent.right_depth = depth;
				}
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
		{1, 2}, // true
		{1, 2, 3}, // true
		{1, 0, 2}, // true
		{1, 2, 0, 3}, // false
		{1, 2, 3, 4, 5, 6, 7, 8}, // true
		{1, 2, 3, 0, 4, 0, 5, 6}, // false
		{1, 2, 2, 3, 3, 0, 0, 4, 4}, // false
		{1, 2, 0, 3, 0, 4, 0, 5, 0}, // false
		{1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 0, 0, 5, 5}, // true
	};
	Solution solution;
	for (const auto& values: input) {
		auto root = makeTree(values);
		cout << "Binary tree " << root << " is ";
		if (!solution.isBalanced(root))
			cout << "not ";
		cout << "balanced" << endl;
		deleteTree(root);
	}
	return 0;
}
