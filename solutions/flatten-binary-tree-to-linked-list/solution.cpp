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
	void flatten(TreeNode* root) {
		TreeNode* curr = root;
		while (curr) {
			if (!curr->left) {
				curr = curr->right;
				continue;
			}
			auto p = curr->left;
			while (p->right)
				p = p->right;
			p->right = curr->right;
			curr->right = curr->left;
			curr->left = nullptr;
		}
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
		{1, 2, 4, 0, 3},
		{1, 2, 3, 0, 0, 4},
		{1, 2, 5, 3, 4, 0, 6},
	};
	Solution solution;
	for (const auto& values: input) {
		auto root = makeTree(values);
		cout << root << " => ";
		solution.flatten(root);
		cout << root << endl;
		deleteTree(root);
	}
	return 0;
}
