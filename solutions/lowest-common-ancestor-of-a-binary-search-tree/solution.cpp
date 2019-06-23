#include <iostream>
#include <queue>
#include <tuple>
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

// Assume < 0 means no value.
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
		if ((val = *it++) >= 0) {
			node->left = new TreeNode(val);
			todo.push(node->left);
		}
		if (it != values.end() && (val = *it++) >= 0) {
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
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		while (root) {
			if ((p->val <= root->val && q->val >= root->val) ||
			    (p->val >= root->val && q->val <= root->val))
				return root;
			if (p->val >= root->val)
				root = root->right;
			else
				root = root->left;
		}
		return nullptr;
	}
};

int main()
{
	tuple<vector<int>, int, int> input[] = {
		{{2, 1, 3}, 1, 2}, // 2
		{{2, 1, 3}, 1, 3}, // 2
		{{4, 2, 5, 1, 3}, 1, 3}, // 2
		{{4, 2, 5, 1, 3}, 1, 5}, // 4
		{{4, 2, 5, 1, 3}, 3, 4}, // 4
		{{6, 2, 8, 0, 4, 7, 9, -1, -1, 3, 5}, 0, 5}, // 2
		{{6, 2, 8, 0, 4, 7, 9, -1, -1, 3, 5}, 2, 4}, // 2
		{{6, 2, 8, 0, 4, 7, 9, -1, -1, 3, 5}, 2, 8}, // 6
	};
	Solution solution;
	for (const auto& t: input) {
		auto root = makeTree(get<0>(t));
		auto p = new TreeNode(get<1>(t));
		auto q = new TreeNode(get<2>(t));
		auto ancestor = solution.lowestCommonAncestor(root, p, q);
		cout << "Input: root = " << root <<
			", p = " << p->val << ", q = " << q->val << endl <<
			"Output: " << ancestor->val << endl;
		delete p;
		delete q;
		deleteTree(root);
	}
	return 0;
}
