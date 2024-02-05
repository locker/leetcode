#include <algorithm>
#include <iostream>
#include <optional>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

namespace {

template<typename T>
ostream& operator<<(ostream& out, const optional<T>& v)
{
	if (v.has_value())
		out << v.value();
	else
		out << "null";
	return out;
}

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	bool first = true;
	for (const auto& x : v) {
		if (!first)
			out << ',';
		out << x;
		first = false;
	}
	return out << ']';
}

class Node {
public:
	int val;
	vector<Node*> children;

	Node() {}

	Node(int _val) {
		val = _val;
	}

	Node(int _val, vector<Node*> _children) {
		val = _val;
		children = _children;
	}
};

class Tree {
public:
	Node *root;

	Tree(const vector<optional<int>>& values) {
		if (values.empty()) {
			root = nullptr;
			return;
		}
		root = new Node(values[0].value());
		queue<Node*> todo;
		todo.push(root);
		for (int i = 2; i < static_cast<int>(values.size()); ++i) {
			if (!values[i].has_value()) {
				todo.pop();
				continue;
			}
			Node* node = new Node(values[i].value());
			todo.push(node);
			Node* parent = todo.front();
			parent->children.push_back(node);
		}
	}

	~Tree() {
		queue<Node*> todo;
		if (root)
			todo.push(root);
		while (!todo.empty()) {
			Node *node = todo.front();
			todo.pop();
			for (Node* child : node->children)
				todo.push(child);
			delete node;
		}
	}
};

class Solution {
public:
	vector<vector<int>> levelOrder(Node* root) {
		vector<vector<int>> result;
		vector<Node*> level;
		if (root)
			level.push_back(root);
		while (!level.empty()) {
			result.emplace_back();
			vector<Node*> next_level;
			for (Node* node : level) {
				for (Node* child : node->children)
					next_level.push_back(child);
				result.back().push_back(node->val);
			}
			swap(level, next_level);
		}
		return result;
	}
};

} // namespace

int main()
{
	const tuple<vector<optional<int>>, vector<vector<int>>> test_data[] = {
		{{}, {}},
		{
			{1, nullopt, 3, 2, 4, nullopt, 5, 6},
			{{1}, {3, 2, 4}, {5, 6}},
		},
		{
			{
				1, nullopt, 2, 3, 4, 5, nullopt,
				nullopt, 6, 7, nullopt, 8, nullopt,
				9, 10, nullopt, nullopt, 11, nullopt,
				12, nullopt, 13, nullopt, nullopt, 14,
			},
			{
				{1}, {2, 3, 4, 5}, {6, 7, 8, 9, 10},
				{11, 12, 13}, {14},
			},
		},
	};
	bool success = true;
	Solution solution;
	for (const auto& [input, expected] : test_data) {
		Tree tree(input);
		auto result = solution.levelOrder(tree.root);
		cout << input << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
