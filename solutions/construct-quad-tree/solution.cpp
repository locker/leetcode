#include <iostream>
#include <optional>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

namespace {

template<typename T, typename U>
ostream& operator<<(ostream& out, const pair<T, U>& p)
{
	return out << '[' << p.first << ',' << p.second << ']';
}

template<typename T>
ostream& operator<<(ostream& out, const optional<T>& o)
{
	if (o.has_value())
		return out << o.value();
	else
		return out << "null";
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
	out << ']';
	return out;
}


class Node {
public:
	bool val;
	bool isLeaf;
	Node* topLeft;
	Node* topRight;
	Node* bottomLeft;
	Node* bottomRight;

	Node() {
		val = false;
		isLeaf = false;
		topLeft = NULL;
		topRight = NULL;
		bottomLeft = NULL;
		bottomRight = NULL;
	}

	Node(bool _val, bool _isLeaf) {
		val = _val;
		isLeaf = _isLeaf;
		topLeft = NULL;
		topRight = NULL;
		bottomLeft = NULL;
		bottomRight = NULL;
	}

	Node(bool _val, bool _isLeaf,
	     Node* _topLeft, Node* _topRight,
	     Node* _bottomLeft, Node* _bottomRight) {
		val = _val;
		isLeaf = _isLeaf;
		topLeft = _topLeft;
		topRight = _topRight;
		bottomLeft = _bottomLeft;
		bottomRight = _bottomRight;
	}
};

void qtreeDelete(Node* root)
{
	queue<Node*> todo;
	todo.push(root);
	while (!todo.empty()) {
		Node* node = todo.front();
		todo.pop();
		if (node) {
			todo.push(node->topLeft);
			todo.push(node->topRight);
			todo.push(node->bottomLeft);
			todo.push(node->bottomRight);
			delete node;
		}
	}
}

vector<optional<pair<int, int>>> qtreeValues(Node* root)
{
	vector<optional<pair<int, int>>> values;
	queue<Node*> todo;
	todo.push(root);
	while (!todo.empty()) {
		Node* node = todo.front();
		todo.pop();
		if (node) {
			values.emplace_back(make_pair(node->isLeaf, node->val));
			todo.push(node->topLeft);
			todo.push(node->topRight);
			todo.push(node->bottomLeft);
			todo.push(node->bottomRight);
		} else {
			values.emplace_back(nullopt);
		}
	}
	while (!values.empty() && !values.back().has_value())
		values.pop_back();
	return values;
}

class Solution {
private:
	Node* doConstruct(const vector<vector<int>>& grid, int i0, int j0, int n) {
		if (n == 1)
			return new Node(grid[i0][j0], true);
		n /= 2;
		Node* topLeft = doConstruct(grid, i0, j0, n);
		Node* topRight = doConstruct(grid, i0, j0 + n, n);
		Node* bottomLeft = doConstruct(grid, i0 + n, j0, n);
		Node* bottomRight = doConstruct(grid, i0 + n, j0 + n, n);
		if (topLeft->isLeaf && topRight->isLeaf &&
		    bottomLeft->isLeaf && bottomRight->isLeaf &&
		    topLeft->val == topRight->val &&
		    bottomLeft->val == bottomRight->val &&
		    topLeft->val == bottomLeft->val) {
			delete topLeft;
			delete topRight;
			delete bottomLeft;
			delete bottomRight;
			return new Node(grid[i0][j0], true);
		}
		return new Node(true, false, topLeft, topRight, bottomLeft, bottomRight);
	}
public:
	Node* construct(const vector<vector<int>>& grid) {
		return doConstruct(grid, 0, 0, grid.size());
	}
};

} // namespace

int main()
{
	const tuple<vector<vector<int>>,
		    vector<optional<pair<int, int>>>> test_data[] = {
		{
			{{0}},
			{{{1, 0}}},
		},
		{
			{
				{0,1},
				{1,0},
			},
			{
				{{0,1}},
				{{1,0}},{{1,1}},{{1,1}},{{1,0}},
			},
		},
		{
			{
				{1,1,1,1,0,0,0,0},
				{1,1,1,1,0,0,0,0},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,0,0,0,0},
				{1,1,1,1,0,0,0,0},
				{1,1,1,1,0,0,0,0},
				{1,1,1,1,0,0,0,0},
			},
			{
				{{0,1}},
				{{1,1}},{{0,1}},{{1,1}},{{1,0}},
				nullopt,nullopt,nullopt,nullopt,{{1,0}},{{1,0}},{{1,1}},{{1,1}},
			},
		},
	};
	bool success = true;
	Solution solution;
	for (const auto& [grid, expected] : test_data) {
		Node* qtree = solution.construct(grid);
		auto result = qtreeValues(qtree);
		qtreeDelete(qtree);
		cout << grid << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
