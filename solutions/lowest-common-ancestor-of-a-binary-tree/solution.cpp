#include <algorithm>
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
		TreeNode dummy(0);
		TreeNode* prev = &dummy;
		TreeNode* curr = root;

		vector<TreeNode*> path, path_to_p, path_to_q;
		path.push_back(root);

		while (path_to_p.empty() || path_to_q.empty()) {
			if (path_to_p.empty() && curr->val == p->val)
				path_to_p = path;
			if (path_to_q.empty() && curr->val == q->val)
				path_to_q = path;

			TreeNode *next;
			if (curr->left &&
			    prev != curr->left &&
			    prev != curr->right) {
				next = curr->left;
				path.push_back(next);
			} else if (curr->right &&
				   prev != curr->right) {
				next = curr->right;
				path.push_back(next);
			} else {
				path.pop_back();
				next = path.back();
			}
			prev = curr;
			curr = next;
		}

		int len = min(path_to_p.size(), path_to_q.size());
		path_to_p.resize(len);
		path_to_q.resize(len);

		while (path_to_p.back()->val != path_to_q.back()->val) {
			path_to_p.pop_back();
			path_to_q.pop_back();
		}
		return path_to_p.back();
	}
};

int main()
{
	tuple<vector<int>, int, int> input[] = {
		{{1, 2, 3}, 1, 2}, // 1
		{{1, 2, 3}, 2, 3}, // 1
		{{1, 2, 3, 4, 5}, 3, 4}, // 1
		{{1, 2, 3, 4, 5}, 5, 2}, // 2
		{{1, 2, 3, 4, 5}, 4, 5}, // 2
		{{3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4}, 5, 1}, // 3
		{{3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4}, 5, 4}, // 5
		{{3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4}, 7, 6}, // 5
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
