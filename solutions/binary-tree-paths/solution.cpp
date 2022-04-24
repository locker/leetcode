#include <iostream>
#include <optional>
#include <queue>
#include <set>
#include <stack>
#include <string>
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

class Solution {
public:
	vector<string> binaryTreePaths(TreeNode* root) {
		vector<string> paths;
		string path;
		stack<pair<TreeNode*, bool>> todo;
		if (root)
			todo.emplace(root, false);
		while (!todo.empty()) {
			auto [node, visited] = todo.top();
			todo.pop();
			if (!visited) {
				if (!path.empty())
					path.append("->");
				path.append(to_string(node->val));
				if (!node->left && !node->right)
					paths.push_back(path);
				todo.emplace(node, true);
				if (node->left)
					todo.emplace(node->left, false);
				if (node->right)
					todo.emplace(node->right, false);
			} else {
				size_t pos = path.rfind("->");
				if (pos == string::npos)
					pos = 0;
				path.resize(pos);
			}
		}
		return paths;
	}
};

int main()
{
	const pair<vector<optional<int>>, vector<string>> test_data[] = {
		{{}, {}},
		{{1}, {"1"}},
		{{-1}, {"-1"}},
		{{1, 2}, {"1->2"}},
		{{10, 20}, {"10->20"}},
		{{-10, -20}, {"-10->-20"}},
		{{1, nullopt, 2}, {"1->2"}},
		{{1, 2, 3}, {"1->2", "1->3"}},
		{{1, 2, 3, nullopt, 5}, {"1->2->5", "1->3"}},
	};
	bool success = true;
	Solution solution;
	for (const auto& [values, expected] : test_data) {
		TreeNode* root = newTree(values);
		auto result = solution.binaryTreePaths(root);
		cout << values << " -> " << result << endl;
		set<string> result_set(result.begin(), result.end());
		set<string> expected_set(expected.begin(), expected.end());
		if (result_set != expected_set) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
		deleteTree(root);
	}
	return success ? 0 : 1;
}
