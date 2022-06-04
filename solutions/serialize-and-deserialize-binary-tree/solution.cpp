#include <cassert>
#include <iostream>
#include <optional>
#include <queue>
#include <string>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const optional<T>& x) {
	if (x.has_value())
		return out << x.value();
	else
		return out << "null";
}

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v) {
	out << '[';
	bool first = true;
	for (const auto& x : v) {
		if (!first)
			out << ',';
		out << x;
		first = false;
	}
	out << ']';
	return out;
}

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* newTree(const vector<optional<int>>& values) {
	TreeNode* root = nullptr;
	queue<TreeNode**> todo;
	todo.push(&root);
	for (auto x : values) {
		TreeNode** pnode = todo.front();
		todo.pop();
		if (x.has_value()) {
			*pnode = new TreeNode(x.value());
			todo.push(&(*pnode)->left);
			todo.push(&(*pnode)->right);
		}
	}
	return root;
}

void deleteTree(TreeNode* root) {
	queue<TreeNode*> todo;
	todo.push(root);
	while (!todo.empty()) {
		TreeNode* node = todo.front();
		todo.pop();
		if (node) {
			todo.push(node->left);
			todo.push(node->right);
			delete node;
		}
	}
}

vector<optional<int>> treeValues(const TreeNode* root) {
	int count = 0;
	vector<optional<int>> values;
	queue<const TreeNode*> todo;
	todo.push(root);
	while (!todo.empty()) {
		const TreeNode* node = todo.front();
		todo.pop();
		if (node) {
			values.push_back(node->val);
			count = values.size();
			todo.push(node->left);
			todo.push(node->right);
		} else {
			values.push_back(nullopt);
		}
	}
	values.resize(count);
	return values;
}

class Codec {
private:
	static constexpr int min_val = -1000;
	static constexpr int max_val = 1000;
public:
	// Encodes a tree to a single string.
	string serialize(const TreeNode* root) {
		int size = 0;
		string data;
		queue<const TreeNode*> todo;
		todo.push(root);
		while (!todo.empty()) {
			const TreeNode* node = todo.front();
			todo.pop();
			data.resize(data.size() + 2);
			unsigned char* p =
				reinterpret_cast<unsigned char*>(
					data.data() + data.size() - 2);
			unsigned int val = 0;
			if (node) {
				assert(node->val >= min_val &&
				       node->val <= max_val);
				val = node->val - min_val + 1;
				todo.push(node->left);
				todo.push(node->right);
				size = data.size();
			}
			*p = val & ((1 << 8) - 1);
			*(p + 1) = val >> 8;
		}
		data.resize(size);
		return data;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(const string& data) {
		const int size = data.size();
		assert(size % 2 == 0);
		TreeNode* root = nullptr;
		queue<TreeNode**> todo;
		todo.push(&root);
		for (int i = 0; i < size; i += 2) {
			const unsigned char *p =
				reinterpret_cast<const unsigned char*>(
					data.data() + i);
			unsigned int val = *p | (*(p + 1) << 8);
			TreeNode** pnode = todo.front();
			todo.pop();
			if (val != 0) {
				*pnode = new TreeNode(val + min_val - 1);
				todo.push(&(*pnode)->left);
				todo.push(&(*pnode)->right);
			}
		}
		return root;
	}
};

int main()
{
	const vector<optional<int>> test_data[] = {
		{},
		{1},
		{1, 2},
		{1, nullopt, 2},
		{1, 2, 3, nullopt, nullopt, 4, 5},
		{1, 2, 3, nullopt, nullopt, 4, 5, nullopt, 6, nullopt, 7},
	};
	bool success = true;
	Codec codec;
	for (const auto& values : test_data) {
		TreeNode* root = newTree(values);
		cout << values << endl;
		string bin = codec.serialize(root);
		TreeNode* copy = codec.deserialize(bin);
		auto values_copy = treeValues(copy);
		if (values != values_copy) {
			cout << "  ERROR: got " << values_copy << endl;
			success = false;
		}
		deleteTree(copy);
		deleteTree(root);
	}
	return success ? 0 : 1;
}
