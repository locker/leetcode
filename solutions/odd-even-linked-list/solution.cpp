#include <iostream>
#include <vector>
#include <utility>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& values) {
	out << '[';
	bool first = true;
	for (const auto& val : values) {
		if (!first)
			out << ',';
		out << val;
		first = false;
	}
	out << ']';
	return out;
}

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* newList(const vector<int> values) {
	ListNode* head = nullptr;
	ListNode** pnext = &head;
	for (int val : values) {
		*pnext = new ListNode(val);
		pnext = &(*pnext)->next;
	}
	return head;
}

void deleteList(ListNode* head) {
	while (head) {
		ListNode* next = head->next;
		delete head;
		head = next;
	}
}

vector<int> listValues(const ListNode* head) {
	vector<int> values;
	while (head) {
		values.push_back(head->val);
		head = head->next;
	}
	return values;
}

class Solution {
public:
	ListNode* oddEvenList(ListNode* head) {
		if (!head || !head->next)
			return head;
		ListNode* odd = head;
		ListNode* cur = head->next;
		int n = 0;
		while (cur->next) {
			ListNode* node = cur->next;
			if (n % 2 == 0) {
				cur->next = node->next;
				node->next = odd->next;
				odd->next = node;
				odd = node;
			} else {
				cur = cur->next;
			}
			++n;
		}
		return head;
	}
};

int main()
{
	const pair<vector<int>, vector<int>> test_data[] = {
		{{}, {}},
		{{1, 2}, {1, 2}},
		{{1, 2, 3}, {1, 3, 2}},
		{{1, 2, 3, 4, 5}, {1, 3, 5, 2, 4}},
		{{2, 1, 3, 5, 6, 4, 7}, {2, 3, 6, 7, 1, 5, 4}},
	};
	bool success = true;
	Solution solution;
	for (const auto& [values, expected] : test_data) {
		ListNode* head = newList(values);
		cout << listValues(head) << " => ";
		head = solution.oddEvenList(head);
		cout << listValues(head) << endl;
		if (listValues(head) != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
