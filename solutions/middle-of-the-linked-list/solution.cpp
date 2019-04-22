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
	ListNode* middleNode(ListNode* head) {
		auto it1 = head;
		auto it2 = head;
		while (it2 && it2->next) {
			it1 = it1->next;
			it2 = it2->next->next;
		}
		return it1;
	}
};

int main()
{
	Solution solution;
	for (int i = 0; i < 8; ++i) {
		auto head = newList(i);
		cout << head << " => " << solution.middleNode(head) << endl;
		deleteList(head);
	}
	return 0;
}
