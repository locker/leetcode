#include <iostream>
#include <queue>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) :
		val(x), left(left), right(right) {}
};

TreeNode* newTree(int count)
{
	TreeNode* root = nullptr;
	queue<TreeNode**> nodes;
	nodes.push(&root);
	for (int i = 0; i < count; ++i) {
		TreeNode** p = nodes.front();
		nodes.pop();
		*p = new TreeNode(i + 1);
		nodes.push(&(*p)->left);
		nodes.push(&(*p)->right);
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
	int countNodes(TreeNode* root) {
		if (!root)
			return 0;
		int height = 0;
		for (TreeNode* node = root; node; node = node->left)
			++height;
		int level = 0;
		int count = 0;
		while (height > 1) {
			count += 1 << level;
			++level;
			--height;
			int right_height = 0;
			for (TreeNode* node = root->right; node; node = node->left)
				++right_height;
			if (right_height == height) {
				count += (1 << (height - 1));
				root = root->right;
			} else {
				root = root->left;
			}
		}
		return count + 1;
	}
};

int main()
{
	bool success = true;
	Solution solution;
	for (int count = 0; count <= 100; ++count) {
		TreeNode* root = newTree(count);
		int result = solution.countNodes(root);
		if (result != count) {
			cout << "ERROR: expected " << count <<
				", got " << result << endl;
			success = false;
		}
		deleteTree(root);
	}
	if (success) {
		cout << "SUCCESS" << endl;
		return 0;
	}
	return 1;
}
