#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

ostream& operator<<(ostream& out, const ListNode* head)
{
	out << '(';
	auto node = head;
	while (node) {
		if (node != head)
			out << ", ";
		out << node->val;
		node = node->next;
	}
	out << ')';
	return out;
}

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

class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		auto it1 = head;
		auto it2 = head;
		while (n-- > 0) {
			it1 = it1->next;
			if (!it1) {
				auto node = head;
				head = head->next;
				delete node;
				return head;
			}
		}
		for (it1 = it1->next; it1; it1 = it1->next)
			it2 = it2->next;
		auto node = it2->next;
		it2->next = node->next;
		delete node;
		return head;
	}
};

void test(const vector<int>& values, int n)
{
	auto head = newList(values);
	cout << head << ", " << n << " => ";
	head = Solution().removeNthFromEnd(head, n);
	cout << head << endl;
	deleteList(head);
}

int main()
{
	test({1, 2, 3, 4}, 1);
	test({1, 2, 3, 4}, 2);
	test({1, 2, 3, 4}, 3);
	test({1, 2, 3, 4}, 4);
	return 0;
}
