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

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			cout << ',';
		cout << *it;
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
				cout << ',';
			while (null_count > 0) {
				cout << "null,";
				--null_count;
			}
			cout << node->val;
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
	vector<int> postorderTraversal(const TreeNode* root) {
		vector<int> result;
		const TreeNode* curr = root;
		const TreeNode* prev = nullptr;
		stack<const TreeNode*> todo;
		while (curr || !todo.empty()) {
			if (!curr) {
				curr = todo.top();
				todo.pop();
			}
			if ((curr->right && curr->right == prev) ||
			    (!curr->right && (!curr->left ||
					      curr->left == prev))) {
				result.push_back(curr->val);
				prev = curr;
				curr = nullptr;
			} else if (curr->right && (!curr->left ||
						   curr->left == prev)) {
				todo.push(curr);
				prev = curr;
				curr = curr->right;
			} else {
				todo.push(curr);
				prev = curr;
				curr = curr->left;
			}
		}
		return result;
	}
};

int main()
{
	vector<int> input[] = {
		{},
		{1},
		{1,2},
		{1,2,3},
		{1,0,2,3},
		{1,0,2,0,3},
		{1,0,2,3,4,0,5},
		{1,2,3,4,5,6,7,8},
		{1,2,3,0,4,0,5,0,6},
	};
	Solution solution;
	for (const auto& values: input) {
		auto root = makeTree(values);
		cout << root << " => " <<
			solution.postorderTraversal(root) << endl;
		deleteTree(root);
	}
	return 0;
}
