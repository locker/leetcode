#include <deque>
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
	bool isSymmetric(const TreeNode* root) {
		// Iterate through the tree level by level (BFS).
		// Upon completing a level, check that it's symmetric.
		deque<const TreeNode*> level;
		deque<const TreeNode*> next_level;
		level.push_back(root);
		while (!level.empty()) {
			auto node = level.front();
			level.pop_front();
			if (node) {
				next_level.push_back(node->left);
				next_level.push_back(node->right);
			}
			if (!level.empty())
				continue;

			swap(level, next_level);
			int i = 0;
			int j = level.size() - 1;
			while (i < j) {
				if (level[i] && level[j] &&
				    level[i]->val != level[j]->val)
					return false;
				if (!level[i] && level[j])
					return false;
				if (level[i] && !level[j])
					return false;
				++i;
				--j;
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
		{1, 2}, // false
		{1, 2, 3}, // false
		{1, 2, 2}, // true
		{1, 2, 2, 0, 3, 3}, // true
		{1, 2, 2, 0, 3, 4}, // false
		{1, 2, 2, 0, 3, 0, 3}, // false
		{1, 2, 2, 3, 4, 4, 3, 5, 0, 6, 0, 0, 6, 0, 5}, // true
	};
	Solution solution;
	for (const auto& values: input) {
		auto root = makeTree(values);
		cout << root << " is ";
		if (!solution.isSymmetric(root))
			cout << "not ";
		cout << "symmetric" << endl;
		deleteTree(root);
	}
	return 0;
}
