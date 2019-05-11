#include <iostream>
#include <queue>
#include <unordered_map>
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

void deleteTree(TreeNode* root)
{
	if (root) {
		deleteTree(root->left);
		deleteTree(root->right);
		delete root;
	}
}

class Solution {
	typedef vector<int>::const_iterator iterator;

	// Map: a tree node value => position in the inorder array.
	unordered_map<int, iterator> inorder_pos_by_val;

	// Recursively build a tree from preorder and inorder arrays
	// given as boundary iterators.
	TreeNode* doBuildTree(iterator preorder_begin,
			      iterator inorder_begin, iterator inorder_end)
	{
		if (inorder_begin == inorder_end)
			return nullptr;

		// The first entry of preorder array is the tree root.
		int val = *preorder_begin;
		auto root = new TreeNode(val);

		// Divide inorder array in two parts by the root node.
		// The first part is for the left subtree, the second
		// part is for the right subtree.
		auto inorder_pos = inorder_pos_by_val[val];
		root->left = doBuildTree(preorder_begin + 1,
					 inorder_begin, inorder_pos);
		root->right = doBuildTree(preorder_begin + 1 +
					  (inorder_pos - inorder_begin),
					  inorder_pos + 1, inorder_end);
		return root;
	}
public:
	TreeNode* buildTree(const vector<int>& preorder,
			    const vector<int>& inorder) {
		for (auto it = inorder.begin(); it != inorder.end(); ++it)
			inorder_pos_by_val[*it] = it;
		auto root = doBuildTree(preorder.begin(),
					inorder.begin(), inorder.end());
		inorder_pos_by_val.clear();
		return root;
	}
};

int main()
{
	pair<vector<int>, vector<int>> input[] = {
		{{}, {}}, // []
		{{1}, {1}}, // [1]
		{{1, 2}, {2, 1}}, // [1, 2]
		{{1, 2}, {1, 2}}, // [1, null, 2]
		{{1, 2, 3}, {2, 1, 3}}, // [1, 2, 3]
		{{1, 2, 3}, {3, 2, 1}}, // [1, 2, null, 3]
		{{1, 2, 3}, {2, 3, 1}}, // [1, 2, null, null, 3]
		{{1, 2, 3}, {1, 3, 2}}, // [1, null, 2, 3]
		{{1, 2, 3}, {1, 2, 3}}, // [1, null, 2, null, 3]
		{{3, 9, 20, 15, 7}, {9, 3, 15, 20, 7}}, // [3, 9, 20, null, null, 15, 7]
	};
	Solution solution;
	for (const auto& p: input) {
		const auto& preorder = p.first;
		const auto& inorder = p.second;
		auto root = solution.buildTree(preorder, inorder);
		cout << "preorder = " << preorder << ", inorder = " <<
			inorder << " => " << root << endl;
		deleteTree(root);
	}
	return 0;
}
