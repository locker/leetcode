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

// Assume < 0 means no value.
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
		if ((val = *it++) >= 0) {
			node->left = new TreeNode(val);
			todo.push(node->left);
		}
		if (it != values.end() && (val = *it++) >= 0) {
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
	int sumNumbers(const TreeNode* root) {
		if (!root)
			return 0;
		int sum = 0;
		stack<const TreeNode*> path;
		path.push(root);
		int path_val = root->val;
		const TreeNode* prev = nullptr;
		while (!path.empty()) {
			auto node = path.top();
			auto right = node->right;
			auto left = node->left;
			if (!left && !right)
				sum += path_val;
			if ((right && right == prev) ||
			    (!right && (!left || left == prev))) {
				path.pop();
				path_val /= 10;
			} else if (right && (!left || left == prev)) {
				path.push(right);
				path_val *= 10;
				path_val += right->val;
			} else {
				path.push(left);
				path_val *= 10;
				path_val += left->val;
			}
			prev = node;
		}
		return sum;
	}
};

int main()
{
	vector<int> input[] = {
		{}, // 0
		{1}, // 1
		{0, 2}, // 2
		{1, 2}, // 12
		{0, 2, 3}, // 5
		{1, 2, 3}, // 25
		{4, 9, 0, 5, 1}, // 1026
		{1, -1, 2, 3, 4}, // 247
		{2, -1, 0, -1, 0, 0, 0, 0}, // 22000
	};
	Solution solution;
	for (const auto& values: input) {
		auto root = makeTree(values);
		auto sum = solution.sumNumbers(root);
		cout << root << " => " << sum << endl;
		deleteTree(root);
	}
	return 0;
}
