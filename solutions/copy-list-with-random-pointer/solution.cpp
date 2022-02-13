#include <cassert>
#include <iostream>
#include <unordered_map>
#include <optional>
#include <vector>
#include <utility>

using namespace std;

template<typename T>
ostream& operator<<(ostream& o, optional<T> v) {
	if (v.has_value())
		return o << v.value();
	else
		return o << "null";
}

template<typename T, typename U>
ostream& operator<<(ostream& o, pair<T, U> v) {
	return o << '(' << v.first << ',' << v.second << ')';
}

template<typename T>
ostream& operator<<(ostream& o, vector<T> v) {
	o << '[';
	bool first = true;
	for (auto& x : v) {
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
	Node* next;
	Node* random;
	Node(int _val) {
		val = _val;
		next = nullptr;
		random = nullptr;
	}
};

Node* newList(const vector<pair<int, optional<int>>> elements) {
	const int count = elements.size();
	vector<Node*> nodes(count);
	for (int i = 0; i < count; ++i) {
		const auto& elem = elements[i];
		if (!nodes[i])
			nodes[i] = new Node(0);
		Node* node = nodes[i];
		assert(node->val == 0);
		node->val = elem.first;
		if (elem.second.has_value()) {
			int j = elem.second.value();
			assert(j < count);
			if (!nodes[j])
				nodes[j] = new Node(0);
			node->random = nodes[j];
		}
		if (i > 0)
			nodes[i - 1]->next = node;
	}
	return nodes.empty() ? nullptr : nodes[0];
}

void deleteList(Node* head) {
	while (head) {
		Node* next = head->next;
		delete head;
		head = next;
	}
}

vector<pair<int, optional<int>>> getElements(Node* head) {
	unordered_map<Node*, int> node2idx;
	int idx = 0;
	for (Node* it = head; it; it = it->next)
		node2idx.emplace(it, idx++);
	vector<pair<int, optional<int>>> elements;
	for (Node* it = head; it; it = it->next) {
		optional<int> random;
		if (it->random)
			random = node2idx[it->random];
		elements.emplace_back(it->val, random);
	}
	return elements;
}

class Solution {
public:
	Node* copyRandomList(Node* head) {
		vector<Node*> copy;
		unordered_map<Node*, int> node2idx;
		int idx = 0;
		for (Node* it = head; it; it = it->next) {
			copy.push_back(new Node(it->val));
			if (idx > 0)
				copy[idx - 1]->next = copy[idx];
			node2idx.emplace(it, idx);
			++idx;
		}
		idx = 0;
		for (Node* it = head; it; it = it->next) {
			if (it->random)
				copy[idx]->random = copy[node2idx[it->random]];
			++idx;
		}
		return copy.empty() ? nullptr : copy[0];
	}
};

int main()
{
	vector<pair<int, optional<int>>> test_data[] = {
		{},
		{{5,nullopt}},
		{{1,1},{2,1}},
		{{3,nullopt},{3,0},{3,nullopt}},
		{{7,nullopt},{13,0},{11,4},{10,2},{1,0}},
	};
	bool success = true;
	Solution solution;
	for (const auto& elements : test_data) {
		cout << "Copying " << elements << endl;
		Node* head = newList(elements);
		Node* head_copy = solution.copyRandomList(head);
		assert(head == nullptr || head != head_copy);
		auto elements_copy = getElements(head_copy);
		if (elements_copy != elements)
			cout << "  ERROR: got " << elements_copy << endl;
		deleteList(head);
		deleteList(head_copy);
	}
	return success ? 0 : 1;
}
