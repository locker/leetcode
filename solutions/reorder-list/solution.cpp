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
	void reorderList(ListNode* head) {
		if (!head)
			return;

		// First, find the middle node of the given list.
		auto it1 = head;
		auto it2 = head;
		while (it2 && it2->next) {
			it1 = it1->next;
			it2 = it2->next;
			it2 = it2->next;
		}
		// Split the list in two by the middle node and
		// reverse the second part. The middle node goes
		// to the first part.
		it2 = it1->next;
		it1 = it1->next = nullptr;
		while (it2) {
			auto next = it2->next;
			it2->next = it1;
			it1 = it2;
			it2 = next;
		}
		// Finally, interleave nodes of the two parts.
		it2 = it1;
		it1 = head;
		while (it2) {
			auto next1 = it1->next;
			auto next2 = it2->next;
			it1->next = it2;
			it2->next = next1;
			it1 = next1;
			it2 = next2;
		}
	}
};

void test(const vector<int>& values)
{
	ListNode* head = newList(values);
	cout << head << " => ";
	Solution().reorderList(head);
	cout << head << endl;
	deleteList(head);
}

int main()
{
	vector<int> input[] = {
		{},
		{1},
		{1, 2},
		{1, 2, 3},
		{1, 2, 3, 4},
		{1, 2, 3, 4, 5},
		{1, 2, 3, 4, 5, 6},
		{1, 2, 3, 4, 5, 6, 7},
	};
	for (const auto& values: input)
		test(values);
	return 0;
}
