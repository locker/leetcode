#include <iostream>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Print a tree in the BFS format.
ostream& operator<<(ostream& out, TreeNode* root)
{
	out << '[';
	int null_count = 0;
	queue<TreeNode*> todo;
	todo.push(root);
	while (!todo.empty()) {
		auto node = todo.front();
		todo.pop();
		if (node) {
			todo.push(node->left);
			todo.push(node->right);
			while (null_count > 0) {
				out << ",null";
				--null_count;
			}
			if (node != root)
				out << ',';
			out << node->val;
		} else {
			++null_count;
		}
	}
	out << ']';
	return out;
}

// Create a tree from BFS output. Assume 0 means no child (null).
TreeNode* newTree(const vector<int> values)
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
		if ((val = *it++) > 0) {
			node->left = new TreeNode(val);
			todo.push(node->left);
		}
		if (it != values.end() && (val = *it++) > 0) {
			node->right = new TreeNode(val);
			todo.push(node->right);
		}
	}
	return root;
}

void deleteTree(TreeNode *root)
{
	if (root) {
		deleteTree(root->left);
		deleteTree(root->right);
		delete root;
	}
}

class Solution {
public:
	TreeNode* addOneRow(TreeNode* root, int v, int d) {
		if (d == 1) {
			auto new_root = new TreeNode(v);
			new_root->left = root;
			return new_root;
		}
		vector<TreeNode*> todo;
		todo.push_back(root);
		for (int i = 0; i < d - 2; ++i) {
			vector<TreeNode*> next;
			for (auto node: todo) {
				if (node->left)
					next.push_back(node->left);
				if (node->right)
					next.push_back(node->right);
			}
			todo.clear();
			swap(todo, next);
		}
		for (auto node: todo) {
			auto new_left = new TreeNode(v);
			new_left->left = node->left;
			node->left = new_left;
			auto new_right = new TreeNode(v);
			new_right->right = node->right;
			node->right = new_right;
		}
		return root;
	}
};

int main()
{
	tuple<vector<int>, int, int> input[] = {
		{{}, 1, 1}, // [1]
		{{5}, 1, 1}, // [5, 1]
		{{5, 0, 4}, 1, 2}, // [5, 1, 1, null, null, null, 4]
		{{4, 2, 0, 3, 1}, 1, 3}, // [4, 2, null, 1, 1, 3, null, null, 1]
		{{4, 2, 6, 3, 1, 5}, 1, 2}, // [4, 1, 1, 2, null, null, 6, 3, 1, 5]
	};
	Solution solution;
	for (auto& t: input) {
		auto root = newTree(get<0>(t));
		auto v = get<1>(t);
		auto d = get<2>(t);
		cout << "Input: " << root << ", v = " << v << ", d = " << d << endl;
		root = solution.addOneRow(root, v, d);
		cout << "Output: " << root << endl;
		deleteTree(root);
	}
	return 0;
}
