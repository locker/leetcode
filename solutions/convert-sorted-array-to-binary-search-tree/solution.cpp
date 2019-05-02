#include <iostream>
#include <queue>
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

// Print a tree level by level (BFS).
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

// Delete a tree (post-order DFS).
void deleteTree(TreeNode* root)
{
	if (root) {
		deleteTree(root->left);
		deleteTree(root->right);
		delete root;
	}
}

class Solution {
	template<typename iterator_type>
	TreeNode* doSortedArrayToBST(iterator_type begin, iterator_type end) {
		if (begin == end)
			return nullptr;
		auto mid = begin + (end - begin) / 2;
		auto root = new TreeNode(*mid);
		root->left = doSortedArrayToBST(begin, mid);
		root->right = doSortedArrayToBST(mid + 1, end);
		return root;
	}
public:
	TreeNode* sortedArrayToBST(const vector<int>& nums) {
		return doSortedArrayToBST(nums.begin(), nums.end());
	}
};

int main()
{
	vector<int> input[] = {
		{},
		{1},
		{-4, 4},
		{-1, 0, 10},
		{-2, -1, 3, 5},
		{-10, -3, 0, 5, 9},
	};
	Solution solution;
	for (const auto& nums: input) {
		auto tree = solution.sortedArrayToBST(nums);
		cout << nums << " => " << tree << endl;
		deleteTree(tree);
	}
	return 0;
}
