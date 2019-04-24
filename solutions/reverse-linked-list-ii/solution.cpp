#include <iostream>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* newList(int n)
{
	ListNode* head = nullptr;
	for (int i = n; i > 0; --i) {
		auto node = new ListNode(i);
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
	ListNode* reverseBetween(ListNode* head, int m, int n) {
		if (m == n)
			return head;

		// Find the link to the first node to reverse.
		int i = 1;
		auto pfirst = &head;
		while (i < m) {
			pfirst = &(*pfirst)->next;
			++i;
		}

		// Reverse nodes between m and n.
		auto prev = *pfirst;
		auto curr = prev->next;
		while (i < n) {
			auto next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
			++i;
		}
		// Now, prev is the head of the reversed sub-list
		// while curr is the next node in the original list.

		// Link the sub-list to the original list.
		(*pfirst)->next = curr;
		*pfirst = prev;
		return head;
	}
};

int main()
{
	Solution solution;
	for (int len = 1; len < 6; ++len) {
		for (int m = 1; m <= len; ++m) {
			for (int n = m; n <= len; ++n) {
				auto head = newList(len);
				cout << head << ", m = " << m << ", n = " << n;
				head = solution.reverseBetween(head, m, n);
				cout << " => " << head << endl;
				deleteList(head);
			}
		}
	}
	return 0;
}
