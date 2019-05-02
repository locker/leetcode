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

// Print a tree level by level (BFS).
ostream& operator<<(ostream& out, const TreeNode* root)
{
	out << '[';
	queue<const TreeNode*> todo;
	todo.push(root);
	int null_count = 0;
	while (!todo.empty()) {
		const TreeNode* node = todo.front();
		todo.pop();
		if (node) {
			if (node != root)
				cout << ',';
			todo.push(node->left);
			todo.push(node->right);
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

// Recursively clone a tree (pre-order DFS).
TreeNode* cloneTree(TreeNode* root)
{
	if (!root)
		return nullptr;
	auto new_root = new TreeNode(root->val);
	new_root->left = cloneTree(root->left);
	new_root->right = cloneTree(root->right);
	return new_root;
}

// Recursively delete a tree (post-order DFS).
void deleteTree(TreeNode* root)
{
	if (root) {
		deleteTree(root->left);
		deleteTree(root->right);
		delete root;
	}
}

class Solution {
	// Array entry n stores all unique binary tree templates
	// of n elements (all tree nodes store 0s).
	vector<vector<TreeNode*>> cache;

	void doFillCache() {
		int size = cache.size();
		cache.emplace_back();
		auto& trees = cache.back();
		for (int left_size = 0; left_size < size; ++left_size) {
			int right_size = size - left_size - 1;
			for (auto left: cache[left_size]) {
				for (auto right: cache[right_size]) {
					auto root = new TreeNode(0);
					root->left = cloneTree(left);
					root->right = cloneTree(right);
					trees.push_back(root);
				}
			}
		}
	}

	// Fill the cache with trees up to the given size.
	void fillCache(size_t size) {
		while (cache.size() <= size)
			doFillCache();
	}

	void doMakeSearchTree(TreeNode* root, int& val) {
		if (!root)
			return;
		doMakeSearchTree(root->left, val);
		root->val = ++val;
		doMakeSearchTree(root->right, val);
	}

	// Turn the given binary tree into a search tree storing
	// values from 1 to the tree size (in-order DFS).
	void makeSearchTree(TreeNode* root) {
		int val = 0;
		doMakeSearchTree(root, val);
	}
public:
	// Initialize the cache with a null tree.
	Solution() {
		cache.emplace_back(1);
	}

	// Clean up the cache.
	~Solution() {
		for (auto trees: cache) {
			for (auto root: trees)
				deleteTree(root);
		}
	}

	vector<TreeNode*> generateTrees(int n) {
		vector<TreeNode*> trees;
		if (n == 0)
			return trees;
		fillCache(n);
		for (auto cached_root: cache[n]) {
			auto root = cloneTree(cached_root);
			makeSearchTree(root);
			trees.push_back(root);
		}
		return trees;
	}
};

int main()
{
	Solution solution;
	for (int n = 0; n <= 5; ++n) {
		cout << "Input: " << n << endl << "Output: [";
		auto trees = solution.generateTrees(n);
		for (auto it = trees.begin(); it != trees.end(); ++it) {
			if (it != trees.begin())
				cout << ',';
			cout << endl << "  " << *it;
			deleteTree(*it);
		}
		cout << endl << ']' << endl << endl;
	}
	return 0;
}
