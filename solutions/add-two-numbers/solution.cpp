#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
};

struct List {
	ListNode* head = nullptr;
	List(ListNode* head) : head(head) {}
	List(const vector<int>& values) {
		for (auto it = values.begin(); it != values.end(); ++it) {
			auto node = new ListNode(*it);
			node->next = head;
			head = node;
		}
	}
	~List() {
		while (head) {
			auto next = head->next;
			delete head;
			head = next;
		}
	}
	operator ListNode*() { return head; }
};

ostream& operator<< (ostream& out, ListNode* l)
{
	out << "(";
	auto node = l;
	while (node) {
		if (node != l)
			out << " -> ";
		out << node->val;
		node = node->next;
	}
	out << ")";
	return out;
}

class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		int carry = 0;
		ListNode* last = nullptr;
		ListNode* result = nullptr;
		while (l1 || l2 || carry) {
			int val = carry;
			if (l1) {
				val += l1->val;
				l1 = l1->next;
			}
			if (l2) {
				val += l2->val;
				l2 = l2->next;
			}
			carry = val / 10;
			auto node = new ListNode(val % 10);
			if (last)
				last->next = node;
			else
				result = node;
			last = node;
		}
		return result;
	}
};

void test(const vector<int>& v1, const vector<int>& v2)
{
	auto l1 = List(v1);
	auto l2 = List(v2);
	auto result = List(Solution().addTwoNumbers(l1, l2));
	cout << l1 << " + " << l2 << " = " << result << endl;
}

int main()
{
	test({5}, {5});
	test({1, 2, 3}, {3, 5, 7});
	test({1, 5, 3, 7, 8}, {4, 7, 1, 3});
	return 0;
}
