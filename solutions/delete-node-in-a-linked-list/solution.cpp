#include <iostream>
#include <vector>
#include <utility>

using namespace std;

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

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* newList(const vector<int>& values)
{
	ListNode* head = nullptr;
	ListNode** pnext = &head;
	for (int x : values) {
		ListNode* node = new ListNode(x);
		*pnext = node;
		pnext = &node->next;
	}
	return head;
}

void deleteList(ListNode* head)
{
	while (head) {
		ListNode* node = head;
		head = head->next;
		delete node;
	}
}

vector<int> getListValues(const ListNode* head)
{
	vector<int> values;
	while (head) {
		values.push_back(head->val);
		head = head->next;
	}
	return values;
}

ListNode* getListNode(ListNode* head, int index)
{
	while (index > 0) {
		head = head->next;
		--index;
	}
	return head;
}

class Solution {
public:
	void deleteNode(ListNode* node) {
		ListNode* next = node->next;
		*node = *next;
		delete next;
	}
};

int main()
{
	const pair<vector<int>, int> test_data[] = {
		{{10, 20}, 0},
		{{40, 50, 10, 30}, 0},
		{{40, 50, 10, 30}, 1},
		{{40, 50, 10, 30}, 2},
	};
	bool success = true;
	Solution solution;
	for (const auto& [values, n] : test_data) {
		ListNode* head = newList(values);
		ListNode *node = getListNode(head, n);
		solution.deleteNode(node);
		auto result = getListValues(head);
		cout << values << ", n=" << n << " -> " << result << endl;
		auto expected = values;
		expected.erase(expected.begin() + n);
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
		deleteList(head);
	}
	return success ? 0 : 1;
}
