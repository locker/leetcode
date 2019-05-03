#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
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
	bool isSameTree(const TreeNode* tree1, const TreeNode* tree2) {
		stack<pair<const TreeNode*, const TreeNode*>> todo;
		todo.emplace(tree1, tree2);
		while (!todo.empty()) {
			const auto& p = todo.top();
			const auto node1 = p.first;
			const auto node2 = p.second;
			todo.pop();
			if (!!node1 != !!node2)
				return false;
			if (node1) {
				if (node1->val != node2->val)
					return false;
				todo.emplace(node1->left, node2->left);
				todo.emplace(node1->right, node2->right);
			}
		}
		return true;
	}
};

int main()
{
	pair<vector<int>, vector<int>> input[] = {
		{{}, {}}, // true
		{{}, {1}}, // false
		{{1}, {1}}, // true
		{{1,2}, {1,0,2}}, // false
		{{1,2,3}, {1,2,3}}, // true
		{{1,2,3}, {1,2,4}}, // false
		{{1,2,0,3}, {1,2,0,3}}, // true
		{{1,0,3,4,5}, {1,2,3,0,0,4,5}}, // false
		{{1,2,0,3,4,5,6}, {1,2,0,3,4,5,6}}, // true
		{{1,2,3,4,5,6,7,0,8}, {1,2,3,4,5,6,7}}, //false
	};
	Solution solution;
	for (const auto& p: input) {
		TreeNode* tree1 = makeTree(p.first);
		TreeNode* tree2 = makeTree(p.second);
		bool same = solution.isSameTree(tree1, tree2);
		cout << tree1 << (same ? " == " : " != ") << tree2 << endl;
		deleteTree(tree1);
		deleteTree(tree2);
	}
	return 0;
}
