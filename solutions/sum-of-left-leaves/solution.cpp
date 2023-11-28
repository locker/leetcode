#include <iostream>
#include <optional>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

namespace {

template<typename T>
ostream& operator<<(ostream& out, const vector<optional<T>>& v)
{
	out << '[';
	bool first = true;
	for (const auto& x : v) {
		if (!first)
			out << ',';
		if (x.has_value())
			out << x.value();
		else
			out << "null";
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

struct Tree {
	TreeNode *root;

	Tree(const vector<optional<int>> values) : root(nullptr) {
		queue<TreeNode**> q;
		q.push(&root);
		for (const auto& val : values) {
			if (val.has_value()) {
				auto node = new TreeNode(val.value());
				q.push(&node->left);
				q.push(&node->right);
				*q.front() = node;
			}
			q.pop();
		}
	}

	~Tree() {
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()) {
			auto node = q.front();
			q.pop();
			if (node) {
				q.push(node->left);
				q.push(node->right);
				delete node;
			}
		}
	}

	vector<optional<int>> values() const {
		vector<optional<int>> values;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()) {
			auto node = q.front();
			q.pop();
			if (node) {
				q.push(node->left);
				q.push(node->right);
				values.push_back(node->val);
			} else {
				values.push_back(nullopt);
			}
		}
		while (!values.empty() && !values.back().has_value())
			values.pop_back();
		return values;
	}
};

class Solution {
public:
	int sumOfLeftLeaves(const TreeNode* root) {
		queue<const TreeNode*> q;
		if (root)
			q.push(root);
		int sum = 0;
		while (!q.empty()) {
			auto node = q.front();
			q.pop();
			if (node->left) {
				if (!node->left->left && !node->left->right)
					sum += node->left->val;
				else
					q.push(node->left);
			}
			if (node->right)
				q.push(node->right);
		}
		return sum;
	}
};

} // namespace

int main()
{
	const tuple<vector<optional<int>>, int> test_data[] = {
		{vector<optional<int>>(), 0},
		{{1}, 0},
		{{1, 2, 3}, 2},
		{{1, nullopt, 3}, 0},
		{{3, 9, 20, nullopt, nullopt, 15, 7}, 24},
		{{3, 9, 20, nullopt, nullopt, 15, 7, nullopt, 10}, 9},
	};
	bool success = true;
	Solution solution;
	for (const auto& [values, expected] : test_data) {
		Tree tree(values);
		int result = solution.sumOfLeftLeaves(tree.root);
		cout << tree.values() << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
