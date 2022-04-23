#include <algorithm>
#include <iostream>
#include <optional>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const optional<T>& o)
{
	if (o.has_value())
		out << o.value();
	else
		out << "null";
	return out;
}

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	bool first = true;
	for (const auto& x : v) {
		if (!first)
			out << ',';
		out << x;
		first = false;
	}
	out << ']';
	return out;
}

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) :
		val(x), left(left), right(right) {}
};

TreeNode* newTree(const vector<optional<int>> values)
{
	TreeNode* root = nullptr;
	queue<TreeNode**> todo;
	todo.push(&root);
	for (const auto& o : values) {
		TreeNode** pnode = todo.front();
		todo.pop();
		if (o.has_value()) {
			TreeNode* node = new TreeNode(o.value());
			todo.push(&node->left);
			todo.push(&node->right);
			*pnode = node;
		}
	}
	return root;
}

void deleteTree(TreeNode* root)
{
	queue<TreeNode*> todo;
	todo.push(root);
	while (!todo.empty()) {
		TreeNode* node = todo.front();
		todo.pop();
		if (node != nullptr) {
			todo.push(node->left);
			todo.push(node->right);
			delete node;
		}
	}
}

vector<optional<int>> treeValues(const TreeNode* root)
{
	vector<optional<int>> values;
	queue<const TreeNode*> todo;
	todo.push(root);
	while (!todo.empty()) {
		const TreeNode* node = todo.front();
		todo.pop();
		if (node == nullptr) {
			values.push_back(nullopt);
		} else {
			values.push_back(node->val);
			todo.push(node->left);
			todo.push(node->right);
		}
	}
	while (!values.empty() && values.back() == nullopt)
		values.pop_back();
	return values;
}

class Solution {
public:
	TreeNode* invertTree(TreeNode* root) {
		stack<TreeNode*> todo;
		todo.push(root);
		while (!todo.empty()) {
			TreeNode* node = todo.top();
			todo.pop();
			if (node != nullptr) {
				swap(node->left, node->right);
				todo.push(node->left);
				todo.push(node->right);
			}
		}
		return root;
	}
};

int main()
{
	const pair<vector<optional<int>>, vector<optional<int>>> test_data[] = {
		{{}, {}},
		{{1}, {1}},
		{{1, 2}, {1, nullopt, 2}},
		{{1, nullopt, 2}, {1, 2}},
		{{1, 2, 3}, {1, 3, 2}},
		{{4, 2, 7, 1, 3, 6, 9}, {4, 7, 2, 9, 6, 3, 1}},
	};
	bool success = true;
	Solution solution;
	for (const auto& [input, expected] : test_data) {
		TreeNode* root = newTree(input);
		root = solution.invertTree(root);
		const auto result = treeValues(root);
		cout << input << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
		deleteTree(root);
	}
	return success ? 0 : 1;
}
