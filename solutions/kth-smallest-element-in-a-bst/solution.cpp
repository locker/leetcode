#include <iostream>
#include <optional>
#include <queue>
#include <stack>
#include <tuple>
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
	int kthSmallest(TreeNode* root, int k) {
		int n_visited = 0;
		stack<pair<TreeNode*, bool>> todo;
		todo.emplace(root, false);
		while (!todo.empty()) {
			auto [node, visited] = todo.top();
			todo.pop();
			if (visited) {
				++n_visited;
				if (n_visited == k)
					return node->val;
			} else if (node != nullptr) {
				todo.emplace(node->right, false);
				todo.emplace(node, true);
				todo.emplace(node->left, false);
			}
		}
		return 0;
	}
};

int main()
{
	const tuple<vector<optional<int>>, int, int> test_data[] = {
		{{10}, 1, 1},
		{{20, 10}, 1, 10},
		{{20, 10}, 2, 20},
		{{10, nullopt, 20}, 1, 10},
		{{30, 10, 40, nullopt, 20}, 1, 10},
		{{30, 10, 40, nullopt, 20}, 2, 20},
		{{30, 10, 40, nullopt, 20}, 3, 30},
		{{30, 10, 40, nullopt, 20}, 4, 40},
		{{50, 30, 60, 20, 40, nullopt, nullopt, 10}, 1, 10},
		{{50, 30, 60, 20, 40, nullopt, nullopt, 10}, 2, 20},
		{{50, 30, 60, 20, 40, nullopt, nullopt, 10}, 3, 30},
		{{50, 30, 60, 20, 40, nullopt, nullopt, 10}, 4, 40},
		{{50, 30, 60, 20, 40, nullopt, nullopt, 10}, 5, 50},
		{{50, 30, 60, 20, 40, nullopt, nullopt, 10}, 6, 60},
	};
	bool success = true;
	Solution solution;
	for (const auto& [values, k, expected] : test_data) {
		TreeNode* root = newTree(values);
		int result = solution.kthSmallest(root, k);
		cout << values << ", k=" << k << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
		deleteTree(root);
	}
	return success ? 0 : 1;
}
