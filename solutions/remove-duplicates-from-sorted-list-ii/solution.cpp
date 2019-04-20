#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* newList(const vector<int>& values)
{
	ListNode* head = nullptr;
	for (auto it = values.rbegin(); it != values.rend(); ++it) {
		auto node = new ListNode(*it);
		node->next = head;
		head = node;
	}
	return head;
}

void deleteList(ListNode* head)
{
	while (head) {
		auto next = head->next;
		delete head;
		head = next;
	}
}

ostream& operator<<(ostream& out, const ListNode* head)
{
	out << '[';
	for (auto node = head; node; node = node->next) {
		if (node != head)
			out << ',';
		out << node->val;
	}
	out << ']';
	return out;
}

class Solution {
public:
	ListNode* deleteDuplicates(ListNode* head) {
		auto pcurr = &head;
		while (*pcurr) {
			int val = (*pcurr)->val;
			auto next = (*pcurr)->next;
			if (!next || next->val != val) {
				pcurr = &(*pcurr)->next;
				continue;
			}
			delete *pcurr;
			do {
				auto tmp = next->next;
				delete next;
				next = tmp;
			} while (next && next->val == val);
			*pcurr = next;
		}
		return head;
	}
};

void test(const vector<int> values)
{
	Solution solution;
	ListNode *head = newList(values);
	cout << "Input: " << head << endl;
	head = solution.deleteDuplicates(head);
	cout << "Output: " << head << endl;
	deleteList(head);
}

int main()
{
	vector<int> input[] = {
		{},
		{1},
		{1, 1},
		{1, 2, 3},
		{1, 2, 2, 3},
		{1, 1, 2, 3, 3},
		{1, 1, 2, 2, 3, 3},
	};
	for (const auto& values: input)
		test(values);
	return 0;
}
