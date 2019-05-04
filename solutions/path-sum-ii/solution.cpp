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
	vector<vector<int>> pathSum(const TreeNode* root, int sum) {
		if (!root)
			return {};
		vector<vector<int>> result;
		vector<const TreeNode*> path;
		path.push_back(root);
		int path_sum = root->val;
		const TreeNode* prev = nullptr;
		while (!path.empty()) {
			auto node = path.back();
			auto left = node->left;
			auto right = node->right;
			if (!left && !right && path_sum == sum) {
				result.emplace_back();
				for (auto n: path)
					result.back().push_back(n->val);
			}
			if ((right && right == prev) ||
			    (!right && (!left || left == prev))) {
				path.pop_back();
				path_sum -= node->val;
			} else if (right && (!left || left == prev)) {
				path.push_back(right);
				path_sum += right->val;
			} else {
				path.push_back(left);
				path_sum += left->val;
			}
			prev = node;
		}
		return result;
	}
};

int main()
{
	pair<vector<int>, int> input[] = {
		{{}, 0},
		{{1}, 1},
		{{1, 2}, 4},
		{{1, 2, 3}, 4},
		{{1, 0, 2, 3, 4, 1}, 7},
		{{1, 0, 3, 4, 0, 5, 6}, 14},
		{{1, 2, 3, 0, 0, 4, 0, 5}, 15},
		{{1, 9, 2, 0, 0, 3, 0, 4, 5}, 10},
		{{5, 4, 8, 11, 0, 13, 4, 7, 2, 0, 0, 5, 1}, 22},
	};
	Solution solution;
	for (const auto& p: input) {
		auto root = makeTree(p.first);
		auto sum = p.second;
		auto paths = solution.pathSum(root, sum);
		cout << root << ", " << sum << " => " << paths << endl;
		deleteTree(root);
	}
	return 0;
}
