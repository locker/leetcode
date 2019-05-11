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
	typedef vector<int>::const_reverse_iterator riterator;

	// Map: a tree node value => position in the inorder array.
	unordered_map<int, iterator> inorder_pos_by_val;

	// Recursively build a tree from inorder and postorder arrays
	// given as boundary iterators.
	TreeNode* doBuildTree(iterator inorder_begin, iterator inorder_end,
			      riterator postorder_rbegin)
	{
		if (inorder_begin == inorder_end)
			return nullptr;

		// The last entry of postorder array is the tree root.
		int val = *postorder_rbegin;
		auto root = new TreeNode(val);

		// Divide inorder array in two parts by the root node.
		// The first part is for the left subtree, the second
		// part is for the right subtree.
		//
		// Note in postorder array left and right are reversed,
		// because we use reverse iterator.
		//
		auto inorder_pos = inorder_pos_by_val[val];
		root->left = doBuildTree(inorder_begin, inorder_pos,
					 postorder_rbegin +
					 (inorder_end - inorder_pos));
		root->right = doBuildTree(inorder_pos + 1, inorder_end,
					  postorder_rbegin + 1);
		return root;
	}
public:
	TreeNode* buildTree(const vector<int>& inorder,
			    const vector<int>& postorder) {
		for (auto it = inorder.begin(); it != inorder.end(); ++it)
			inorder_pos_by_val[*it] = it;
		auto root = doBuildTree(inorder.begin(), inorder.end(),
					postorder.rbegin());
		inorder_pos_by_val.clear();
		return root;
	}
};

int main()
{
	pair<vector<int>, vector<int>> input[] = {
		{{}, {}}, // []
		{{1}, {1}}, // [1]
		{{2, 1}, {2, 1}}, // [1, 2]
		{{1, 2}, {2, 1}}, // [1, null, 2]
		{{2, 1, 3}, {2, 3, 1}}, // [1, 2, 3]
		{{3, 2, 1}, {3, 2, 1}}, // [1, 2, null, 3]
		{{2, 3, 1}, {3, 2, 1}}, // [1, 2, null, null, 3]
		{{1, 3, 2}, {3, 2, 1}}, // [1, null, 2, 3]
		{{1, 2, 3}, {3, 2, 1}}, // [1, null, 2, null, 3]
		{{9, 3, 15, 20, 7}, {9, 15, 7, 20, 3}}, // [3, 9, 20, null, null, 15, 7]
	};
	Solution solution;
	for (const auto& p: input) {
		const auto& inorder = p.first;
		const auto& postorder = p.second;
		auto root = solution.buildTree(inorder, postorder);
		cout << "inorder = " << inorder << ", postorder = " <<
			postorder << " => " << root << endl;
		deleteTree(root);
	}
	return 0;
}
