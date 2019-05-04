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
	// Return the number of paths starting at the root node
	// and summing up to the given value.
	int pathSumFrom(const TreeNode* root, int sum) {
		if (!root)
			return 0;
		int count = 0;
		if (root->val == sum)
			++count;
		count += pathSumFrom(root->left, sum - root->val);
		count += pathSumFrom(root->right, sum - root->val);
		return count;
	}
public:
	int pathSum(const TreeNode* root, int sum) {
		if (!root)
			return 0;
		int count = 0;
		count += pathSumFrom(root, sum);
		count += pathSum(root->left, sum);
		count += pathSum(root->right, sum);
		return count;
	}
};

int main()
{
	pair<vector<int>, int> input[] = {
		{{}, 0}, // 0
		{{1}, 1}, // 1
		{{1, 2}, 4}, // 0
		{{1, 2, 3}, 4}, // 1
		{{1, 0, 2, 3, 4, 1}, 7}, // 2
		{{1, 0, 3, 4, 0, 6, 7}, 14}, // 2
		{{1, 2, 3, 0, 0, -1, 0, 1}, 3}, // 4
		{{1, 9, 2, 0, 0, 3, 0, 4, 5}, 10}, // 3
		{{1, 0, 2, 0, 3, 0, 4, 0, 5}, 3}, // 2
		{{3, 0, -1, 0, 1, 0, -1, 0, 1}, 3}, // 3
		{{10, 5, -3, 3, 2, 0, 11, 3, -2, 0, 1}, 8} // 3
	};
	Solution solution;
	for (const auto& p: input) {
		auto root = makeTree(p.first);
		auto sum = p.second;
		auto count = solution.pathSum(root, sum);
		cout << root << ", " << sum << " => " << count << endl;
		deleteTree(root);
	}
	return 0;
}
