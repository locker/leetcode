#include <iostream>
#include <queue>
#include <stack>
#include <utility>
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
	void recoverTree(TreeNode* root) {
		// First node violating the BST property.
		TreeNode* bad = nullptr;
		// In-order predecessor of the bad node.
		TreeNode* bad_prev = nullptr;

		//
		// Traverse the tree in-order and swap values of bad nodes.
		// For the solution to use constant space, implement Morris
		// algorithm.
		//
		TreeNode* prev = nullptr;
		TreeNode* curr = root;
		while (curr) {
			if (curr->left) {
				// Check the left subtree.
				auto p = curr->left;
				while (p->right && p->right != curr)
					p = p->right;
				if (!p->right) {
					// Haven't traversed it yet.
					// Link the last in-order node
					// to the current and descend.
					p->right = curr;
					curr = curr->left;
					continue;
				}
				// A loop is found hence we've already been
				// there. Clear the auxiliary pointer and go
				// right.
				p->right = nullptr;
			}

			// Either there's no left subtree or we have already
			// traversed it. Visit the current node and go right.
			if (prev && prev->val > curr->val) {
				// A node violating the BST property is found.
				if (bad) {
					// This is the second such node.
					// Swap its value with the first.
					swap(bad_prev->val, curr->val);
					bad = bad_prev = nullptr;
				} else {
					// The first bad node is found.
					bad = curr;
					bad_prev = prev;
				}
			}

			prev = curr;
			curr = curr->right;
		}
		if (bad) {
			// Special case: if there's the only bad node,
			// then we need to swap it with its predecessor.
			swap(bad->val, bad_prev->val);
		}
	}
};

int main()
{
	vector<int> input[] = {
		{1, 2},
		{1, 2, 3},
		{2, 0, 1},
		{1, 2, 0, 3},
		{3, 1, 4, 0, 0, 2},
		{5, 3, 4, 1, 6, 0, 7, 0, 2},
	};
	Solution solution;
	for (const auto& values: input) {
		auto root = makeTree(values);
		cout << root << " => ";
		solution.recoverTree(root);
		cout << root << endl;
		deleteTree(root);
	}
	return 0;
}
