#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ',';
		out << *it;
	}
	out << ']';
	return out;
}

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
	vector<vector<int>> zigzagLevelOrder(const TreeNode* root) {
		if (!root)
			return {};
		vector<vector<int>> levels;
		queue<const TreeNode*> todo;
		todo.push(nullptr);
		todo.push(root);
		while (true) {
			auto node = todo.front();
			todo.pop();
			if (!node) {
				if (!levels.empty() &&
				    levels.size() % 2 == 0)
					reverse(levels.back().begin(),
						levels.back().end());
				if (todo.empty())
					break;
				levels.emplace_back();
				todo.push(nullptr);
				continue;
			}
			levels.back().push_back(node->val);
			if (node->left)
				todo.push(node->left);
			if (node->right)
				todo.push(node->right);
		}
		return levels;
	}
};

int main()
{
	vector<int> input[] = {
		{},
		{1},
		{1, 2},
		{1, 2, 3},
		{1, 0, 2},
		{1, 2, 3, 0, 4},
		{1, 2, 0, 3, 0, 4},
		{1, 2, 3, 0, 0, 4, 0, 5, 6},
		{1, 2, 3, 0, 0, 4, 5, 6, 7},
	};
	Solution solution;
	for (const auto& values: input) {
		auto root = makeTree(values);
		cout << root << " => " <<
			solution.zigzagLevelOrder(root) << endl;
		deleteTree(root);
	}
	return 0;
}
