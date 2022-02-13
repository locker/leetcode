#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
#include <utility>

using namespace std;

template<typename T>
ostream& operator<<(ostream& o, const vector<T> v) {
	o << '[';
	bool first = true;
	for (const auto& x : v) {
		if (!first)
			o << ',';
		o << x;
		first = false;
	}
	o << ']';
	return o;
}

class Node {
public:
	int val;
	vector<Node*> neighbors;
	Node() {
		val = 0;
		neighbors = vector<Node*>();
	}
	Node(int _val) {
		val = _val;
		neighbors = vector<Node*>();
	}
	Node(int _val, vector<Node*> _neighbors) {
		val = _val;
		neighbors = _neighbors;
	}
};

Node *newGraph(const vector<vector<int>>& adj_list) {
	int count = adj_list.size();
	if (count == 0)
		return nullptr;
	vector<Node*> nodes(count);
	for (int i = 0; i < count; ++i)
		nodes[i] = new Node(i + 1);
	for (int i = 0; i < count; ++i) {
		for (int j : adj_list[i]) {
			nodes[i]->neighbors.push_back(nodes[j - 1]);
		}
	}
	return nodes[0];
}

vector<Node*> getNodes(Node* graph) {
	vector<Node*> nodes;
	queue<Node*> todo;
	if (graph)
		todo.push(graph);
	while (!todo.empty()) {
		Node* it = todo.front();
		todo.pop();
		int i = it->val - 1;
		if (i >= static_cast<int>(nodes.size()))
			nodes.resize(i + 1);
		if (nodes[i]) {
			assert(nodes[i] == it);
			continue;
		}
		nodes[i] = it;
		for (Node* nbor : it->neighbors)
			todo.push(nbor);
	}
	for (int i = 0; i < static_cast<int>(nodes.size()); ++i) {
		assert(nodes[i] != nullptr);
		assert(nodes[i]->val == i + 1);
	}
	return nodes;
}

vector<vector<int>> toAdjList(Node *graph) {
	vector<vector<int>> adj_list;
	for (Node *it : getNodes(graph)) {
		adj_list.emplace_back();
		for (Node* nbor : it->neighbors) {
			adj_list.back().push_back(nbor->val);
		}
	}
	return adj_list;
}

void deleteGraph(Node* graph) {
	for (Node* it : getNodes(graph))
		delete it;
}

class Solution {
public:
	Node* cloneGraph(Node* node) {
		if (!node)
			return nullptr;
		vector<Node*> nodes(node->val);
		Node* clone = new Node(node->val);
		nodes[node->val - 1] = clone;
		queue<pair<Node*, Node*>> todo;
		todo.emplace(node, clone);
		while (!todo.empty()) {
			auto [it, it_clone] = todo.front();
			todo.pop();
			assert(it_clone->val == it->val);
			assert(it_clone->neighbors.empty());
			for (Node* nbor : it->neighbors) {
				int i = nbor->val - 1;
				if (i >= static_cast<int>(nodes.size()))
					nodes.resize(i + 1);
				Node* nbor_clone = nodes[i];
				if (!nbor_clone) {
					nbor_clone = nodes[i] = new Node(i + 1);
					todo.emplace(nbor, nbor_clone);
				}
				it_clone->neighbors.push_back(nbor_clone);
			}
		}
		return clone;
	}
};

int main()
{
	vector<vector<int>> test_data[] = {
		{},
		{{}},
		{{2}, {1}},
		{{2, 4}, {1, 3}, {2, 4}, {1, 3}},
	};
	bool success = true;
	Solution solution;
	for (auto& adj_list : test_data) {
		cout << "Cloning " << adj_list << endl;
		Node* graph = newGraph(adj_list);
		Node* cloned_graph = solution.cloneGraph(graph);
		assert(graph == nullptr || graph != cloned_graph);
		auto cloned_adj_list = toAdjList(cloned_graph);
		if (cloned_adj_list != adj_list) {
			cout << "  ERROR: got " << cloned_adj_list << endl;
			success = false;
		}
		deleteGraph(graph);
		deleteGraph(cloned_graph);
	}
	return success ? 0 : 1;
}
