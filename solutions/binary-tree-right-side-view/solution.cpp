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
			if (node != root)
				out << ',';
			while (null_count > 0) {
				out << "null,";
				--null_count;
			}
			out << node->val;
			todo.push(node->left);
			todo.push(node->right);
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
	vector<int> rightSideView(const TreeNode* root) {
		vector<int> result;

		// Iterate over tree nodes using BFS.
		// Append the last node at each level
		// to the result.
		vector<const TreeNode*> todo, todo_next;
		if (root)
			todo.push_back(root);

		while (!todo.empty()) {
			const TreeNode* last = nullptr;
			for (auto node: todo) {
				if (node->left)
					todo_next.push_back(node->left);
				if (node->right)
					todo_next.push_back(node->right);
				last = node;
			}
			result.push_back(last->val);
			swap(todo, todo_next);
			todo_next.clear();
		}
		return result;
	}
};

int main()
{
	vector<int> input[] = {
		{}, // []
		{1}, // [1]
		{1, 2}, // [1, 2]
		{1, 2, 3}, // [1, 3]
		{1, 0, 2}, // [1, 2]
		{1, 0, 2, 0, 3}, // [1, 2, 3]
		{1, 2, 3, 0, 5, 0, 4}, // [1, 3, 4]
		{1, 2, 3, 0, 4, 5, 0, 6}, // [1, 3, 5, 6]
	};
	Solution solution;
	for (const auto values: input) {
		auto root = makeTree(values);
		cout << root << " => " << solution.rightSideView(root) << endl;
		deleteTree(root);
	}
	return 0;
}
