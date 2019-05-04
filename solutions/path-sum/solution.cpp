#include <iostream>
#include <queue>
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
public:
	bool hasPathSum(const TreeNode* root, int target) {
		if (!root)
			return false;
		if (!root->left && !root->right && root->val == target)
			return true;
		return hasPathSum(root->left, target - root->val) ||
			hasPathSum(root->right, target - root->val);
	}
};

int main()
{
	pair<vector<int>, int> input[] = {
		{{}, 0}, // false
		{{1}, 1}, // true
		{{1, 2}, 4}, // false
		{{1, 2, 3}, 4}, // true
		{{1, 0, 3, 4, 5}, 7}, // false
		{{1, 0, 3, 4, 0, 5, 6}, 14}, // true
		{{1, 2, 3, 0, 0, 4, 0, 5}, 15}, // false
		{{1, 2, 3, 0, 0, 4, 0, 5, 6}, 3}, // true
		{{1, 2, 3, 0, 0, 4, 0, 5, 6, 0, 7}, 17}, // false
		{{5, 4, 8, 11, 0, 13, 4, 7, 2, 0, 0, 0, 1}, 22}, // true
	};
	Solution solution;
	for (const auto& p: input) {
		auto root = makeTree(p.first);
		auto sum = p.second;
		auto has_path = solution.hasPathSum(root, sum);
		cout << root << ", " << sum << " => " <<
			(has_path ? "true" : "false") << endl;
		deleteTree(root);
	}
	return 0;
}
